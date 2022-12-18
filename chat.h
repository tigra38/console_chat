#pragma once
#include <iostream>
#include <string>

class Chat {
private:
    User** userlist;
    size_t users_num = 0;

public:
    Chat();
    void register_user(std::string login, std::string password, std::string username);
    void show_users();
    virtual ~Chat();
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;
    size_t get_users();
};
