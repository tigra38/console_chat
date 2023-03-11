#include "chat.h"
#include "message.h"
#include "sha1.h"
#include <string>
#include <chrono>
#include <ctime>
#include <exception>

using namespace std;
using chrono::system_clock;

class bad_login : public exception {
public:
    const char* what() const noexcept override
    {
        return "Too many failed login attempts!";
    }
};

class bad_password : public exception {
public:
    const char* what() const noexcept override
    {
        return "too many bad password attempts!";
    }
};

template <typename T> void Chat<T>::setCurrentUser(const std::string& user) {
    currentUser = user;
}

template <typename T> void Chat<T>::getCurrentUser() const {
    if (!currentUser.empty()) {
        cout << currentUser->get_login() << endl;
    }
    else cout << "Nobody logged in" << endl;
}

template <typename T> bool Chat<T>::pwdVerify(const std::string& password) const {
    unsigned int* digest = sha1((char* )password.data(), password.size());

    bool cmpHashes = !memcmp(
        data[i].pass_sha1_hash,
        digest,
        SHA1HASHLENGTHBYTES);
    delete[] digest;
    return cmpHashes;
}


template <typename T> void Chat<T>::loginOperation() {
    T login, password;
    map<std::string, unsigned int *>::iterator it;
    
    for (size_t try_num = 0; try_num < 6; ++try_num)
    {
        cout << "Sign-in. Enter login:" << endl;
        cin >> login;
        if (login != "") {
            break;
        }
        if (login == "" && try_num < 5) {
            cout << "Empty login! Try again! (" << try_num + 1 << "/5)" << endl;
        }
        else throw bad_login();
    }
    bool success = false;

    it = _usr.find(login);
    if (it != _usr.end()) {
        success = true;
    }

    if (success) {
        for (size_t try_num = 0; try_num < 6; ++try_num)
        {
            cout << "Enter password:" << endl;
            cin >> password;
            if (!memcmp(it->second, sha1((char*)password.data(), sizeof(password) - 1), SHA1HASHLENGTHBYTES)) {
                break;
            }

            if (try_num < 5) {
                cout << "Incorrect Password! Try again (" << try_num + 1 << "/5)" << endl;
            }
            else throw bad_password();

        }
            system("cls");
            cout << "Welcome, " << it->first << "!" << endl;
            this->setCurrentUser(it->first);
            cout << endl;
            this->userMenu();
    }
    else {
        cout << "No such user!" << endl;
    }
}

template <typename T> void Chat<T>::logoutOperation() {
    this->setCurrentUser("");
    system("cls");
}

template <typename T> void Chat<T>::addUser() {
    T login, password;
    cout << "Register new user. Enter login:" << endl;
    cin >> login;
    bool error = true;
    if (login == "") cout << "You didn't enter the data!" << endl;
    else if (login == "all") cout << "The user 'all' is forbidden to use" << endl;
    else
    {
        error = false;
        map<std::string, unsigned int*>::iterator it = _usr.find(login);
        if (it != _usr.end()) {
            cout << "A user with this name is already registered!" << endl;
            error = true;
        }
    }
    if (!error)
    {
        cout << "Enter password:" << endl;
        cin >> password;
        _usr.emplace(make_pair(login, sha1((char*)password.data(), sizeof(password) - 1)));
        cout << "User added." << endl;
        unsigned int* digest = sha1((char*)password.data(), sizeof(password) - 1);
        cout << endl;
        delete[] digest;
    }
}

template <typename T> int Chat<T>::showUsersByLogin() const{
    cout << "Users list:" << endl;
    int num_users = 0;
    for (const auto& it : _usr)
    {
        if (it.first != currentUser) {
            cout << it.first << endl;
            num_users++;
        }
    }
    if (!num_users) cout << "No another users" << endl;        
    cout << endl;
    return num_users;
}

template <typename T> void Chat<T>::createMessage(bool toAll = false) {
    T from, to = "", text;
    system_clock::time_point value_t = system_clock::now();
    time_t timestamp = system_clock::to_time_t(value_t);
    if (toAll) {
        to = "all";
    }
    else if (showUsersByLogin())
    {
        while (1)  {
            cout << "Enter recipient login: " << endl;
            cin >> to;
            if (to == currentUser) {
                cout << "You can't send a message to yourself" << endl;
            }
            else if (_usr.find(to) == _usr.end())
            {
                cout << "No such user" << endl;
            }
            else break;
        }
    }
    if (!to.empty())
    {
        from = currentUser;
        cout << "Write your message, press enter to send: " << endl;
        while (getline(cin, text))
        {
            if (text != "") break;
        }
        _messages.emplace_back(from, to, text, timestamp);
        cout << "Message '" << text << "' from user <" << from << "> to user <" << to << "> sent. " << endl;
        userMenu();
    }
}

template <typename T> void Chat<T>::showMessages(bool toAll = false) const {
    cout << "New messages: " << endl;
    size_t message_num = 0;
    for (auto& text : _messages)
    {
        time_t x = text.getTime();
        if (toAll)
        {
            if (text.getTo() == "all") {
                cout << "<" << text.getFrom() << ">: " << "'" << text.getText() << "'" << " received at " << ctime(&x) << endl;
                message_num++;
            }
        }
        else
        {
            if (currentUser == text.getTo() && currentUser != text.getFrom()) {
                cout << "From <" << text.getFrom() << ">: " << "'" << text.getText() << "'" << " received at " << ctime(&x) << endl;
                message_num++;
            }
        }
    }
    if (!message_num) {
        if (toAll) cout << "No broadcast messages" << endl;
        else cout << "No messages" << endl;
    }
        
}

template <typename T> void Chat<T>::showAllMessagesWith() const {

    T with;
    size_t message_num = 0;
    if (showUsersByLogin()) {
        cout << " Enter addressee login: " << endl;
        cin >> with;
        if (currentUser == with)
        {
            cout << "You enter your own login" << endl;
        }
        else
        {
            for (auto& text : _messages)
            {
                time_t x = text.getTime();
                if (with == text.getTo() && currentUser == text.getFrom())
                {
                    cout << text.getFrom() << " >>> " << text.getTo() << ": " << text.getText()
                        << " | received at " << ctime(&x) << endl;
                    message_num++;
                }
                else if (with == text.getFrom() && currentUser == text.getTo())
                {
                    cout << text.getTo() << " <<< " << text.getFrom() << ": " << text.getText()
                        << " | received at " << ctime(&x) << endl;
                    message_num++;
                }
            }
        }
        if (!message_num) cout << "No messages with user " << with << endl;
    }
}

template <typename T> void Chat<T>::sentMessages() {
    int num_messages = 0;
    for (auto& text : _messages) {
        if (currentUser == text.getFrom())
        {
            auto x = text.getTime();
            auto y = ctime(&x);
            cout << "Message to <" << text.getTo() << ">: " << "'" << text.getText() << "'"
                << " received at " << y << endl;
            num_messages++;
        }
    }
    if (!num_messages) cout << "No sent messages" << endl;
}

template <typename T> void Chat<T>::userMenu(){
    while (!currentUser.empty())
    {
        char user_choice;
        cout << endl;
        cout << "\033[93m" << "************** User Menu: Choose an option: ***************" << endl;
        cout << "\033[93m" << "1 - Read new messages | 2 - Read messages with... | 3 - Read broadcast messages" << endl;
        cout << "\033[93m" << "4 - Send a message | 5 - Send a broadcast message | 6 - View sent messages" << endl;
        cout << "\033[93m" << "0 - Logout / Return to start" << endl;
        cin >> user_choice;
        cout << endl;
        switch (user_choice)
        {
        case '1':
            showMessages(false);
            break;
        case '2':
            showAllMessagesWith();
            break;
        case '3':
            showMessages(true);
            break;
        case '4':
            createMessage(false);
            break;
        case '5':
            createMessage(true);
            break;
        case '6':
            sentMessages();
            break;
        case '0':
            logoutOperation();
            break;
        default:
            logoutOperation();
            cout << "Wrong input. Return to start" << endl;
        }
    }
    cout << endl;
}

template <typename T> void Chat<T>::runChat() {
    bool chat_enable = true;
    while (chat_enable)
    {
        system_clock::time_point today = system_clock::now();
        time_t tt;
        tt = system_clock::to_time_t(today);
        cout << "Today is: " << ctime(&tt);
        char user_choise;
        cout << "\033[0m" << "*********** Initial Menu: Choose an option: ***************" << endl;
        cout << "\033[0m" << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << endl;
        cin >> user_choise;
        cout << endl;

        switch (user_choise)
        {
        case '1':
            addUser();
            break;
        case '2':
            loginOperation();
            break;
        case '0':
            cout << "Exit" << endl;
            chat_enable = false;
            break;
        default:
            cout << "Wrong input. Exit" << endl;
            chat_enable = false;
            break;
        }
    }
    cout << "Chat session terminated! See you again!" << endl;
}