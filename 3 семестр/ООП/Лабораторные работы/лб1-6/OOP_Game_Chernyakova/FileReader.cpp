#include "FileReader.h"
#include <vector>
#include <algorithm>
#include <sstream>

FileReader::FileReader() {
    defaultCommand();
}

FileReader::FileReader(const std::string& filename) {
    file.open(filename);
    readFile(filename);
}

void FileReader::readFile(const std::string& filename) {
    std::ifstream addfile(filename);
    int count_of_lines = 0;
    if (file.is_open()) {
        std::string line;
        while (std::getline(addfile, line, addfile.widen('\n'))) {
            std::cout << line << '\n';
            ++count_of_lines;
        }
        if (count_of_lines == 8) {
            std::vector<char> list1;
            std::vector<std::string> list2;
            int count = 0;
            while (count < 8) {
                std::string tmp1 = "";
                std::string tmp2 = "";
                std::string tmp3 = "";
                file >> tmp1;
                file >> tmp2;
                file >> tmp3;
                if (tmp1.length() == 1
                    && (tmp3 == "up" || tmp3 == "down" || tmp3 == "left" || tmp3 == "right" || tmp3 == "exit"
                        || tmp3 == "save" || tmp3 == "restart") && (tmp2 == "is" || tmp2 == "=")) {
                    list1.push_back(tmp1[0]);
                    list2.push_back(tmp3);
                }
                else {
                    std::cout
                        << "Violation of the uniqueness of values. Check file content. The control is set by default.\n";
                    defaultCommand();
                }
                std::vector<char> list_1 = list1;
                std::vector<std::string> list_2 = list2;
                std::sort(list1.begin(), list1.end());
                bool u = std::unique(list1.begin(), list1.end()) == list1.end();
                std::sort(list2.begin(), list2.end());
                bool d = std::unique(list2.begin(), list2.end()) == list2.end();
                if (u && d) {
                    setCommand(tmp1[0], tmp3);
                }
                else {
                    std::cout << "Non-unique values. The control is set by default.\n";
                    defaultCommand();
                    break;
                }
                count++;
            }
        }
    }
}
void FileReader::defaultCommand() {
    scheme.insert(std::make_pair('W', Command::move_up));
    scheme.insert(std::make_pair('S', Command::move_down));
    scheme.insert(std::make_pair('A', Command::move_left));
    scheme.insert(std::make_pair('D', Command::move_right));
    scheme.insert(std::make_pair('E', Command::exit));
    scheme.insert(std::make_pair('N', Command::restart));
    scheme.insert(std::make_pair('K', Command::save));
    scheme.insert(std::make_pair('L', Command::load));
}

void FileReader::setCommand(char symb, std::string num) {
    if (num == "up")
        scheme.insert(std::make_pair(symb, Command::move_up));
    else if (num == "down")
        scheme.insert(std::make_pair(symb, Command::move_down));
    else if (num == "left")
        scheme.insert(std::make_pair(symb, Command::move_left));
    else if (num == "right")
        scheme.insert(std::make_pair(symb, Command::move_right));
    else if (num == "exit")
        scheme.insert(std::make_pair(symb, Command::exit));
    else if (num == "save")
        scheme.insert(std::make_pair(symb, Command::restart));
    else if (num == "restart")
        scheme.insert(std::make_pair(symb, Command::save));
    else if (num == "load")
        scheme.insert(std::make_pair(symb, Command::load));
    else
        std::cout << "ErrorThe control is set by default.\n";
    defaultCommand();
}

FileReader::~FileReader() {
    file.close();
}
std::map<char, Command>& FileReader::getScheme() {
    return scheme;
}