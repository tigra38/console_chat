#include <iostream>
#include <string>
#include "user.h"
#include "chat.h"
#include "chat.cpp"
#include <exception>



int main()
{
    
    try {
        Chat<string> chat;
        chat.runChat();
    }
    catch (exception& e) {
        cout << e.what();
    }

    return 0;
}
