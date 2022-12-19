#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>

using namespace std;

Chat::Chat()
{
}

void Chat::login_user(std::string login, std::string password)
{
    //if () //проверка существования пользователя и поиск его номера в массиве userlist
    //if () //проверка пароля для логина
    current_user = userlist[0]; //допустим, номер 0
}

void Chat::logout()
{
    if (current_user != nullptr)
    delete current_user;
}

void Chat::register_user(std::string login, std::string password, std::string username)
{
    if (users_num > 0)
    {
        User** temp_list = new User*[users_num+1];
        for (size_t i = 0; i < users_num; ++i)
        {
            temp_list[i] = userlist[i];
        }
        userlist = temp_list;
    }
    userlist[users_num] = new User(login, password, username);
    users_num++;
}

void Chat::create_message(std::string From, std::string To, std::string Text)
{
    if (message_num > 0)
    {
        Message** new_message = new Message*[message_num+1];
        for (size_t i = 0; i < message_num; ++i)
        {
            new_message[i] = messagelist[i];
        }
        messagelist = new_message;
    }
    messagelist[message_num] = new Message(From, To, Text);
    message_num++;
}

void Chat::show_users()
{
    for(size_t i = 0; i < users_num ; ++i)
    {
        cout << userlist[i]->get_login() << " - " << userlist[i]->get_username() << endl;
    }
}

Chat::~Chat()
{
    for(size_t i = 0; i < users_num ; ++i)
    {
        delete[] userlist[i];
    }
    delete userlist;

    for(size_t i = 0; i < message_num ; ++i)
    {
        delete[] messagelist[i];
    }
    delete messagelist;
}

size_t Chat::get_users() {return users_num;}
