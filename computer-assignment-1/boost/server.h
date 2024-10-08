#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, int listenTo);
    void send(std::string message);
private:
    void acceptConnection();


    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

#endif // SERVER_H
