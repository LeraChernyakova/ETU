#include "Message.h"

void Message::sortMessages(int number, std::string message, MessageInfo info, Logger* log){
    if ((number==1 && info.getLevel(1)) || (number==2 && info.getLevel(2)) || (number==3 && info.getLevel(3)))
        {log->update(info, message);}
}
