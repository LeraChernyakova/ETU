#include "ErrorWriter.h"

void creationError(std::string line)
{
    std::cout << "ERROR: " << line << " not created" << std::endl;
}

void classError(std::string className, std::string error)
{
    std::cout << "ERROR: " << className << " : " << error << std::endl;
}
