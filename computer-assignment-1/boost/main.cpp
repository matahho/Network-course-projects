#include <QCoreApplication>
#include <QDebug>
#include "AudioRecorder.h"
#include "server.h"
#include "client.h"
#include <string>


void run_server(std::string &message){
    boost::asio::io_context io_context;

    Server server(io_context, 8080);
    for (;;)
        server.send(message);
}

void run_client(){
    boost::asio::io_context io_context;
    Client client(io_context , "localhost" , 8080);
    client.receive();

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string audioBuffer;
    AudioSource audioSource;

    QObject::connect(&audioSource, &AudioSource::audioDataTransmit, [&](const std::string& receivedBuffer, qreal audioLevel){
        audioBuffer = receivedBuffer;
    });


    std::thread server_thread(run_server, std::ref(audioBuffer));
    std::thread client_thread(run_client);

    server_thread.join();
    client_thread.join();

    return 0;
}



// int main(int argc, char *argv[])
// {

//     std::cout << "Server is starting" << std::endl;


//     QCoreApplication a(argc, argv);
//     std::string audioBuffer;

//     boost::asio::io_context io_context;
//     Server server(io_context, 8080);


//     AudioSource audioSource;
//     int count = 0 ;
//     QObject::connect(&audioSource, &AudioSource::audioDataTransmit, [&](const std::string& receivedBuffer, qreal audioLevel){
//         audioBuffer = receivedBuffer;
//         server.send(audioBuffer);
//         count ++;

//         if (count == 10){
//             a.exit();
//         }
//     });



//     return a.exec();


// }
