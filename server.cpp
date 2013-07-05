#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "governor.hpp"
#include "world/player.hpp"
#include "world/optionlist.hpp"
#include "misc/registry.hpp"
using namespace Ennovia;



int main(int argc, char* argv[])
{
    Governor& gov = Governor::get();
    gov.run();
    return 0;
}

