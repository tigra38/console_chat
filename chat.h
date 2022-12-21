
#pragma once
#include <iostream>
#include <string>
#include <memory> //need to use smart pointers!
#include "user.h"
#include "message.h"

class Chat {
private:

    //std::vector<User> _users;
    //User userlist;
    //size_t users_num = 0;


public:
    /*
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
                std::cin >> lgn >> pwd;
                _users.emplace_back(lgn, pwd);
                //_users.addUser();
                //*******************************to add: taken login check 
                //*******************************to add: password procedure
                std::cout << "user added" << std::endl;//TEST. to be removed
                //_users.showUsers();//TEST. to be removed
                for (auto& user : _users)
                    std::cout << user.get_login() << " "
                    << user.get_password() << std::endl;
                break;

            case '2':
                std::cout << "Existing user sign-in procedure" << std::endl;
                //return 0;
                break;

            case '0':
                std::cout << "Exit" << std:: endl;
                //return 0;
                break;

            default:
                std::cout << "Wrong input. Exit" << std::endl;
                //return 0;
                break;
            }
        }
    }
      */
    /*
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
    */
};
