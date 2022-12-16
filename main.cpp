#include <iostream>
#include <string>
#include "users.h"

using namespace std;

int main()
{
   Users* chat = new Users;
   chat->register_user("login1", "password1", "username1");
   chat->register_user("login2", "password2", "username2");

   chat->show_users();

    return 0;
}
