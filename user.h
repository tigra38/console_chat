#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "chat.h"

class User 
{
private:
    //для простоты предлагаю сократить переменные до как указано ниже, без префикса user. 
    //Эти переменные уникальны, нет необходимости в префиксах
    const std::string _login;//АЗ отмечал важность сохранения логина как константы от дальнейш изменений
    std::string _password;
    std::vector<User> _users;//declared here for tests. potential move to chat.h
    
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
    const std::string get_password() { return _password; }
    void showUsers()
    {
        for (auto& user : _users)
            std::cout << user.get_login() << " "
            << user.get_password() << std::endl;
    }
    void addUser()
    {
        std::string lgn;
        std::string pwd;
        std::cout << "Login Password" << std::endl;
        std::cin >> lgn >> pwd;
        _users.emplace_back(lgn, pwd);
    }
      
    void initialMenu()
    {
        while (true)
        {
            char op;
            std::cout << "*********** Choose an option: ***************" << std::endl;
            std::cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << std::endl;
            std::cin >> op;
            std::string lgn;
            std::string pwd;
            switch (op)
            {
            case '1':
                std::cout << "sign-up procedure called" << std::endl;
                std::cout << "Login Password" << std::endl;
                this->addUser();
                //*******************************to add: check for taken login 
                //*******************************to add: password procedure
                std::cout << "user added" << std::endl;//TEST. to be removed
                this->showUsers();//TEST. to be removed
                break;

            case '2':
                std::cout << "Existing user sign-in procedure" << std::endl;
                //return 0;
                break;

            case '0':
                std::cout << "Exit" << std::endl;
                //return 0;
                break;

            default:
                std::cout << "Wrong input. Exit" << std::endl;
                //return 0;
                break;
            }
        }
    }
    
    
};
// 
/*
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
*/