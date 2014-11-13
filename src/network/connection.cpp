#include "network/connection.hpp"

namespace Ennovia
{

void Connection::async_read(ErrorHandler errorHandler, Handler handler, boost::shared_ptr<Connection> conn)
{
    boost::asio::async_read(ssl_socket_,boost::asio::buffer(inbound_header_,4),
    //boost::asio::async_read(socket_,boost::asio::buffer(inbound_buffer_),
                            boost::bind(&Connection::handle_read_header,
                                        this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred,
                                        boost::make_tuple(errorHandler,handler),conn));
}

void Connection::handle_read_header(const boost::system::error_code& e, size_t bytes_transferred,
                                    boost::tuple<ErrorHandler,Handler> handler, boost::shared_ptr<Connection> conn)
{

    try
    {
        if (e)
        {
            boost::get<0>(handler)(e);
        }
        else
        {
            int sz = inbound_header_[3];
                sz = (sz << 8) | inbound_header_[2];
                sz = (sz << 8) | inbound_header_[1];
                sz = (sz << 8) | inbound_header_[0];
            std::cout << "Size " << sz << std::endl;
            inbound_data_.resize(sz);
            boost::asio::async_read(ssl_socket_,boost::asio::buffer(inbound_data_),
                            boost::bind(&Connection::handle_read,
                                        this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred,
                                        handler,conn));
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Connection::handle_read(const boost::system::error_code& e, size_t bytes_transferred,
                                    boost::tuple<ErrorHandler,Handler> handler, boost::shared_ptr<Connection> conn)

{
    try
    {
        if (!e)
        {
            std::string archive_data(&inbound_data_[0], inbound_data_.size());
            Json::Value value;
            std::cout << archive_data << std::endl;
            if(reader.parse(archive_data,value))
            {
                boost::get<1>(handler)(value);
            }
        }
        boost::get<0>(handler)(e);
    }
    catch(std::exception& e)
    {
        std::cout << "Connection::handle_read_header: " << e.what() << std::endl;
    }
}

void Connection::write_(Json::Value val)
{
    try
    {
        std::string json = writer.write(val);
        std::cout << json.size() << ":" << json << std::endl;
        outbound_data_.resize(HEADER_SIZE);
        int sz = json.size();
        outbound_data_[0] = sz & 255;
        sz >>= 8;
        outbound_data_[1] = sz & 255;
        sz >>= 8;
        outbound_data_[2] = sz & 255;
        sz >>= 8;
        outbound_data_[3] = sz & 255;
        outbound_data_.insert(outbound_data_.end(),json.begin(),json.end());
        //json.copy(&inbound_data_[HEADER_SIZE],json.size());
        boost::asio::async_write(ssl_socket_, boost::asio::buffer(outbound_data_),no_handler());
    }
    catch(std::exception& e)
    {
        std::cout << "Connection::write: " << e.what() << std::endl;
    }
}

}
