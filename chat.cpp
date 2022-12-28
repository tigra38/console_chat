#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>
#include <chrono>
#include <ctime>
#include <exception>

using namespace std;
using chrono::system_clock;

class bad_emptylogin : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "Too many empty login!";
    }
};

class bad_password : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "Too many incorrect password!";
    }
};

template <typename T> void Chat<T>::setCurrentUser(User* user)
{
    currentUser = user;
}

template <typename T> void Chat<T>::getCurrentUser() const
{
    if (currentUser != nullptr) {
        cout << currentUser->get_login() << endl;
    }
    else cout << "Nobody logged in" << endl;
}

template <typename T> void Chat<T>::login() {
    T login, password;
    for (size_t i = 0; i < 6; ++i)
    {
        cout << "Sign-in. Enter login:" << endl;
        cin >> login;
        if (login != "") {
            break;
        }
        else if (login == "" && i < 5) {
            cout << "Empty login! Try again! (" << i+1 << "/5)" << endl;
        }
        else throw bad_emptylogin();
    }
    bool success = false;
    User* temp;
    for (auto& user : _users) {
        if (user.get_login() == login) {
            success = true;
            temp = &user;
            break;
        }
    }
    if (success) {
        for (size_t i = 0; i < 6; ++i)
        {
            cout << "Enter password:" << endl;
            cin >> password;
            if (temp->pwdVerify(password)) {
                break;
            }
            else if (!temp->pwdVerify(password) && i < 5) {
                cout << "Incorrect Password! Try again (" << i + 1 << "/5)" << endl;
            }
            else throw bad_password();
        }
            system("cls");
            cout << "Welcome, " << temp->get_login() << "!" << endl;
            this->setCurrentUser(temp);
            cout << endl;
            this->userMenu();

    }
    else {
        cout << "No such user!" << endl;
    }
}

template <typename T> void Chat<T>::logout() {
    this->setCurrentUser(nullptr);
    system("cls");
}

template <typename T> void Chat<T>::addUser()
{
    T login, password;
    cout << "Register new user. Enter login:" << endl;
    cin >> login;
    bool error = true;
    if (login == "") cout << "You didn't enter the data!" << endl;
    else if (login == "all") cout << "The user 'all' is forbidden to use" << endl;
    else
    {
        error = false;
        for (auto& user : _users)
        {
            if (user.get_login() == login)
            {
                cout << "A user with this name is already registered";
                error = true;
                break;
            }
        }
    }
    if (!error)
    {
        cout << "Enter password:" << endl;
        cin >> password;
        _users.emplace_back(login, password);
        cout << "User added." << endl;
    }
}

template <typename T> void Chat<T>::showUsersByLogin()
{
    for (auto& user : _users)
        if (user.get_login() != currentUser->get_login())
            cout << user.get_login() << endl;
}

template <typename T> void Chat<T>::createMessage(bool toAll = false)
{
    T from, to, text;
    //time_t timestamp;
    system_clock::time_point value_t = system_clock::now();
    time_t timestamp = system_clock::to_time_t(value_t);
    if (toAll) {
        to = "all";
    }
    else
    {
        while (1)  {
            cout << "Users online:" << endl;
            showUsersByLogin();
            cout << "Enter recipient login: " << endl;
            cin >> to;
            if (to == currentUser->get_login()) {
                cout << "You can't send a message to yourself" << endl;
            }
            else break;
        }
    }
    from = currentUser->get_login();
    cout << "Write your message, press enter to send: " << endl;
    while (getline(cin, text))
    {
        if (text != "") break;
    }
    _messages.emplace_back(from, to, text, timestamp);
    cout << "Message '" << text << "' from user <" << from << "> to user <" << to << "> sent. " << endl;
    userMenu();
}

template <typename T> void Chat<T>::showMessages(bool toAll = false)
{
    size_t message_num = 0;
    for (auto& text : _messages)
    {
        time_t x = text.getTime();
        //auto y = ctime(&x);
        if (toAll)
        {
            if (text.getTo() == "all") {
                cout << "<" << text.getFrom() << ">: " << "'" << text.getText() << "'" << " received at " << ctime(&x) << endl;
                message_num++;
            }
        }
        else
        {
            if (currentUser->get_login() == text.getTo() && currentUser->get_login() != text.getFrom()) {
                cout << "From <" << text.getFrom() << ">: " << "'" << text.getText() << "'" << " received at " << ctime(&x) << endl;
                message_num++;
            }
        }
    }
    if (!message_num) cout << "No messages" << endl;
}

template <typename T> void Chat<T>::showAllMessagesWith()
{
    T with;
    size_t message_num = 0;
    showUsersByLogin();
    cout << " Enter addressee login: " << endl;
    cin >> with;
    if (currentUser->get_login() == with)
    {
        cout << "You enter your own password" << endl;
    }
    else
    {
        for (auto& text : _messages)
        {
            time_t x = text.getTime();
            //auto y = ctime(&x);
            if (currentUser->get_login() == text.getFrom())
            {
                cout << text.getFrom() << " >>> " << text.getTo() << ": " << text.getText()
                    << " | received at " << ctime(&x) << endl;
                message_num++;
            }
            else if (currentUser->get_login() == text.getTo())
            {
                cout << text.getTo() << " <<< " << text.getFrom() << ": " << text.getText()
                    << " | received at " << ctime(&x) << endl;
                message_num++;
            }
        }
    }
    if (!message_num) cout << "No messages" << endl;
}

template <typename T> void Chat<T>::sentMessages()
{
    for (auto& text : _messages)
        if (currentUser->get_login() == text.getFrom())
        {
            auto x = text.getTime();
            auto y = ctime(&x);
            cout << "Message to <" << text.getTo() << ">: " << "'" << text.getText() << "'"
                << " received at " << y << endl;
        }
}

template <typename T> void Chat<T>::userMenu()
{
    while (currentUser != nullptr)
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
        case '7':
            logout();
            break;
        default:
            logout();
            cout << "Wrong input. Return to start" << endl;
        }
    }
    cout << endl;
}

template <typename T> void Chat<T>::runChat()
{
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
            login();
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
