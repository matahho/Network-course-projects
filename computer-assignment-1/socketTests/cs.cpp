#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <unistd.h>
using boost::asio::ip::tcp;




int run_server(int port , std::string message){
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

    tcp::socket socket(io_context);
    acceptor.accept(socket);


    boost::system::error_code ignored_error;
    int count = 0;

    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

    return 0 ;
}



int client(int port  , std::string address){
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints = resolver.resolve(address, std::to_string (port));

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    std::array<char, 128> buf;
    boost::system::error_code error;

    size_t len = socket.read_some(boost::asio::buffer(buf), error);

    std::cout.write(buf.data(), len);
   
    return 0 ; 
}


int main (int argc , char* argv[]){

    int porta = 8080;
    int portb = 8080;
    
    std::string message = "Test mahdi " + std::to_string (portb);

    std::thread server_thread (run_server , porta , message);

    std::thread client_thread (client , portb , "localhost");

    
    server_thread.join();
    client_thread.join();



}
