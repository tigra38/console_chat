#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
   Chat* chat1 = new Chat;
   chat1->register_user("login1", "password1", "username1");
   chat1->register_user("login2", "password2", "username2");

   chat1->show_users();

   char pause = '0';
   cout << "¬ведите 0 дл€ выхода: ";
   cin >> pause;
   
    return 0;
}
