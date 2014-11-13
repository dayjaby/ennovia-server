#include "world/entity.hpp"
#include "world/optionlist.hpp"

namespace Ennovia {

OptionList* Entity::getOptionList(Locatable* o) {
    return new OptionList();
}

}
