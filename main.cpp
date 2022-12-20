#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"


using namespace std;

int main()
{
    User us;
    us.initialMenu();
    
    
    /*
        while (true)
        {
            char op;
            cout << "*********** Choose an option: ***************" << endl;
            cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << endl;
            cin >> op;

            switch (op)
            {
            case '1':
                cout << "sign-up procedure called" << endl;
                us.addUser();
                //to add: taken login check 
                //to add: password procedure
                cout << "user added" << endl;//TEST. to be removed
                us.showUsers();//TEST. to be removed
                break;

            case '2':
                cout << "Existing user sign-in procedure" << endl;
                return 0;
                break;

            case '0':
                cout << "Exit" << endl;
                return 0;
                break;

            default:
                cout << "Wrong input. Exit" << endl;
                return 0;
                break;
            }
        }
    
    */
          
    
   /*
   Chat* chat1 = new Chat;
   chat1->register_user("login1", "password1", "username1");
   chat1->register_user("login2", "password2", "username2");
   chat1->show_users();
   */
    return 0;
}
