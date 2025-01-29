#include "model/MultiplicationMatrix.h"

void testing(std::function<void()>& fun, std::string str){


}

int main() {
    std::vector<int> sizes = {64, 128, 256, 512, 1024};
    std::vector<int> threads = {4, 8, 10, 15};
    int thread = 14;
    for (auto& size: sizes) {
        std::cout << "------------------------------"<<std::endl;
        Matrix left = Matrix::generate(size);
        Matrix right = Matrix::generate(size);
        MultiplicationMatrix m = MultiplicationMatrix::create(left, right);
        std::cout << "Matrix size: " << size << "x" << size << std::endl;
        auto start = std::chrono::steady_clock::now();
        m.multiplyParallel(thread);
        auto end = std::chrono::steady_clock::now();
        std::cout << "lr1 " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
        start = std::chrono::steady_clock::now();
        m.multiplyScalable(thread);
        end = std::chrono::steady_clock::now();
        std::cout << "scallable " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
        start = std::chrono::steady_clock::now();
        m.multiplyStrassen();
        end = std::chrono::steady_clock::now();
        std::cout << "strassen " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
    }

    return 0;
}
