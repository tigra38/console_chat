#pragma once
#include "message.h"
//#include "sha1.h"
#include <vector>
#include <map>

template <typename T> class Chat {
private:
    std::vector<Message> _messages;
    std::map <std::string, unsigned int*> _usr;
    std::string currentUser = "";

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
    int showUsersByLogin() const;
    void setCurrentUser(const std::string& user);
    void createMessage(bool toAll = false);
    void showMessages(bool toAll = false) const;
    void showAllMessagesWith() const;
    void sentMessages();
    const std::string get_login() { return currentUser; }
};
