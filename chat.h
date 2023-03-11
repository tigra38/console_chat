#pragma once
#include "message.h"
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
    void getCurrentUser() const;
    
    void createMessage(bool toAll);
    void showMessages(bool toAll) const;
    void showAllMessagesWith() const;
    void sentMessages();
    bool pwdVerify(const std::string& password) const;
    const std::string get_login() { return currentUser; }
};
