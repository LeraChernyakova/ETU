#ifndef COMMON_MATRIX_H
#define COMMON_MATRIX_H

#include <vector>
#include <cstddef>
#include <iosfwd>

namespace ipc
{

class Socket;

} // namespace ipc

namespace common
{

/// @brief Класс матрицы размера rows*columns.
class Matrix final
{
public:
    /// @brief Конструктор класса матрицы.
    /// @details Создается матрица размера rows*columns.
    /// @param[in] rows Количество строк в матрице.
    /// @param[in] columns Количество столбцов в матрице.
    /// @throws std::bad_alloc в случае неудачного выделения памяти.
    Matrix( size_t rows, size_t columns );

    // /// @brief Конструктор копирования.
    // Matrix( const Matrix& other );

    // /// @brief Оператор копирования.
    // Matrix& operator=( const Matrix& other );

    /// @brief Получение количества строк матрицы.
    /// @return Количество строк матрицы.
    inline size_t   rows() const { return rows_; }

    /// @brief Получение количества столбцов матрицы.
    /// @return Количество столбцов матрицы.
    inline size_t   columns() const { return columns_; }

    /// @brief Получение элементов матрицы.
    /// @note Элементы матрицы представлены в виде линейного массива, элементы идут построчно.
    /// @return Массив элементов матрицы. nullptr в случае неудачного выделения памяти.
    inline float*   data() { return data_.data(); }

    /// @brief Получение элементов матрицы.
    /// @note Элементы матрицы представлены в виде линейного массива, элементы идут построчно.
    /// @return Массив элементов матрицы. nullptr в случае неудачного выделения памяти.
    inline const float* data() const { return data_.data(); }

    /// @brief Получение элемента матрицы.
    /// @param[in] row Номер строки.
    /// @param[in] column Номер строки.
    /// @return Значение элемента, расположенного на пересечении строки row и столбца column.
    /// @throws std::out_of_range в случае неверно заданного номера строки или столбца
    float           get( size_t row, size_t column ) const;

    /// @brief Изменение элемента матрицы.
    /// @param[in] row Номер строки.
    /// @param[in] column Номер строки.
    /// @param[in] el Новое значение элемента.
    /// @throws std::out_of_range в случае неверно заданного номера строки или столбца
    void            set( size_t row, size_t column, float el );

    /// @brief Чтение матрицы из потока ввода.
    /// @param[out] matrix Считываемая матрица.
    /// @param[in] stream Поток для чтения.
    /// @return Результат чтения: успех или провал.
    static bool     read( Matrix& matrix, std::istream& stream );

    /// @brief Запись матрицы в поток ввода.
    /// @param[out] matrix Записываемая матрица.
    /// @param[in] stream Поток для записи.
    /// @return Результат записи: успех или провал.
    static bool     write( const Matrix& matrix, std::ostream& stream );

    /// @brief Умножение строки rown матрицы а на столбец coln матрицы b.
    /// @param[in] lhs Умножаемая матрица (левый операнд).
    /// @param[in] rhs Матрица, на которую производится умножение (правый операнд).
    /// @param[in] result Результирующая матрица.
    /// @param[in] row Номер строки lhs.
    /// @param[in] column Номер столбца rhs.
    /// @return Значение элемента - результат умножения.
    /// @throws std::out_of_range в случае неверно заданного номера строки или столбца.
    static float    multiplyRC( const Matrix& lhs, const Matrix& rhs, size_t row, size_t column );

private:
    size_t rows_;               ///< Количество строк в матрице.
    size_t columns_;            ///< Количество столбцов в матрице.
    std::vector< float > data_; ///< Элементы матрицы.
}; // class Matrix

} // namespace common

#endif // COMMON_MATRIX_H
