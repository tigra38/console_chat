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

public:
    Chat();
    void initialMenu();
    void userMenu();
    void login (std::string login, std::string password);
    void logout();
    void createMessage(std::string From, std::string To, std::string Text);
    void showUsersByLogin();
    virtual ~Chat();
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;
    size_t get_users();
    void addUser();
    void showMessages();
};
