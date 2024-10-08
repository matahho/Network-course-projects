#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Client{
public:
    Client (boost::asio::io_context& io_context, std::string host, int port);
    void receive();
private:
    tcp::resolver resolver_;
    tcp::resolver::results_type endpoints_;
    tcp::socket socket_;
};



#endif // CLIENT_H