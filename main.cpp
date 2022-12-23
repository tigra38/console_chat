#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"
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
   
    Chat chat1;
    try {
        chat1.initialMenu();
    }
    catch (exception& e) {
        cout << e.what();
    }

    return 0;
}
