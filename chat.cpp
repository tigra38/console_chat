#include "chat.h"
#include "user.h"
#include "message.h"
#include <string>

using namespace std;

Chat::Chat()
{

}

void Chat::setCurrentuser(User* user)
{
    currentUser = user;
}


void Chat::getCurrentuser()
{
    cout << currentUser->get_login() << endl;
}

void Chat::login(){
    string login, password;
    cout << "Sign-in. Enter login:" << endl;
    cin >> login;
    bool success = false;
    User* temp;
    for (auto& user : _users)
    {
        if (user.get_login() == login)
        {
            success = true;
            temp = &user;
            break;
        }
    }
    if (success)
    {
        cout << "Enter password:" << endl;
        cin >> password;
        if (temp->pwdVerify(password))
        {
            cout << "Welcome, " << temp->get_login() << "!" << endl;
            this->setCurrentuser(temp);
            userMenu();
        }
        else
        {
            cout << "Password incorrect!" << endl;
        }
    }
    else
    {
        cout << "No such user!" << endl;
    }
}

void Chat::logout() {
    this->setCurrentuser(nullptr);
}

void Chat::addUser()
{
    string login, password;
    cout << "Sign-up. Enter login:" << endl;
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
void Chat::showMessages()
{
    for (auto& text : _messages)
        if (text.getTo() == currentUser->get_login())
            std::cout << "Message *" << text.getText() 
            << "* from user *" << text.getFrom() << "*"
            << std::endl;
}

void Chat::createMessage() 
{
    std::string from, to, text;
    std::cout << "Users online:" << std::endl;
    showUsersByLogin();
    std::cout << " Enter addressee login: " << endl;
    std::cin >> to;
    from = currentUser->get_login();
    std::cout << "Write your message, press enter to send: " << endl;
    std::cin >> text;
    _messages.emplace_back(from, to, text);
    std::cout << "Message *" << text << "* from user *" << from << "* to user *" << to << "* sent. " << std::endl;
    userMenu();
}

void Chat::userMenu()
{
    while (true)
    {
        char user_choice;
        std::cout << "\033[93m" << "************** User Menu: Choose an option: ***************" << std::endl;
        std::cout << "\033[93m" << " 1 - Read messages | 2 - Send a message | 3 - Change user / Restart | 0 - Exit" << endl;
        std::cin >> user_choice;
        switch (user_choice)
        {
        case '1':
            showMessages();
            std::cout << "Hit Enter to continue ... " << std::endl;
            (void)getchar();
            break;
        case '2':
            createMessage();
            break;
        case '3':
            initialMenu();
            break;
        case '0':
            std::cout << "Exit" << std::endl;
            // ? нужно создать процедуру типа Чат старт = 1 / Чат закрыт = 0 и вставить её сюда
            break;
        default:
            std::cout << "Wrong input. Exit" << std::endl;
            // ? нужно создать процедуру типа Чат старт = 1 / Чат закрыт = 0 и вставить её сюда
        }
    }
}

void Chat::initialMenu()
{
    while (true)
    {
        char user_choise;
        std::cout << "*********** Initial Menu: Choose an option: ***************" << std::endl;
        std::cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << std::endl;
        std::cin >> user_choise;
        std::string lgn;
        std::string pwd;
        switch (user_choise)
        {
        case '1':
            addUser();
            break;
        case '2':
            std::cout << "Existing user sign-in procedure" << std::endl;
            login();
            //this->getCurrentuser(); //for testing login
            break;

        case '0':
            std::cout << "Exit" << std:: endl;
            // ? нужно создать функцию типа Чат старт = 1 / Чат закрыт = 0 и вставить её сюда
            break;

        default:
            std::cout << "Wrong input. Exit" << std::endl;
            // ? нужно создать функцию типа Чат старт = 1 / Чат закрыт = 0 и вставить её сюда
            break;
        }
    }
}

Chat::~Chat()
{

}


