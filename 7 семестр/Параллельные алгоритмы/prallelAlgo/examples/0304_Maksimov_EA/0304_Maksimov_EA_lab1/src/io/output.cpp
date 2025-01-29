#include "output.h"

void writeMatrixToFile(std::string fileName, Matrix matrix) {
    std::ofstream fout(fileName);
    if(!fout) {
        std::cout << "Cannot open file " << fileName << " to write result.";
        return;
    }

    int rows = matrix.size(), columns = matrix[0].size();
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            fout << matrix[i][j] << " ";
        }
        fout << "\n";
    }

    fout.close();
    return;
}
