//
// Created by mikeasta on 10/30/23.
//
#pragma once
#include "MatrixUtils.h"

namespace ThreadUtils {
    void generateMatrices(
            int leftMatrix[MATRIX_SIZE][MATRIX_SIZE],
            int rightMatrix[MATRIX_SIZE][MATRIX_SIZE]
    ) {
        MatrixUtils::generateMatrix(leftMatrix);
        log("Left matrix generated.");
        MatrixUtils::generateMatrix(rightMatrix);
        log("Right matrix generated.");
    }
}