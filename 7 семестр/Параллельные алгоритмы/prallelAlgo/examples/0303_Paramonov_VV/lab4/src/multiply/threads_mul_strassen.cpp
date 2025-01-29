#include <thread>

#include "../utils/matrix.h"

using namespace std;


void threadsMulStrassen(Matrix first, Matrix second, Matrix& mulResult, int recursionDepth, int allowRecursionDepth = 3) {
    int half = first.getRows() / 2;

    if (first.getRows() > 2 && recursionDepth < allowRecursionDepth) {
        Matrix first00(half, half), first01(half, half), first10(half, half), first11(half, half);
        Matrix second00(half, half), second01(half, half), second10(half, half), second11(half, half);

        for (int row = 0; row < half; row++) {
            for (int col = 0; col < half; col++) {
                first00[row][col] = first[row][col];
                first01[row][col] = first[row][half + col];
                first10[row][col] = first[half + row][col];
                first11[row][col] = first[half + row][half + col];

                second00[row][col] = second[row][col];
                second01[row][col] = second[row][half + col];
                second10[row][col] = second[half + row][col];
                second11[row][col] = second[half + row][half + col];
            }
        }

        Matrix p1(half, half), p2(half, half), p3(half, half), p4(half, half); 
        Matrix p5(half, half), p6(half, half), p7(half, half);
        if (recursionDepth == 0) {
            vector<thread> p_1_7 = vector<thread>(7);
            p_1_7[0] = thread(threadsMulStrassen, first00 + first11, second00 + second11, ref(p1), recursionDepth + 1, allowRecursionDepth);
            p_1_7[1] = thread(threadsMulStrassen, first10 + first11, second00, ref(p2), recursionDepth + 1, allowRecursionDepth);
            p_1_7[2] = thread(threadsMulStrassen, first00, second01 - second11, ref(p3), recursionDepth + 1,allowRecursionDepth);
            p_1_7[3] = thread(threadsMulStrassen, first11, second10 - second00, ref(p4), recursionDepth + 1, allowRecursionDepth);
            p_1_7[4] = thread(threadsMulStrassen, first00 + first01, second11, ref(p5), recursionDepth + 1, allowRecursionDepth);
            p_1_7[5] = thread(threadsMulStrassen, first10 - first00, second00 + second01, ref(p6), recursionDepth + 1, allowRecursionDepth);
            p_1_7[6] = thread(threadsMulStrassen, first01 - first11, second10 + second11, ref(p7), recursionDepth + 1, allowRecursionDepth); 

            for (int i=0; i < 7; i++) {
                p_1_7[i].join();
            }
        } else {
            threadsMulStrassen(first00 + first11, second00 + second11, ref(p1), recursionDepth + 1, allowRecursionDepth);
            threadsMulStrassen(first10 + first11, second00, ref(p2), recursionDepth + 1, allowRecursionDepth);
            threadsMulStrassen(first00, second01 - second11, ref(p3), recursionDepth + 1, allowRecursionDepth);
            threadsMulStrassen(first11, second10 - second00, ref(p4), recursionDepth + 1, allowRecursionDepth);
            threadsMulStrassen(first00 + first01, second11, ref(p5), recursionDepth + 1, allowRecursionDepth);
            threadsMulStrassen(first10 - first00, second00 + second01, ref(p6), recursionDepth + 1, allowRecursionDepth);
            threadsMulStrassen(first01 - first11, second10 + second11, ref(p7), recursionDepth + 1, allowRecursionDepth); 
        }

        Matrix computed00 = p1 + p4 - p5 + p7;
        Matrix computed01 = p3 + p5;
        Matrix computed10 = p2 + p4;
        Matrix computed11 = p1 - p2 + p3 + p6;
        for (int row = 0; row < half; row++) {
            for (int col = 0; col < half; col++) {
                mulResult[row][col] = computed00[row][col];
                mulResult[row][half + col] = computed01[row][col];
                mulResult[half + row][col] = computed10[row][col];
                mulResult[half + row][half + col] = computed11[row][col];
            }
        }
    } else {
        mulResult = first * second;
    }
}