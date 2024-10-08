#ifndef __USER
#define __USER

#include <iostream>



class User {
public:
    User(const std::string& username , const std::string& ip, int socket_fd)
        :username_(username),
        ip_(ip),
        socket_fd_(socket_fd),
        isOnline_(0) {}
    
    User(const std::string& username , int socket_fd)
        :username_(username),
        ip_(""),
        socket_fd_(socket_fd),
        isOnline_(0) {}

    std::string getUsername() { return username_; }
    void setUsername(const std::string& username) { username_ = username; }

    std::string getIP() { return ip_; }
    void setIP(const std::string& ip) { ip_ = ip; }

    int getSocketFd() { return socket_fd_; }
    void setSocketFd(int socket_fd) { socket_fd_ = socket_fd; }


    bool isOnline() { return isOnline_; }
    void setIsOnline(bool status) { isOnline_ = status; }

private:
    std::string username_;
    std::string ip_;
    int socket_fd_;
    bool isOnline_;
};

#endif