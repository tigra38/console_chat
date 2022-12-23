#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"
#include <chrono>
#include <ctime>

using namespace std;
using std::chrono::system_clock;

int main()
{
   system_clock::time_point today = system_clock::now();
   std::time_t tt;
   tt = system_clock::to_time_t(today);
   std::cout << "Today is: " << ctime(&tt);
   
    Chat chat1;
    chat1.initialMenu();
    

    return 0;
}
