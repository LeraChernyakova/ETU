
#include "ConsoleLogger.h"

ILogger &ConsoleLogger::operator<<(Message message) {
    std::cout << message.getMessage() << "\n";
//    system("pause");
    return *this;
}
