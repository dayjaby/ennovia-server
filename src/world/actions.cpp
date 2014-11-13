#include "world/actions.hpp"
#include "world/locatable.hpp"
#include "governor.hpp"

namespace Ennovia {

    void Action::onTick() {}
    void ActionList::tick() {
        std::cout << "tick()" << std::endl;
        for(Actions::iterator i = actions.begin();i != actions.end();i++) {
            boost::shared_ptr<Action> action = *i;
            std::cout << action->getTicks() << ">=" << action->getDuration() << std::endl;
            if(action->getTicks()>=action->getDuration()) {
                action->onFinish();
                actions.erase(action);
            } else {
                action->tick();
                return;
            }
        }
    }

    ActionList& ActionList::add(Action* action) {
        actions.insert(boost::shared_ptr<Action>(action));
        return *this;
    }

Move::Move(Locatable* performer,const Position& start,const Position& end)
    : Action(performer) {
        float dx = end.x - start.x;
        float dy = end.y - start.y;
        distance = std::sqrt(dx*dx+dy*dy);
        float movement = performer->getMovementSpeed();
        if(distance == 0 || movement == 0) {
            duration = 0;
            dX = 0;
            dY = 0;
        } else {
            duration = std::ceil(distance / movement);
            dX = dx / duration;
            dY = dy / duration;
        }
        std::cout << "dx=" << dx << ",dy=" << dy << std::endl;
        std::cout << "DURATION=" << duration << ",MOVEMENT=" << movement << ",DX=" << dX << ",DY=" << dY << std::endl;
    }
    void Move::onTick() {
        Governor::get().log << "MOVE TICKS" << std::endl;
        Position pos = performer->getPosition();
        pos.x += dX;
        pos.y += dY;
        performer->setPosition(pos);
        Governor::get().updateLocatablePosition(performer);
    }
    void Move::onFinish() {
    }


}


