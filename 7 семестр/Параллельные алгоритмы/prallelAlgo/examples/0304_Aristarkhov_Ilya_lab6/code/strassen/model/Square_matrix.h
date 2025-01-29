#ifndef PA_LAB_2_SQUARE_MATRIX_H
#define PA_LAB_2_SQUARE_MATRIX_H

#include <vector>

class Square_matrix {
private:
    std::vector<std::vector<int>> matrix;
    int size;
public:
    explicit Square_matrix(int size);

    void set_data(int value, int i, int j);
    int get_data(int i, int j) const;

    int get_size() const;
};

Square_matrix operator+(const Square_matrix &first, const Square_matrix &second);
Square_matrix operator-(const Square_matrix &first, const Square_matrix &second);
bool operator==(const Square_matrix &first, const Square_matrix &second);

#endif //PA_LAB_2_SQUARE_MATRIX_H
