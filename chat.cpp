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
            cout << "Welcome, " << temp->get_login() << "!" << endl;
            this->setCurrentuser(temp);
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
        std::cout << user.get_login() << std::endl;
}

void Chat::createMessage(std::string From, std::string To, std::string Text) 
{
    std::cout << "Users online:" << std::endl;
    showUsersByLogin();
    std::cout << " Enter addressee login: " << endl;
    std::cin >> To;

/*   for (auto& user : _users)
        if (To != ???)                                                                                  //Как реализовать перебор значений users
        {
            std::cout << "There is no such user.\nSelect user:" << endl;
            showUsersByLogin();
        }
*/

    if (currentUser->get_login() == To)                                                                 //Не отправлять сообщения себе
    {
        std::cout << "You can't send a message to yourself.\nSelect another user:" << endl;
        showUsersByLogin();
    }
    From = currentUser->get_login();

    std::cout << "Write your message, press enter to send: " << endl;
    std::cin >> Text;
    _messages.emplace_back(From, To, Text);
    std::cout << "Message sent." << endl;
    userMenu();
}

void Chat::showMessages()
{
    for (auto& text : _messages)
        if (currentUser->get_login() != text.getFrom())
        {
            std::cout << "<" << text.getFrom() << ">: " << text.getText() << std::endl;
        }
}

void Chat::userMenu()
{
    while (true)
    {
        char user_choice;
        std::cout << "************** User Menu: Choose an option: ***************" << std::endl;
        std::cout << " 1 - Read messages | 2 - Send a message | 3 - Change user / Restart | 0 - Exit" << endl;
        std::cin >> user_choice;
        switch (user_choice)
        {
        case '1':
            showMessages();
            std::cout << "Hit Enter to continue ... " << std::endl;
            (void)getchar();
            // ? returning to level up 
            break;
        case '2':
            createMessage("test_from", "test_to", "test_msg");
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
    bool chat_enable = true;
    while (chat_enable)
    {
        char user_choise;
        std::cout << "*********** Initial Menu: Choose an option: ***************" << std::endl;
        std::cout << "   1 - new user sign-up | 2 - sign-in | 0 - exit" << std::endl;
        std::cin >> user_choise;
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


