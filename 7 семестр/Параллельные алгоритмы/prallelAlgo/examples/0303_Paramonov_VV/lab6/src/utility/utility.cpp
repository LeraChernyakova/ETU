#include "utility.hpp"

using namespace std;


string read_file(const string& file_name) {
    return string(
        (istreambuf_iterator<char>(
            ifstream(file_name).rdbuf()
        )),
        istreambuf_iterator<char>()
    );
}