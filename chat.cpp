/*
#include "chat.h"
#include "user.h"
#include <string>

using namespace std;

Chat::Chat()
{
    userlist = new User*;
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
        delete[] userlist;
        userlist = temp_list;
    }
    userlist[users_num] = new User(login, password, username);
    users_num++;
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
    delete[] userlist;
}

size_t Chat::get_users() {return users_num;}
*/