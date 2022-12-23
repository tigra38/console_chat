#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>
#include <chrono>
#include <ctime>
 
using namespace std;
using chrono::system_clock;

Chat::Chat()
{

}

void Chat::setCurrentuser(User* user)
{
    currentUser = user;
}


void Chat::getCurrentuser()
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

void Chat::addUser()
{
    string login, password;
    cout << "Register new user. Enter login:" << endl;
    cin >> login;
    bool error = true;
    if (login == "") cout << "Вы не ввели данные!" << endl;
    else if (login == "all") cout << "Пользователь all запрещён для использования." << endl;
    else
    {
        error = false;
        for (auto& user : _users)
        {
            if (user.get_login() == login)
            {
                cout << "Пользователь с таким именем уже зарегистрирован";
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

void Chat::showUsersByLogin()
{
    for (auto& user : _users)
        if(user.get_login() != currentUser->get_login())
        cout << user.get_login() << endl;
}

void Chat::createMessage()
{
    string from, to, text;
    time_t timestamp;
    //char ts;
    system_clock::time_point value_t = system_clock::now();
    timestamp = system_clock::to_time_t(value_t);
    cout << "Users online:" << endl;
    showUsersByLogin();
    cout << " Enter addressee login: " << endl;
    cin >> to;
    from = currentUser->get_login();
    cout << "Write your message, press enter to send: " << endl;
    cin >> text;
    _messages.emplace_back(from, to, text, timestamp);
    cout << "Message *" << text << "* from user *" << from << "* to user *" << to << "* sent. " << endl;
    userMenu();
}

void Chat::showMessages()
{
    for (auto& text : _messages)
        if (currentUser->get_login() != text.getFrom() )
        {
            auto x = text.getTime();
            auto y = ctime(&x);
            cout << "Message from <" << text.getFrom() << ">: " << text.getText()
               << "received at " << y << endl;
        }
}

void Chat::userMenu()
{
    while (currentUser != nullptr)
    {
        char user_choice;
        cout << "\033[93m" << "************** User Menu: Choose an option: ***************" << endl;
        cout << "\033[93m" << " 1 - Read messages | 2 - Send a message | 3 - Logout / Return to start" << endl;
        cin >> user_choice;
        cout << endl;
        switch (user_choice)
        {
        case '1':
            showMessages();
            cout << endl;
            cout << "Hit Enter to continue ... " << endl;
            (void)getchar();
            break;
        case '2':
            createMessage();
            break;
        case '3':
            logout();
            break;
        default:
            logout();
            cout << "Wrong input. Return to start" << endl;
        }
    }
}

void Chat::initialMenu()
{
    bool chat_enable = true;
    while (chat_enable)
    {
        char user_choise;
        cout << "*********** Initial Menu: Choose an option: ***************" << endl;
        cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << endl;
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
            cout << "Exit" <<  endl;
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

Chat::~Chat()
{

}


