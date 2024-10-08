#include <mutex>
#include "User.cpp"
#include <iostream>
#include <thread>
#include <vector>

class UsersPoll {

public:
    // Add a user to the poll
    void addUser(User* user) {
        const std::lock_guard<std::mutex> lock(mtx);
        users.push_back(user);

    }


    // Logout from the server's userspoll (Went Offline)
    void logOutUser(const std::string& username) {
        User* user = findUserByName(username);
        if (user != nullptr){
            user->setIsOnline(false);
            std::cout << "User" << username << "Logged Out (Went Offline)" << std::endl;
            return ;
        }
        std::cout << "BAD-REQ: No user found by this username " << std::endl;

    }

    // Login from the server's userspoll (Went Online)
    void logInUser(const std::string& username) {
        User* user = findUserByName(username);
        if (user != nullptr){
            user->setIsOnline(true);
            std::cout << "User" << username << "Logger IN (Went Online)" << std::endl;
            return ;
        }
        std::cout << "BAD-REQ: No user found by this username " << std::endl;

    }
    
    bool isUserOnlineToSendCallReq(const std::string& username){
        User* user = findUserByName(username);
        if (user != nullptr){
            return user->isOnline();
        }
        std::cout << "BAD-REQ: No user found by this username " << std::endl;
        return 0 ; 
    }

    bool isThereAnyUserBy(const std::string& username){
        User* user = findUserByName(username);
        if (user == nullptr)
            return false;
        return true; 
    }

    User* findUserByName(const std::string& username){
        for (User* user : users) {
            if (user->getUsername() == username) {
                return user;
            }
        }
        return nullptr;
    }



private :
    std::vector<User*> users;
    mutable std::mutex mtx;


  
};