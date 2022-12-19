#pragma once
#include <iostream>
#include <string>
#include "user.h"
#include "message.h"

class Chat {
private:
    User** userlist = new User*;
    Message** messagelist = new Message*;
    size_t users_num = 0;
    size_t message_num = 0;
    User* current_user;

public:
    Chat();
    void login_user (std::string login, std::string password);
    void logout();
    void register_user(std::string login, std::string password, std::string username);
    void create_message(std::string From, std::string To, std::string Text);
    void show_users();
    virtual ~Chat();
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;
    size_t get_users();
};
