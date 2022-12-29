#pragma once
#include <iostream>
#include <string>


class User 
{
private:
    const std::string _login;
    std::string _password;
    
public:
    User() = default;
    User(const std::string& login, const std::string& password)
        : _login(login), _password(password) {}
    virtual ~User() = default;
    const std::string get_login() { return _login; }
    bool pwdVerify(const std::string& password) const {
        if (password == _password)
            return true;
        return false;
    }
    
};
