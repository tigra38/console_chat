#pragma once
#include <iostream>
#include <string>

class User {

private:
    std::string user_login;
    std::string user_password;
    std::string user_username;

public:
    User();
    User(std::string login, std::string password, std::string username);
    virtual ~User();
    User(User& _arr) = delete;
    User& operator=(User& _list) = delete;

    std::string show_login() const;
    std::string show_username() const;
    void set_username(std::string login);
    void change_password(std::string login);
};

class Users {
private:
    User** userlist;
    size_t users_num = 0;

public:
    Users();
    void register_user(std::string login, std::string password, std::string username);
    void show_users();
    virtual ~Users();
    Users(Users& _arr) = delete;
    Users& operator=(Users& _list) = delete;
    size_t get_users();
};
