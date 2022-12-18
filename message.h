#pragma once
#include <iostream>
#include <string>


class Message
{
private:
    std::string _mFrom;
    std::string _mTo;
    std::string _mText;
    std::string _mID; // TEST
    int _mTime; //TEST
public:
    Message(std::string From, std::string To, std::string Text);
    Message(std::string From, std::string To, std::string Text, std::string ID); //TEST
    Message(std::string From, std::string To, std::string Text, int Time); //TEST
    void getFrom() const;
    void getTo() const;
    void getMessage() const;
};
