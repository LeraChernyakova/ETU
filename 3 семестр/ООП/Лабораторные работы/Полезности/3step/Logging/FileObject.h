#pragma once
#include <fstream>
#include "Output.h"

class FileObject: public Output {
    std::ofstream file;
    public:
        FileObject();
        ~FileObject();
        Output& operator <<(std::string message) final;
        void changeY(int a) final;
};

