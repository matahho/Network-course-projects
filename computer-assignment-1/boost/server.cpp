#include "server.h"
#include <iostream>

Server::Server(boost::asio::io_context& io_context, int port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) , socket_(io_context){
    acceptConnection();
}

void Server::acceptConnection() {
    acceptor_.accept(socket_);
    std::cout << "Client Connected" << std::endl ;

}


void Server::send(std::string message){


    boost::system::error_code ignored_error;
    boost::asio::write(socket_, boost::asio::buffer(message), ignored_error);
    //std::cout << "Message Sent !" << std::endl ;

}
