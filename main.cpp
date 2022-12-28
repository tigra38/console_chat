#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"
#include "chat.cpp"
#include <exception>



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
