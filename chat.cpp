#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>
#include <chrono>
#include <ctime>
 
using namespace std;
using std::chrono::system_clock;

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
            std::cout << endl;
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
    std::cout << "User added." << std::endl;
    }
}

void Chat::showUsersByLogin()
{
    for (auto& user : _users)
        if(user.get_login() != currentUser->get_login())
        std::cout << user.get_login() << std::endl;
}


void Chat::createMessage()
{
    std::string from, to, text;
    std::time_t timestamp;
    //char ts;
    system_clock::time_point value_t = system_clock::now();
    timestamp = system_clock::to_time_t(value_t);
    std::cout << "Users online:" << std::endl;
    showUsersByLogin();
    std::cout << " Enter addressee login: " << endl;
    std::cin >> to;
    from = currentUser->get_login();
    std::cout << "Write your message, press enter to send: " << endl;
    std::cin >> text;
    _messages.emplace_back(from, to, text, timestamp);
    std::cout << "Message *" << text << "* from user *" << from << "* to user *" << to << "* sent. " << std::endl;
    userMenu();
}

void Chat::showMessages()
{
    for (auto& text : _messages)
        if (currentUser->get_login() != text.getFrom() )
        {
            auto x = text.getTime();
            auto y = ctime(&x);
            std::cout << "Message from <" << text.getFrom() << ">: " << text.getText() 
               << "received at " << y << std::endl;
        }
}

void Chat::userMenu()
{
    while (currentUser != nullptr)
    {
        char user_choice;
        std::cout << "\033[93m" << "************** User Menu: Choose an option: ***************" << std::endl;
        std::cout << "\033[93m" << " 1 - Read messages | 2 - Send a message | 3 - Logout / Return to start" << endl;
        std::cin >> user_choice;
        std::cout << endl;
        switch (user_choice)
        {
        case '1':
            showMessages();
            std::cout << endl;
            std::cout << "Hit Enter to continue ... " << std::endl;
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
            std::cout << "Wrong input. Return to start" << std::endl;
        }
    }
}

void Chat::initialMenu()
{
    bool chat_enable = true;
    while (chat_enable)
    {
        char user_choise;
        std::cout << "*********** Initial Menu: Choose an option: ***************" << std::endl;
        std::cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << std::endl;
        std::cin >> user_choise;
        std::cout << endl;

        switch (user_choise)
        {
        case '1':
            addUser();
            break;
        case '2':
            login();
            break;
        case '0':
            std::cout << "Exit" << std:: endl;
            chat_enable = false;
            break;
        default:
            std::cout << "Wrong input. Exit" << std::endl;
            chat_enable = false;
            break;
        }
    }
    cout << "Chat session terminated! See you again!" << endl;
}

Chat::~Chat()
{

}


