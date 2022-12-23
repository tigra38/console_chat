#pragma once
#include <iostream>
#include <string>
#include <memory> //need to use smart pointers!
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
    void createMessage(); 
    void showUsersByLogin();
    virtual ~Chat();
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;
    void setCurrentuser(User* user);
    void getCurrentuser();
    size_t get_users();
    void addUser();
    void showMessages();
};
