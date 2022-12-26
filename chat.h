#pragma once
#include <iostream>
#include <string>
#include <memory> 
#include "user.h"
#include "message.h"

class Chat {
private:
    std::vector<Message> _messages;
    std::vector<User> _users;
    User* currentUser = nullptr;

public:
    Chat() = default;
    virtual ~Chat() = default;
    Chat(Chat& _arr) = delete;
    Chat& operator=(Chat& _list) = delete;

    void initialMenu();
    void userMenu();
    void addUser();
    void addUser(std::string username, std::string password);
    void login();
    void logout();
    void showUsersByLogin() const;
    void setCurrentuser(User* user);
    void getCurrentuser() const;
    
    template <typename T> void createMessage(bool toAll);
    template <typename T> void showMessages(bool toAll) const;
    template <typename T> void showAllMessagesWith() const;
    void sentMessages();
};
