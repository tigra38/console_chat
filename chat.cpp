#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
using chrono::system_clock;

void Chat::setCurrentuser(User* user)
{
    currentUser = user;
}

void Chat::getCurrentuser() const
{
    if (currentUser != nullptr) {
        cout << currentUser->get_login() << endl;
    }
    else cout << "Nobody logged in" << endl;
}

void Chat::login() {
    string login, password;
    cout << "Sign-in. Enter login:" << endl;
    cin >> login;
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
        cout << "Enter password:" << endl;
        cin >> password;
        if (temp->pwdVerify(password)) {
            system("cls");
            cout << "Welcome, " << temp->get_login() << "!" << endl;
            this->setCurrentuser(temp);
            cout << endl;
            this->userMenu();
        }
        else {
            cout << "Password incorrect!" << endl;
        }
    }
    else {
        cout << "No such user!" << endl;
    }
}

void Chat::logout() {
    this->setCurrentuser(nullptr);
    system("cls");
}

void Chat::addUser(string username, string password)
{
    _users.emplace_back(username, password);
}

void Chat::addUser()
{
    string login, password;
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

void Chat::showUsersByLogin() const
{
    for (auto& user : _users)
        if (user.get_login() != currentUser->get_login())
            cout << user.get_login() << endl;
}

template <typename T> void Chat::createMessage(bool toAll = false)
{
    string from, to, text;
    time_t timestamp;
    system_clock::time_point value_t = system_clock::now();
    timestamp = system_clock::to_time_t(value_t);
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

template <typename T> void Chat::showMessages(bool toAll = false) const
{
    size_t message_num = 0;
    for (auto& text : _messages)
    {
        auto x = text.getTime();
        auto y = ctime(&x);
        if (toAll)
        {
            if (text.getTo() == "all") {
                cout << "<" << text.getFrom() << ">: " << "'" << text.getText() << "'" << " received at " << y << endl;
                message_num++;
            }
        }
        else
        {
            if (currentUser->get_login() == text.getTo() && currentUser->get_login() != text.getFrom()) {
                cout << "From <" << text.getFrom() << ">: " << "'" << text.getText() << "'" << " received at " << y << endl;
                message_num++;
            }
        }
    }
    if (!message_num) cout << "No messages" << endl;
}

template <typename T> void Chat::showAllMessagesWith() const
{
    string with;
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
            auto x = text.getTime();
            auto y = ctime(&x);
            if (currentUser->get_login() == text.getFrom())
            {
                cout << text.getFrom() << " >>> " << text.getTo() << ": " << text.getText()
                    << " | received at " << y << endl;
                message_num++;
            }
            else if (currentUser->get_login() == text.getTo())
            {
                cout << text.getTo() << " <<< " << text.getFrom() << ": " << text.getText()
                    << " | received at " << y << endl;
                message_num++;
            }
        }
    }
    if (!message_num) cout << "No messages" << endl;
}

void Chat::sentMessages()
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

void Chat::userMenu()
{
    while (currentUser != nullptr)
    {
        char user_choice;
        cout << endl;
        cout << "\033[93m" << "************** User Menu: Choose an option: ***************" << endl;
        cout << "\033[93m" << "1 - Read new messages | 2 - Read messages with... | 3 - Read broadcast messages" << endl;
        cout << "\033[93m" << "4 - Send a message | 5 - Send a broadcast message | 6 - View sent messages" << endl;
        cout << "\033[93m" << "7 - Logout / Return to start" << endl;
        cin >> user_choice;
        cout << endl;
        switch (user_choice)
        {
        case '1':
            showMessages();
            break;
        case '2':
            showAllMessagesWith();
            break;
        case '3':
            showMessages(true);
            break;
        case '4':
            createMessage();
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

void Chat::initialMenu()
{
    bool chat_enable = true;
    while (chat_enable)
    {
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
