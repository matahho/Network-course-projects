#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


void write_server (std::string message){
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8081));

    tcp::socket socket(io_context);
    acceptor.accept(socket);
    
    
    boost::system::error_code ignored_error;
    boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

}

void read_client(){
    sleep(2);
    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints = resolver.resolve("localhost", "8080");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    int counter = 0;
    for (;;){
        std::array<char, 128> buf;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
          break; // Connection closed cleanly by peer.
        else if (error)
          throw boost::system::system_error(error); // Some other error.

        std::cout.write(buf.data(), len);
        counter++;   
    }
}
    

int main()
{
    std::thread server_thread (write_server, "Hello thread1");
    std::thread client_thread (read_client);
    
    server_thread.join();
    client_thread.join();

    return 0;
}
