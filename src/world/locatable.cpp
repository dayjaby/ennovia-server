#include "world/locatable.hpp"
#include "governor.hpp"
#include "world/library.hpp"
#include "world/optionlist.hpp"
#include "world/map.hpp"

namespace Ennovia
{

Locatable::Locatable(const Position& pos, const std::string& name_, const std::string& model, const std::string& texture)
    : actionEnd(0), name(name_), model_(model), texture_(texture)
{
    Governor::get().getLocatables().create(this);
    setPosition(pos);
}

Locatable::Locatable(const Position& pos, const std::string& name_) : actionEnd(0), name(name_)
{
    setPosition(pos);
}

Locatable::~Locatable()
{
    //if(position_.map)
    //    position_.map->getTile(position_.x,position_.y).leave(this);
}


std::string Locatable::getName()
{
    return name;
}

std::string Locatable::onExamine(Locatable* o)
{
    std::cout << "examining" << std::endl;
    return name;
}



class LookAtOption : public Option {
public:
    LookAtOption(Locatable* lo_) : lo(lo_) {}
    virtual ~LookAtOption() {}
    virtual std::string getDescription() {
        return "Look at";
    }
    virtual void onChoose(Locatable* lo_) {
        int id = Governor::get().getLocatables().get(lo_);
        std::stringstream ss;
        ss << "You see a " << lo->getName();
        Governor::get().writeMessage(id,ss.str());
    }
private:
    Locatable* lo;
};


OptionList* Locatable::getOptionList(Locatable* p)
{
    OptionList* ol = new OptionList();
    ol->add(new LookAtOption(this));
    return ol;
}

void Locatable::setPosition(const Position& position)
{
    //bool change = !(position==position_);
    //if(change && position_.isValid())
    //    position_.getTile()->leave(this);
    if(position.map != position_.map)
    {
        if(position_.map) {
            position_.map->locatables.erase(this);
        }
        if(position.map) {
            position.map->locatables.insert(this);
        }
        //Governor::get().updateLocatablePosition(this);
    }
    position_ = position;
    //if(change && position_.isValid())
    //    position_.getTile()->enter(this);
}



}
