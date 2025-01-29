#include "output.h"

static std::ofstream fout;

bool openOutputFile() {
    fout = std::ofstream(OUTPUT_FILE);
    if(!fout) {
        std::cout << "Cannot open file " << OUTPUT_FILE << " to write result.";
        return false;
    }

    return true;
}

void writeMatrixToFile(Matrix matrix) {
    int rows = matrix.size(), columns = matrix[0].size();
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            fout << matrix[i][j] << " ";
        }
        fout << "\n";
    }
    fout << "\n";

    return;
}

void closeOutputFile() {
    fout.close();
    return;
}
