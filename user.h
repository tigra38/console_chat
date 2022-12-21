#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include "chat.h"

class User 
{
private:
    //для простоты предлагаю сократить переменные до как указано ниже, без префикса user. 
    //Эти переменные уникальны, нет необходимости в префиксах
    const std::string _login;//АЗ отмечал важность сохранения логина как константы от дальнейш изменений
    std::string _password;
   // std::vector<User> _users;//declared here for tests. potential move to chat.h
    
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
    //const std::string get_password() { return _password; }
};
