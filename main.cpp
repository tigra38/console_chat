﻿#include <iostream>
#include "chat.h"
#include "chat.cpp"



int main() {
    try {
        Chat<std::string> chat;
        chat.runChat();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
