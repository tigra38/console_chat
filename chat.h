#pragma once
#include <iostream>
#include <string>
#include <memory> 
#include "user.h"
#include "message.h"

class Chat {
private:
    std::vector<Message> _messages;
    std::vector<User> _users;
    User* currentUser = nullptr;

public:
    Chat();
    void initialMenu();
    void userMenu();
    void login();
    void logout();
    void createMessage(bool toAll); 
    void showUsersByLogin();
    virtual ~Chat();
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;
    void setCurrentuser(User* user);
    void getCurrentuser();
    void addUser();
    void addUser(std::string username, std::string password);
    void showMessages(bool toAll);
    void showAllMessagesWith();
    void sentMessages();
};
