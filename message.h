#pragma once
#include <iostream>
#include <string>


class Message
{
private:
    //уникальные имена переменных для всей программы, предлагается упростить
    const std::string _from;
    const std::string _to;
    const std::string _text;
    /*это фича, имхо. предлагаю пока отложить реализацию
    //std::string _mID; // TEST
    //int _mTime; //TEST*/


public:
    ~Message() {}
    Message(const std::string& from, const std::string& to, const std::string& text) 
        : _from(from), _to(to), _text(text) {}

    const std::string getFrom() { return _from; }
    const std::string getTo() { return _to; }
    const std::string getText() { return _text; }
};
