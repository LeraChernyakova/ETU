#include "FileObject.h"

FileObject::FileObject(){
    file.open("File.txt");
};

FileObject::~FileObject(){
    file.close();
}

Output& FileObject::operator <<(std::string message){
    file<<message<<'\n';
    return *this;
};

void FileObject::changeY(int a){};
