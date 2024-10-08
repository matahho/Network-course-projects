#include <iostream>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>


#include "UsersPoll.cpp"
#include "User.cpp"

#include "rtc/rtc.hpp"
#include "rtc/peerconnection.hpp"
#include "rtc/global.hpp"

#define SOCKET_BUFFER_SIZE 1024
#define IAM "CLIENT"
#define LOGIN "LOGIN"
#define SIGNUP "SIGNUP"



std::atomic_bool running(true);
void signal_handler(int sig) {
    if (sig == SIGINT) {
        running.store(false);
    }
}


class SignalingServer {
public:
    SignalingServer(int port){
        
        port_ = port;


        // Create socket
        socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_ == -1)
            std::cerr << "Failed to create socket" << std::endl;
        


        // Set socket options
        int opt = 1;
        if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) 
            std::cerr << "Failed to set socket options" << std::endl;



        address_.sin_family = AF_INET;
        address_.sin_addr.s_addr = INADDR_ANY;
        address_.sin_port = htons(port_);

        if (bind(socket_, (struct sockaddr *)&address_, sizeof(address_)) == -1)
            std::cerr << "Failed to bind socket" << std::endl;
       

        // Listen for incoming connections
        if (listen(socket_, SOMAXCONN) == -1) 
            std::cerr << "Failed to listen for incoming connections" << std::endl;
        

        // Set signal handler for SIGINT signal
        struct sigaction sig_handler;
        memset(&sig_handler, 0, sizeof(sig_handler));
        sig_handler.sa_handler = signal_handler;
        if (sigaction(SIGINT, &sig_handler, NULL) == -1) {
            std::cerr << "Failed to set signal handler" << std::endl;
        }

        std::cout << "Server started on port " << port << std::endl;

       
    }

    int getSocket(){ return socket_ ;}
    int getPort(){ return port_ ;}
    struct sockaddr_in getAdderss(){ return address_ ;}


    void client_handler(int client_socket){
        std::cout << "Client connected. Socket: " << client_socket << std::endl;
        char client_ip_address[15];
        int client_port_int=-1;
        int client_socket_fd=-1;
        memset(client_ip_address,0,15);
        std::string username;  

        while(running.load()) {

            // Receive messages from the client
            char buffer[SOCKET_BUFFER_SIZE];
            memset(buffer,0,SOCKET_BUFFER_SIZE);
            int num_bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

            if(num_bytes_received<=-0) {
                std::cout<<"terminating server socket corresponds "<<client_socket<<std::endl;
                break;
            }

            if(running.load()==false)  {  
                break;
            }


            std::cout << "Received message from client: " << buffer << std::endl;
            
            if(strncmp(buffer,IAM,6)==0) {
                
                std::cout << "Client ip address and port received\n";
                sscanf(buffer,"CLIENT %s %d",client_ip_address,&client_port_int);

                std::cout << client_ip_address << std::endl;
                std::cout << client_port_int << std::endl;

                if(connect_to_client(client_ip_address, &client_port_int,&client_socket_fd) !=0) {
                    std::cout << "Error connecting to the server\n";
                    break;
                }
                char message[SOCKET_BUFFER_SIZE] = "Hello from new server\n";
                send(client_socket_fd,message,sizeof(message),0);

            }
            else if(strncmp(buffer,LOGIN,5) == 0 ){
                std::cout<< "This is login\n";

                char username_char[50]={0};

                sscanf(buffer,"LOGIN %s",username_char);

                usersPoll.logInUser(std::string(username_char));

                char message[SOCKET_BUFFER_SIZE] = "Login is successful\n";
                send(client_socket,message,sizeof(message),0);    
        
            }
            else if(strncmp(buffer,SIGNUP,6) == 0 ){
                std::cout<< "This is SignUP\n";

                char username_char[50]={0};
                
                sscanf(buffer,"SIGNUP %s",username_char);

                User* newUser = new User(std::string(username_char), client_socket_fd);
                usersPoll.addUser(newUser);

                char message[SOCKET_BUFFER_SIZE] = "Login is successful\n";
                send(client_socket,message,sizeof(message),0);    
        
            }
            else if(strncmp(buffer,"LOGOUT",6)==0) {
               std::cout<< "This is logout\n";

                usersPoll.logOutUser(username);

                char message[SOCKET_BUFFER_SIZE] = "Logout is successful\n";
                send(client_socket,message,sizeof(message),0);             
            
            }
            else if(strncmp(buffer,"EXIT",4)==0) {
                std::cout <<"This is exit\n";
                char message[SOCKET_BUFFER_SIZE] = "Exit is succesful\n";
                if (send(client_socket, message, sizeof(message), 0) == -1) {
                    std::cerr << "Failed to send message to server" << std::endl;
                    break;
                }              
                std::cout << "Client disconnected. Socket: " << client_socket << std::endl;    
                if (send(client_socket_fd, "EXIT", sizeof("EXIT"), 0) == -1) {
                    std::cerr << "Failed to send message to server" << std::endl;
                    break;
                }                 
                break;             
            }
            else if(strncmp(buffer,"CALL",4)==0) {
                std::cout<<"This is call request\n";

                char receiver_username_char[50]={0};
                char first_peer_sdp[SOCKET_BUFFER_SIZE]={0};

                //take senders sdp
                sscanf(buffer,"CALL %s",receiver_username_char);

                int len=4+1+strlen(receiver_username_char)+1; //CALL username 
                strncpy(first_peer_sdp,buffer+len,strlen(buffer)-len);

                std::cout << "First peer sdp\n";
                std::cout << first_peer_sdp << std::endl;
                std::string receiver_username=std::string(receiver_username_char);
                
                //User is not online
                if(!usersPoll.isUserOnlineToSendCallReq(receiver_username)) 
                    std::cout << "The reciever user is not Online" << std::endl;
                
                //user not found, send error message to client
                else if(!usersPoll.isThereAnyUserBy(receiver_username)) 
                    std::cout << "There is no user by this id!" << std::endl;
                
                else {
                    try{
                        User *receiverUser=usersPoll.findUserByName(receiver_username);
                        int receiver_fd=receiverUser->getSocketFd();
                        
                        char message[SOCKET_BUFFER_SIZE*2];
                        memset(message,0,SOCKET_BUFFER_SIZE*2);

                        sprintf(message,"INVITE %s %s",receiver_username_char,first_peer_sdp);

                        std::cout << "Sending message to the receiver\n";
                        std::cout << message << std::endl;
                        send(receiver_fd,message,sizeof(message),0);

                        //wait receiver to send its sdp

                        char incoming_message[SOCKET_BUFFER_SIZE];
                        memset(incoming_message,0,SOCKET_BUFFER_SIZE);

                        recv(receiver_fd,incoming_message,sizeof(incoming_message),0);
                        
                        std::cout << "Receiver's sdp:\n" << std::endl;
                        std::cout << incoming_message << std::endl;

                        char accept_command[50]={0};

                        sscanf(incoming_message,"%s",accept_command);

                        if(strncmp(accept_command,"ACCEPT",6)==0) {
                            //receiver accepted request

                            std::cout << "Forwarding receivers sdp to sender:\n";
                            std::cout << incoming_message << std::endl;
                            //forward it to first sender

                            send(client_socket_fd,incoming_message,sizeof(incoming_message),0);
                            

                        }
                    }
                    catch(std::runtime_error err){
                        err.what();
                    }
                    
                       


                }
            }
        }
    }



private:
    int port_; 
    int socket_; 
    struct sockaddr_in address_;
    UsersPoll usersPoll;

    int connect_to_client(char*client_ip_address,int* client_port_int,int* client_socket_fd) {


        //create socket and connect to client
        *client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (*client_socket_fd == -1) {
            std::cerr << "Failed to create socket" << std::endl;
            return -1;
        }

        // Convert the server address from text to binary form
        struct sockaddr_in client_addr;
        client_addr.sin_family = AF_INET;   
        client_addr.sin_port=htons(*client_port_int);
        if (inet_pton(AF_INET, client_ip_address, &client_addr.sin_addr) != 1) {
            std::cerr << "Invalid client address" << std::endl;
            return -1;
        }

        // Connect to the server
        if (connect(*client_socket_fd, (struct sockaddr*) &client_addr, sizeof(client_addr)) == -1) {
            std::cerr << "Failed to connect to client" << std::endl;
            return -1;
        }
        return 0;
    }


};




int main(int argc, char *argv[]) {

    if(argc!=2) {
        std::cerr << "Usage: " << argv[0] << " <server_port>" << std::endl;
        return 1;        
    }

    SignalingServer server = SignalingServer(std::stoi(argv[1]));


    std::vector<std::thread> threads;

    while (running.load()) {
        // Accept incoming connection
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server.getSocket() , (struct sockaddr *)&client_addr, &client_addr_len);
        
        //if sigint is received
        if(!running.load()) {
            break;
        }

        //error occured on accept
        if (client_socket == -1) {
            std::cerr << "Failed to accept incoming connection" << std::endl;
            break;
        }

        // Create a new thread to handle client request   
        threads.push_back(std::thread(&SignalingServer::client_handler, &server, client_socket));
    
    }

    //wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Close server socket
    close(server.getSocket());
    std::cout << "Server stopped" << std::endl;
    return 0;

}