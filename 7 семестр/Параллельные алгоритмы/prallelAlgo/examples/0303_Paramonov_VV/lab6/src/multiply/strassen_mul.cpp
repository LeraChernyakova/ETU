#include "multiply.hpp"

using namespace std;
using namespace tbb;


void strassen_mul(Matrix first, Matrix second, Matrix& result, int recursion_depth, int allow_recursion_depth = 3) {
    task_group g;
    int half = first.getRows() / 2;

    if (first.getRows() > 2 && recursion_depth < allow_recursion_depth) {
        Matrix first00(half, half), first01(half, half), first10(half, half), first11(half, half);
        Matrix second00(half, half), second01(half, half), second10(half, half), second11(half, half);

        for (int row = 0; row < half; row++) {
            for (int col = 0; col < half; col++) {
                first00(row, col) = first(row, col);
                first01(row, col) = first(row, half + col);
                first10(row, col) = first(half + row, col);
                first11(row, col) = first(half + row, half + col);

                second00(row, col) = second(row, col);
                second01(row, col) = second(row, half + col);
                second10(row, col) = second(half + row, col);
                second11(row, col) = second(half + row, half + col);
            }
        }

        Matrix p1(half, half), p2(half, half), p3(half, half), p4(half, half); 
        Matrix p5(half, half), p6(half, half), p7(half, half);
        g.run([&] { strassen_mul(first00 + first11, second00 + second11, ref(p1), recursion_depth + 1, allow_recursion_depth); });
        g.run([&] { strassen_mul(first10 + first11, second00, ref(p2), recursion_depth + 1, allow_recursion_depth); });
        g.run([&] { strassen_mul(first00, second01 - second11, ref(p3), recursion_depth + 1,allow_recursion_depth); });
        g.run([&] { strassen_mul(first11, second10 - second00, ref(p4), recursion_depth + 1, allow_recursion_depth); });
        g.run([&] { strassen_mul(first00 + first01, second11, ref(p5), recursion_depth + 1, allow_recursion_depth); });
        g.run([&] { strassen_mul(first10 - first00, second00 + second01, ref(p6), recursion_depth + 1, allow_recursion_depth); });
        g.run([&] { strassen_mul(first01 - first11, second10 + second11, ref(p7), recursion_depth + 1, allow_recursion_depth); }); 

        g.wait();

        Matrix computed00 = p1 + p4 - p5 + p7;
        Matrix computed01 = p3 + p5;
        Matrix computed10 = p2 + p4;
        Matrix computed11 = p1 - p2 + p3 + p6;
        for (int row = 0; row < half; row++) {
            for (int col = 0; col < half; col++) {
                result(row, col) = computed00(row, col);
                result(row, half + col) = computed01(row, col);
                result(half + row, col) = computed10(row, col);
                result(half + row, half + col) = computed11(row, col);
            }
        }
    } else {
        result = first * second;
    }
}