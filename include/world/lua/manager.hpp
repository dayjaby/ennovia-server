#ifndef ENNOVIA_LUA_MANAGER_HPP
#define ENNOVIE_LUA_MANAGER_HPP

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include <luabind/dependency_policy.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/return_reference_to_policy.hpp>


namespace Ennovia {

    namespace Lua {


    class Manager
    {
    public:
        Manager();
        ~Manager();
        lua_State* getState();
        void run();
    private:
        void openlualibs(lua_State* L, const luaL_reg* lib);
        void loadlibs(lua_State* L);
        static int add_file_and_line(lua_State* L);
        void init(lua_State* L);

        lua_State* L;
    };

    }
}
#endif
