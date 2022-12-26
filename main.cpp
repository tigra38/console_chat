#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"
#include "chat.cpp"
#include <chrono>
#include <ctime>
#include <exception>

using namespace std;
using chrono::system_clock;

int main()
{
   system_clock::time_point today = system_clock::now();
   time_t tt;
   tt = system_clock::to_time_t(today);
   cout << "Today is: " << ctime(&tt);
   
    Chat<string> chat1;
    try {
        chat1.addUser("test1", "123");
        chat1.addUser("test2", "123");
        chat1.addUser("test3", "123");
        chat1.initialMenu();
    }
    catch (exception& e) {
        cout << e.what();
    }

    return 0;
}
