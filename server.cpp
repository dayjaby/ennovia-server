#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "governor.hpp"

using namespace Ennovia;



int main(int argc, char* argv[])
{
    try {
        Governor& gov = Governor::get();
        gov.run();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

