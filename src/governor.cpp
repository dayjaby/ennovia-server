#include "governor.hpp"
#include "core.hpp"
#include "world/map.hpp"
#include "world/optionlist.hpp"
#include "world/database.hpp"
#include "world/lua/manager.hpp"
#include "world/library.hpp"
#include "world/actions.hpp"
#include "world/locatable.hpp"

#include <mongo/client/dbclient.h>

namespace Ennovia
{

struct GovernorImpl
{
    GovernorImpl(Governor& gov);
    ~GovernorImpl();
    bool alive;
    void run();
    void tick();

    int getTicks()
    {
        return ticks;
    }

    /** Interface for the world **/
    void updateLocatablePosition(Locatable* locatable);
    void moveLocatable(int id,float x,float y);
    void writeMessage(int id,const std::string& msg);

    /** Interface for the network **/
    void onClientConnected(ServerConnection connection);
    void getTileOptionList(ServerConnection connection,int map,int x,int y);
    void getLocatableOptionList(ServerConnection connection,int id);
    void walkTo(ServerConnection connection,float x,float y);

    void chooseOption(ServerConnection,int optionlist,int id);
    void getLocatablePosition(ServerConnection connection,int id);
    void getLocatableIntroduction(ServerConnection connection,int id);

    void login(ServerConnection connection, const std::string& username, const std::string& password);

    void requestMap(ServerConnection connection,int id);

    Governor& governor;
    ConnectionContainer connections;
    OptionListContainer optionLists;
    LocatableContainer locatables;
    MapContainer maps;

    ActionList actionList;

    void sendLocatableOptionList(ServerConnection connection,int locatable);
    void introduceAllLocatables(ServerConnection connection,int id);

    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer;
    int ticks;
    std::map<std::string,int> players;
    Server server;
    mongo::Status mongoStatus;
    mongo::DBClientConnection db;
    Lua::Manager lua;
};

GovernorImpl::GovernorImpl(Governor& gov) :
    governor(gov),
    //db(new Database("tcp://127.0.0.1:3306","root","")),
    timer(io_service, boost::posix_time::milliseconds(TICK)),
    server(io_service,PORT),
    ticks(0),
    mongoStatus(mongo::client::initialize())
{
    std::cout << "Trying to connect to database..." << std::endl;
    db.connect("localhost");
    std::cout << "GovernorImpl constructed" << std::endl;
}

GovernorImpl::~GovernorImpl()
{
    //delete db;
}

void GovernorImpl::run()
{
    io_service.run();
    alive = true;
    tick();
}

void GovernorImpl::tick()
{
    if(alive)
    {
        ticks++;
        timer.expires_at(timer.expires_at() + boost::posix_time::milliseconds(TICK));
        timer.async_wait(boost::bind(&GovernorImpl::tick, this));

        actionList.tick();

        //  server.write<Client::SEND_ENTITIES>(player,...);
    }
}

void GovernorImpl::updateLocatablePosition(Locatable* locatable)
{
    int id = locatables.get(locatable);
    if(id)
    {
        ServerConnection connection = connections.get(id);
        if(connection.get())
        {
            std::cout << "Update position" << std::endl;
            // This locatable is a player! Save his data in the database
            mongo::BSONObjBuilder builder1,builder2,builder3;
            builder1.append("x", locatable->getPosition().x);
            builder1.append("y", locatable->getPosition().y);
            builder2.append("$set",builder1.obj());
            builder3.append("name", locatable->getName());
            /*db.update("ennovia.player",
                      builder3.obj(),
                      builder2.obj());*/
        }
        governor.log << "UPDATE LOCATABLE THAT EXISTS" << std::endl;
        Map* map = locatable->getPosition().map;
        int mapid = maps.get(locatable->getPosition().map);
        Json::Value msg(Json::objectValue);
        msg["msg"] = LOCATABLE_POSITION;
        msg["id"] = id;
        msg["mapid"] = mapid;
        msg["x"] = int(locatable->getPosition().x * 100);
        msg["y"] = int(locatable->getPosition().y * 100);

        typedef std::set<Locatable*>::iterator Iterator;
        for(Iterator i = map->locatables.begin(); i != map->locatables.end(); ++i)
        {
            if((*i)->getPosition().map == map)
            {
                ServerConnection connection = connections.get(id);
                if(connection.get())
                {
                    connection->write(msg);
                }
            }
        }

    }
}


void GovernorImpl::moveLocatable(int id,float x,float y)
{
    Locatable* locatable = locatables.get(id);
    if(locatable)
    {
        governor.log << "MOVE LOCATABLE THAT EXISTS" << std::endl;
        Map* map = locatable->getPosition().map;
        actionList.add(new Move(locatable,locatable->getPosition(),Position(x,y,map)));
        governor.log << "movement added to list" << std::endl;
        Json::Value msg(Json::objectValue);
        msg["msg"] = MOVE_TO;
        msg["id"] = id;
        msg["x"] = int(x*100);
        msg["y"] = int(y*100);
        ServerConnection connection = connections.get(id);
        if(connection.get())
        {
            connection->write(msg);
        }
        typedef std::set<Locatable*>::iterator Iterator;
        for(Iterator i = map->locatables.begin(); i != map->locatables.end(); ++i)
        {
            Locatable* loc = *i;
            if(loc->getPosition().map == map)
            {
                int locatable_id = locatables.get(loc);
                ServerConnection locatable_connection = connections.get(locatable_id);
                if(locatable_connection.get() && locatable_connection.get() != connection.get())
                {
                    locatable_connection->write(msg);
                }
            }
        }
    }
}

void GovernorImpl::writeMessage(int id,const std::string& msg)
{
    ServerConnection connection = connections.get(id);
    if(connection.get())
    {
        Json::Value out(Json::objectValue);
        out["msg"] = SEND_MESSAGE;
        out["text"] = msg;
        connection->write(out);
    }
}

void GovernorImpl::onClientConnected(ServerConnection connection)
{
    Json::Value out(Json::objectValue);
    out["msg"] = SEND_MESSAGE;
    out["text"] = "Welcome to our server!";
    connection->write(out);
    Json::Value request(Json::objectValue);
    request["msg"] = REQUEST_CREDENTIALS;
    connection->write(request);
}

void GovernorImpl::getLocatableOptionList(ServerConnection connection,int id)
{
    sendLocatableOptionList(connection,id);
}

void GovernorImpl::walkTo(ServerConnection connection,float x,float y)
{
    std::cout << "WALK TO " << x << "," << y << std::endl;
    int player_id = connections.get(connection);
    moveLocatable(player_id,x,y);
}



void GovernorImpl::chooseOption(ServerConnection connection,int optionlist,int id)
{
    OptionList* list = optionLists.get(optionlist);
    if(list)
    {
        int connection_id = connections.get(connection);
        Locatable* locatable = locatables.get(connection_id);
        if(locatable)
            list->options[id]->onChoose(locatable);
    }
}

void GovernorImpl::getLocatablePosition(ServerConnection connection,int id)
{
    Locatable* locatable = locatables.get(id);
    if(locatable)
    {
        int mapid = maps.get(locatable->getPosition().map);
        Json::Value position(Json::objectValue);
        position["msg"] = LOCATABLE_POSITION;
        position["id"] = id;
        position["map"] = mapid;
        position["x"] = int(locatable->getPosition().x*100);
        position["y"] = int(locatable->getPosition().y*100);
        connection->write(position);
    }
    else
    {
        std::cout << id << "doesnt exist" << std::endl;
    }
}
void GovernorImpl::getLocatableIntroduction(ServerConnection connection,int id)
{
    Json::Value intro(Json::objectValue);
    intro["msg"] = INTRODUCE_LOCATABLE;
    intro["id"] = id;
    intro["type"] = 0;
    Locatable* locatable = locatables.get(id);
    if(locatable)
    {
        intro["name"] = locatable->getName();
        if(locatable->model().length()>0)
        {
            intro["model"] = locatable->model();
            if(locatable->texture().length()>0) {
                intro["texture"] = locatable->texture();
            }

        }
        connection->write(intro);
    }
}


void GovernorImpl::login(ServerConnection connection,const std::string& username, const std::string& password)
{
    /// TODO: LUA
    //db->playerLogin(username,password);
    Json::Value answer(Json::objectValue);
    std::auto_ptr<mongo::DBClientCursor> cursor = db.query("ennovia.player", BSON("name" << username << "password" << password));
    if(cursor->more())
    {
        mongo::BSONObj playerdata = cursor->next();
        answer["msg"] = LOGIN_VALID;
        connection->write(answer);
        Locatable* player;
        int player_id;
        if(players.count(username) > 0)
        {
            player_id = players[username];
            player = locatables.get(player_id);
            if(player)
            {
                ServerConnection old_connection = connections.get(player_id);
                old_connection->disconnect();
            }
        }
        else
        {
            player_id = locatables.create(username);
            players[username] = player_id;
            player = locatables.get(player_id);
        }
        governor.log << "Login: " << player_id;
        player->model() = playerdata["model"].String();
        player->texture() = playerdata["texture"].String();
        Map* map = maps.get(playerdata["currentMap"].Int());
        if(map)
        {
            player->setPosition(Position(playerdata["x"].Double(),playerdata["y"].Double(),map));
            governor.log << "Introduce all locatables" << std::endl;
            introduceAllLocatables(connection,player_id);
            governor.log << "Send you are " << player_id << std::endl;
            Json::Value youAre(Json::objectValue);
            youAre["msg"] = YOU_ARE;
            youAre["id"] = player_id;
            connection->write(youAre);

            getLocatablePosition(connection,player_id);
        }
        connections.create(player_id,connection);
    }
    else
    {
        answer["msg"] = LOGIN_PASSWORD_INVALID;
        connection->write(answer);
    }
}

void GovernorImpl::requestMap(ServerConnection connection,int id)
{
    Map* map = maps.get(id);
    if(map)
    {
        Json::Value msg(Json::objectValue);
        msg["msg"] = SEND_MAP;
        msg["id"] = id;
        msg["path"] = map->path;
        msg["heightmap"] = map->heightmappath;
        msg["width"] = map->width;
        msg["height"] = map->height;
        connection->write(msg);
    }
}

void GovernorImpl::sendLocatableOptionList(ServerConnection connection,int id)
{
    Json::Value msg(Json::objectValue);
    msg["msg"] = SEND_LOCATABLE_OPTIONLIST;
    int player_id = connections.get(connection);
    if(player_id)
    {
        Locatable* player = locatables.get(player_id);
        Locatable* locatable = locatables.get(id);
        if(player && locatable)
        {
            OptionList* optionlist = locatable->getOptionList(player);
            int olid = optionLists.create(optionlist);
            msg["id"] = id;
            int i=0;
            Json::Value options(Json::arrayValue);
            for(OptionList::Options::iterator iter=optionlist->options.begin(); iter!=optionlist->options.end(); ++iter,++i)
            {
                Json::Value option(Json::objectValue);
                option["index"] = i;
                option["description"] = (*iter)->getDescription();
                option["optionlist"] = olid;
                options.append(option);
            }

            msg["options"] = options;
            connection->write(msg);
        }
    }
}

void GovernorImpl::introduceAllLocatables(ServerConnection connection,int id)
{
    std::cout << "introduce all locatables " << id << std::endl;
    Locatable* locatable = locatables.get(id);
    if(locatable)
    {
        Map* map = locatable->getPosition().map;
        if(map)
        {
            std::cout << "map found" << std::endl;
            for(Map::Locatables::iterator i=map->locatables.begin(); i!=map->locatables.end(); ++i)
            {
                Locatable* loc = *i;
                int loc_id = locatables.get(loc);
                std::cout << "#" << loc_id << std::endl;
                if(loc_id)
                    getLocatableIntroduction(connection,loc_id);
            }
        }
    }
}

Governor::Governor()
: log("server_log.txt")
, d(new GovernorImpl(*this))
{
    std::cout << "Governor constructed" << std::endl;
}

Governor gov;

Governor& Governor::get() {
    //static Governor instance;
    return gov;
}

bool Governor::isAlive()
{
    return d->alive;
}
void Governor::run()
{
    d->lua.run();
    d->run();
}
int Governor::getTicks()
{
    return d->ticks;
}

/** Interface for the world **/
void Governor::updateLocatablePosition(Locatable* locatable)
{
    d->updateLocatablePosition(locatable);
}
void Governor::moveLocatable(int id,float x,float y)
{
    d->moveLocatable(id,x,y);
}
void Governor::writeMessage(int id,const std::string& msg)
{
    d->writeMessage(id,msg);
}

/** Interface for the network **/
void Governor::onClientConnected(ServerConnection connection)
{
    d->onClientConnected(connection);
}
void Governor::getLocatableOptionList(ServerConnection connection,int id)
{
    d->getLocatableOptionList(connection,id);
}
void Governor::walkTo(ServerConnection connection,float x,float y)
{
    d->walkTo(connection,x,y);
}

void Governor::chooseOption(ServerConnection connection,int optionlist,int id)
{
    d->chooseOption(connection,optionlist,id);
}
void Governor::getLocatablePosition(ServerConnection connection,int id)
{
    d->getLocatablePosition(connection,id);
}
void Governor::getLocatableIntroduction(ServerConnection connection,int id)
{
    d->getLocatableIntroduction(connection,id);
}

void Governor::login(ServerConnection connection, const std::string& username, const std::string& password)
{
    d->login(connection,username,password);
}

void Governor::requestMap(ServerConnection connection,int id)
{
    d->requestMap(connection,id);
}

MapContainer& Governor::getMaps() {
    return d->maps;
}
LocatableContainer& Governor::getLocatables() { return d->locatables; }
OptionListContainer& Governor::getOptionLists() { return d->optionLists; }
ConnectionContainer& Governor::getConnections() { return d->connections; }


}
