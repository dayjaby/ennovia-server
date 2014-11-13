#ifndef ENNOVIA_GOVERNOR_HPP
#define ENNOVIA_GOVERNOR_HPP

#include <fstream>
#include <memory>
#include "network/network.hpp"

namespace Ennovia {
class GovernorImpl;
class Locatable;
class LocatableContainer;
class MapContainer;
class OptionListContainer;
class ConnectionContainer;
class Governor {
public:
    Governor();
    static Governor& get();

    std::ofstream log;
    bool isAlive();
    void run();
    int getTicks();

    /** Interface for the world **/
    void updateLocatablePosition(Locatable* locatable);
    void moveLocatable(int id,float x,float y);
    void writeMessage(int id,const std::string& msg);

    /** Interface for the network **/
    void onClientConnected(ServerConnection connection);
    void getLocatableOptionList(ServerConnection connection,int id);
    void walkTo(ServerConnection connection,float x,float y);
    void chooseOption(ServerConnection,int optionlist,int id);
    void getLocatablePosition(ServerConnection connection,int id);
    void getLocatableIntroduction(ServerConnection connection,int id);

    void login(ServerConnection connection, const std::string& username, const std::string& password);

    void requestMap(ServerConnection connection,int id);
    ConnectionContainer& getConnections();
    MapContainer& getMaps();
    LocatableContainer& getLocatables();
    OptionListContainer& getOptionLists();
private:
    std::auto_ptr<GovernorImpl> d;
};

}

#endif
