#include "world/lua/manager.hpp"
#include "world/map.hpp"
#include "world/optionlist.hpp"
#include "world/locatable.hpp"

namespace Ennovia {
    namespace Lua {
        struct LocatableWrapper : Locatable, luabind::wrap_base
        {
            LocatableWrapper(const Position& position, const std::string& name_, const std::string& model_, const std::string& texture_)
            : Locatable(position,name_,model_,texture_) {
            }

            LocatableWrapper(const Position& position, const std::string& name_)
            : Locatable(position,name_) {
            }

            virtual OptionList* getOptionList(Locatable* lo) {
                return call<OptionList*>("getOptionList",lo);
            }

            static OptionList* default_getOptionList(Locatable* ptr, Locatable* lo) {
                return ptr->Locatable::getOptionList(lo);
            }

        };


        struct OptionWrapper : Option, luabind::wrap_base
        {
            virtual std::string getDescription() {
                return call<std::string>("getDescription");
            }
            static std::string default_getDescription(Option* ptr) {
                return ptr->Option::getDescription();
            }
            virtual void onChoose(Locatable* performer) {
                call<void>("onChoose",performer);
            }
            static void default_onChoose(Option* ptr, Locatable* performer) {
                ptr->Option::onChoose(performer);
            }
        };

        Manager::Manager() : L(lua_open()) {
            loadlibs(L);
            init(L);
        }
        Manager::~Manager() {
            lua_close(L);
        }
        lua_State* Manager::getState() { return L; }

        void Manager::run() {
            if(luaL_loadfile(L,"lua/core.lua") || lua_pcall(L,0,0,0)) {
                std::cerr << "Cannot run lua file: " << lua_tostring(L,-1) << std::endl;
                throw 0;
            }
       }
        void Manager::openlualibs(lua_State* L, const luaL_reg* lib) {
            for(;lib->func;lib++) {
                lua_pushcfunction(L, lib->func);
                lua_pushstring(L, lib->name);
                lua_call(L, 1, 0);
            }
        }

        void Manager::loadlibs(lua_State* L) {
            static const luaL_reg lualibs[] =
                {{"base", luaopen_base},
                {NULL,NULL}};
            openlualibs(L,lualibs);
        }
        int Manager::add_file_and_line(lua_State* L)
        {
           lua_Debug d;
           lua_getstack(L, 1, &d);
           lua_getinfo(L, "Sln", &d);
           std::string err = lua_tostring(L, -1);
           lua_pop(L, 1);
           std::stringstream msg;
           msg << d.short_src << ":" << d.currentline;

           if (d.name != 0)
           {
              msg << "(" << d.namewhat << " " << d.name << ")";
           }
           msg << " " << err;
           lua_pushstring(L, msg.str().c_str());
           return 1;
        }
        void Manager::init(lua_State* L) {
            using namespace luabind;
            open(L);
            module(L)
            [
                class_<Map>("Map")
                    .def(constructor<int,const std::string&,const std::string&,int,int>())
                    .def("getHeight",&Map::getHeight)
                , class_<Position>("Position")
                    //.def(constructor<>())
                    .def(constructor<float,float,Map*>())
                    .def_readwrite("x",&Position::x)
                    .def_readwrite("y",&Position::y)
                    .def_readwrite("map",&Position::map)
                , class_<Option,OptionWrapper>("Option")
                    .def(constructor<>())
                    .def("getDescription",&Option::getDescription,&OptionWrapper::default_getDescription)
                    .def("onChoose",&Option::onChoose,&OptionWrapper::default_onChoose)
                , class_<OptionList>("OptionList")
                    .def(constructor<>())
                    .def("add",&OptionList::add)
                    .def("addList",&OptionList::addList)
                , class_<Locatable,LocatableWrapper>("Locatable")
                    .def(constructor<const Position&,const std::string&,const std::string&,const std::string&>())
                    .def(constructor<const Position&,const std::string&>())
                    .def("getOptionList", &Locatable::getOptionList, &LocatableWrapper::default_getOptionList)

            ];
        }
    }
}
