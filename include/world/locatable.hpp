#ifndef ENNOVIA_LOCATABLE_HPP
#define ENNOVIA_LOCATABLE_HPP

#include <deque>
#include "world/entity.hpp"
#include "world/position.hpp"
#include "world/actions.hpp"

namespace Ennovia
{
class Locatable : public Entity
{
public:
    Locatable(const Position& pos, const std::string& name_, const std::string& model, const std::string& texture);
    Locatable(const Position& pos, const std::string& name_);
    virtual ~Locatable();

    virtual OptionList* getOptionList(Locatable* p);
    virtual std::string getName();
    virtual std::string onExamine(Locatable* o);

    const Position& getPosition() const {return position_; }
    void setPosition(const Position& position);

    const std::string& model() const { return model_; }
    std::string& model() { return model_; }

    const std::string& texture() const { return texture_; }
    std::string& texture() { return texture_; }

    virtual float getMovementSpeed() { return 0.1; }

    ActionList actions;
    boost::shared_ptr<Action> currentAction;

protected:

    Position position_;
    std::string model_;
    std::string texture_;

    unsigned actionEnd;

    std::string name;
};
}
#endif
