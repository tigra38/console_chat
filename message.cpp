#include "message.h"

Message::Message(std::string From, std::string To, std::string Text) : _mFrom {From}, _mTo {To}, _mText {Text}
{
    _mFrom = From;
    _mTo = To;
    _mText = Text;
}
