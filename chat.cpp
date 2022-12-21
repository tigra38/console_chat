#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>

using namespace std;

Chat::Chat()
{

}

void Chat::login(std::string login, std::string password){}

void Chat::logout() {}

void Chat::addUser()
{
    string login, password;
    cout << "Sign-up. Enter login:" << endl;
    cin >> login;
    bool error = true;
    if (login == "") cout << "Вы не ввели данные!" << endl;
    else if (login == "all") cout << "Пользователь all запрещён для использования." << endl;
    else
    {
        error = false;
        for (auto& user : _users)
        {
            if (user.get_login() == login)
            {
                cout << "Пользователь с таким именем уже зарегистрирован";
                error = true;
                break;
            }
        }
    }
    if (!error)
    {
    cout << "Enter password:" << endl;
    cin >> password;
    _users.emplace_back(login, password);
    std::cout << "User added." << std::endl;
    }
}

void Chat::showUsers()
{
    for (auto& user : _users)
        std::cout << user.get_login() << std::endl;
}

void Chat::create_message(std::string From, std::string To, std::string Text) {}

void Chat::initialMenu()
{
    while (true)
    {
        char user_choise;
        std::cout << "*********** Choose an option: ***************" << std::endl;
        std::cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << std::endl;
        std::cin >> user_choise;
        std::string lgn;
        std::string pwd;
        switch (user_choise)
        {
        case '1':
            addUser();
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

Chat::~Chat()
{

}


