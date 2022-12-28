#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"
#include "chat.cpp"
//#include <chrono>
//#include <ctime>
#include <exception>

//using namespace std;
//using chrono::system_clock;

int main()
{
   
   
    Chat<string> chat1;
    try {
        chat1.initialMenu();
    }
    catch (exception& e) {
        cout << e.what();
    }

    return 0;
}
