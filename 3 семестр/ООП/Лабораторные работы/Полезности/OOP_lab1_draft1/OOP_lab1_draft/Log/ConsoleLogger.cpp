
#include "ConsoleLogger.h"

ILogger &ConsoleLogger::operator<<(Message message) {
    std::cout << message.get_message() << "\n";
    system("pause");
    return *this;
}
