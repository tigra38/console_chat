#include "users.h"
#include <string>

using namespace std;

User::User(string login, string password, string username) : user_login{login}, user_password{password}, user_username{username}
{
    user_login = login;
    user_password = password;
    user_username = username;
}

User::~User() {
}

string User::show_login() const {return user_login;}

string User::show_username() const {return user_username;}


Users::Users()
{
    userlist = new User*;
}

void Users::register_user(std::string login, std::string password, std::string username)
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

void Users::show_users()
{
    for(size_t i = 0; i < users_num ; ++i)
    {
        cout << userlist[i]->show_login() << " - " << userlist[i]->show_username() << endl;
    }
}

Users::~Users()
{
    for(size_t i = 0; i < users_num ; ++i)
    {
        delete[] userlist[i];
    }
    delete[] userlist;
}

size_t Users::get_users() {return users_num;}
