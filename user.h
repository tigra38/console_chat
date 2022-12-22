#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "chat.h"

class User 
{
private:
    const std::string _login;
    std::string _password;
    
public:
    User() = default;
    User(std::string login, std::string password)
        : _login(login), _password(password) {}
    virtual ~User() {}
    //User(User& _arr) = delete;
    //User& operator=(User& _list) = delete;
    
    void set_login(const std::string login) {}
    void set_password(std::string password) {}
    const std::string get_login() { return _login; }
    bool pwdVerify(std::string password) {
        if (password == _password)
            return true;
        else return false;
    }
    //const string get_password() { return _password; } //unsafe function!
};
