#include "input.h"

std::vector<int> readInputFile() {
    std::vector<int> inputVector;

    std::ifstream inputFile(INPUT_FILE);

    if (!inputFile) {
        std::cout << "Cannot open file " << INPUT_FILE << " to get parameters.\n";
        return inputVector;
    }

    for(int i = 0; i < 3; i++) {
        int inputValue;
        inputFile >> inputValue;
        inputVector.push_back(inputValue);
    }

    inputFile.close();
    return inputVector;
}
