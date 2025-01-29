#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <mutex>

using namespace std;

namespace MatrixUtils
{
    void fillMatrix(vector<vector<int>> &matrix){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 50);

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                matrix[i][j] = dist6(rng);
            }
        }
    }

    void multiplyMatricesItem(int i,
                          int j,
                          const vector<vector<int>> &firstMatrix,
                          const vector<vector<int>> &secondMatrix,
                          vector<vector<int>> &resultMatrix)
    {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < firstMatrix.size(); k++) {
                resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
    }

}

void log(const std::string &message)
{
    cout << message << '\n';
}