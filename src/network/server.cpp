#include "network/server.hpp"
#include "network/message.hpp"
#include "governor.hpp"

namespace Ennovia
{

Server::Server(boost::asio::io_service& io_service, unsigned short port): acceptor_(io_service,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    // Start an accept operation for a new connection.
    boost::shared_ptr<Connection> new_conn(new Connection(acceptor_.get_io_service()));
    std::cout << "async accept" << std::endl;
    acceptor_.async_accept(new_conn->socket(),
                           boost::bind(&Server::handle_accept, this,
                                       boost::asio::placeholders::error, new_conn));
}

void Server::start_read(boost::shared_ptr<Connection> connection)
{
    connection->async_read(boost::bind(&Server::finished_read, this,
                                       boost::asio::placeholders::error, connection),
                           boost::bind(&Server::interpret, this,_1,connection),connection);
}

void Server::finished_read(const boost::system::error_code& e, boost::shared_ptr<Connection> connection)
{
    if(e)
    {
        std::cerr << e.message() << std::endl;
        if(e == boost::asio::error::connection_aborted)
        {
            std::cerr << "aborted" << std::endl;
        }
        else if(e == boost::asio::error::connection_reset)
        {
            std::cerr << "reset" << std::endl;
        }
        else
        {
            start_read(connection);
        }
    }
    else
    {
        start_read(connection);
    }
}

void Server::handle_accept(const boost::system::error_code& e, boost::shared_ptr<Connection> connection)
{
    std::cout << "Handle accept" << std::endl;
    if (!e)
    {
        start_read(connection);
        Governor::get().onClientConnected(connection);
    }

    // Start an accept operation for a new connection.
    boost::shared_ptr<Connection> new_conn(new Connection(acceptor_.get_io_service()));
    acceptor_.async_accept(new_conn->socket(),
                           boost::bind(&Server::handle_accept, this,
                                       boost::asio::placeholders::error, new_conn));
}

void Server::interpret(const Json::Value& in, boost::shared_ptr<Connection> connection)
{
    Governor& governor = Governor::get();
    try
    {

        if(!in.isMember("msg")) return;
        int msgid = in["msg"].asInt();
        std::cout << "Received message: " << msgid << " from " << connection->socket().remote_endpoint().address().to_string() << std::endl;

        switch(msgid)
        {
        case MESSAGE:
        {
            std::cout << "[msg from Client]: " << in["text"].asString() << std::endl;
            governor.log << "[msg from Client]: " << in["text"].asString();
        }
        break;
        case GET_LOCATABLE_OPTIONLIST:
        {
            governor.log << "Get Locatable OptionList " << in["id"].asInt() << std::endl;
            governor.getLocatableOptionList(connection,in["id"].asInt());
        }
        break;
        case WALK_TO:
        {
            governor.walkTo(connection,in["x"].asFloat(),in["y"].asFloat());
        }
        break;
        case CHOOSE_OPTION:
        {
            governor.chooseOption(connection,in["optionlist"].asInt(),in["id"].asInt());
            governor.log << "Choose Option" << in["optionlist"].asInt() << "," << in["id"].asInt();
        }
        break;
        case GET_LOCATABLE_POSITION:
        {
            governor.getLocatablePosition(connection,in["id"].asInt());
            governor.log << "Get Locatable Position " << in["id"].asInt();
        }
        break;
        case GET_LOCATABLE_INTRODUCTION:
        {
            governor.getLocatableIntroduction(connection,in["id"].asInt());
            governor.log << "Get Locatable Introduction " << in["id"].asInt();
        }
        break;
        case CREDENTIALS:
        {
            governor.login(connection,in["username"].asString(),in["password"].asString());
            governor.log << "Credentials " << in["username"].asString() << "," << in["password"].asString();
        }
        break;
        case SEND_AES_KEY:
        {
        }
        break;
        case REQUEST_MAP:
        {
            governor.requestMap(connection,in["id"].asInt());
            governor.log << "Request map " << in["id"].asInt();
        }
        break;
        default:
            break;
        }
        governor.log << "|" << std::endl;
    }
    catch(std::exception& e)
    {
        governor.log << "Exception: " << e.what() << std::endl;
    }
}
}
