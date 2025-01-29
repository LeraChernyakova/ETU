#include "input.h"

std::vector<int> readInputFile() {
    std::vector<int> inputVector;

    std::ifstream inputFile(INPUT_FILE);

    if (!inputFile) {
        std::cout << "Cannot open file " << INPUT_FILE << " to get parameters.\n";
        return inputVector;
    }

    int inputValue;
    while(inputFile >> inputValue) {
        inputVector.push_back(inputValue);
    }
    
    inputFile.close();
    return inputVector;
}
