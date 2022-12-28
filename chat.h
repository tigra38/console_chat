#pragma once
//#include <iostream>
//#include <string>
//#include <memory> 
#include "user.h"
#include "message.h"

template <typename T> class Chat {
private:
    std::vector<Message> _messages;
    std::vector<User> _users;
    User* currentUser = nullptr;

public:
    Chat() = default;
    virtual ~Chat() = default;
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;

    void runChat();
    void userMenu();
    void addUser();
    void addUser(T username, T password);
    void login();
    void logout();
    void showUsersByLogin();
    void setCurrentUser(User* user);
    void getCurrentUser() const;
    
    void createMessage(bool toAll);
    void showMessages(bool toAll);
    void showAllMessagesWith();
    void sentMessages();
};
