#include "input.h"

std::vector<int> readRow(std::ifstream* inputFile) {
    std::vector<int> row;
    std::string line;
    std::getline(*inputFile, line);

    if(!line.empty()) {
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            row.push_back(num);
        }
    }

    return row;
}

Matrix readMatrix(std::ifstream* inputFile) {
    Matrix matrix;
    std::vector<int> row;

    row = readRow(inputFile);
    while (row.size() > 0) {
        matrix.push_back(row);
        row = readRow(inputFile);
    }

    return matrix;
}

void readMatricesFromFile(std::string fileName, std::vector<Matrix>* matricesPointer) {
    std::ifstream inputFile(fileName);

    if (!inputFile) {
        std::cout << "Cannot open file " << fileName << " to get matrices.\n";
        return;
    }

    for(int i = 0; i < 2; i++)
        (*matricesPointer).push_back(readMatrix(&inputFile));

    inputFile.close();
    return;
}

bool isCorrectMatricesInput(std::vector<Matrix> matrices) {
    if(matrices.size() == 0) {
        std::cout << "Matrices not found.\n";
        return false;
    }
    if(matrices.size() != 2) {
        std::cout << "Incorrect amount of input matrices (required 2, got " << matrices.size() << ").\n";
        return false;
    }

    for(int i = 0; i < 2; i++) {
        if((matrices[i].size() == 0)) {
            std::cout << "Incorrect matrix input.\n";
            return false;
        }
        unsigned int rows = matrices[i].size(), columns = matrices[i][0].size();
        for(unsigned int j = 1; j < rows; j++) {
            if(matrices[i][j].size() != columns) {
                std::cout << "Incorrect matrix dimensions (#" << i+1 << ").\n";
                return false;
            }
        }
    }

    if(matrices[0][0].size() != matrices[1].size()) {
        std::cout << "Matrices are incompatible (" 
            << matrices[0].size() << "x" << matrices[0][0].size() << ", "
            << matrices[1].size() << "x" << matrices[1][0].size() << ").\n";
        return false;
    }

    return true;
}
