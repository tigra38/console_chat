#pragma once
#include "user.h"
#include "message.h"
#include <vector>

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
    void loginOperation();
    void logoutOperation();
    void showUsersByLogin();
    void setCurrentUser(User* user);
    void getCurrentUser() const;
    
    void createMessage(bool toAll);
    void showMessages(bool toAll);
    void showAllMessagesWith();
    void sentMessages();
};
