#include "client.h"

Client::Client(boost::asio::io_context& io_context, std::string host, int listenTo)
    : resolver_(io_context), socket_(io_context) {

    endpoints_ = resolver_.resolve(host , std::to_string(listenTo) );
    boost::asio::connect(socket_, endpoints_);
}

void Client::receive(){
    try{
        for (;;){
            std::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = socket_.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error);
            std::cout.write(buf.data(), len);

        }
    }

    catch (std::exception& e){
        std::cerr << "Exception in receive(): " << e.what() << std::endl;
    }
}
