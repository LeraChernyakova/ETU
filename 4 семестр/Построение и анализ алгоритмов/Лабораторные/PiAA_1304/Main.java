package lab1;

import java.util.Scanner;

import static java.lang.Math.min;

/*
 *Класс хранения и обработки квадрата
 * Требует на вход требует сторону квадрата,
 * внутри разбивает квадрат на меньшие минимальное число квадратов меньшего размера
 * и хранит это разбиение
 */
class SquarePuzzle {
    //размер матрицы, минимальный простой делитель переданного в конструктор числа n
    private short p;
    private int step;
    private int[][] square;
    private int count = 0;
    private int[][] squareTmp;
    private int minCount;

    /*
     * Конструктор квадрата
     * Находит минимальный делитель и шаг, запускает алгоритм поиска оптимального разрезания
     */
    public SquarePuzzle(short n) {
        p = n;
        step = 1;
        for (short i = 2; i <= p / 2; i++) {
            if (p % i == 0) {
                step = p / i;
                p = i;
                break;
            }
        }
        square = new int[p][p];
        squareTmp = new int[p][p];

        minCount = p * p;
        puzzle();
    }

    /*
     * Запуск разрезания квадрата
     * добавление начальных квадратов, проверка случая p=2, запуск бэктрекинга
     */
    void puzzle() {
        int tmp = p / 2 + p % 2;
        addSquare(0, 0, tmp);
        addSquare(0, tmp, p - tmp);
        addSquare(tmp, 0, p - tmp);
        if (p == 2) {
            addSquare(tmp, tmp, p - tmp);
            minCount = count;
            return;
        }
        backtracking(p / 2, p / 2, p);
        square = squareTmp;
    }

    /*
     * Поиск следующего квадрата и сохранение результата при необходимости
     */
    private void backtrackHelper(int startA, int startB, int end, int k) {
        if (startB + k < end) {
            backtracking(startA, startB + k, end);
        } else {
            if (startA + 1 < end) {
                backtracking(startA + 1, p / 2, end);
            } else {
                minCount = count;
                cloneTmp();
            }
        }
    }

    /*
     * Нахождение оптимального разрезания квадрата с помощью бэктрекинга
     */
    void backtracking(int startA, int startB, int end) {
        int maxSize = min(end - startA, end - startB);
        if (minCount <= count) {
            return;
        }
        if (square[startA][startB] == 0) {
            for (int k = maxSize; k >= 1; k--) {
                if (addSquareWithChecking(startA, startB, k)) {
                    backtrackHelper(startA, startB, end, k);
                    deleteSquare(startA, startB, k);
                }
            }
        } else {
            backtrackHelper(startA, startB, end, 1);
        }
    }

    /*
     * Добавление квадрата без проверки
     */
    private void addSquare(int a, int b, int size) {
        for (int i = a; i < a + size; i++) {
            for (int j = b; j < b + size; j++) {
                if (square[i][j] == 0) {
                    square[i][j] = -1;
                }
            }
        }
        square[a][b] = size;
        count++;
    }

    /*
     * Добавление квадрата с проверкой возможности этого добавления
     * Возвращает true - добавлено, false - невозможно добавить
     */
    boolean addSquareWithChecking(int a, int b, int size) {
        if (a + size > p || b + size > p) {
            return false;
        }
        for (int i = a; i < a + size; i++) {
            for (int j = b; j < b + size; j++) {
                if (square[i][j] != 0) {
                    return false;
                }
            }
        }
        addSquare(a, b, size);
        return true;
    }

    /*
     * Удаление квадрата без проверки
     */
    private void deleteSquare(int a, int b, int size) {
        for (int i = a; i < a + size; i++) {
            for (int j = b; j < b + size; j++) {
                if (square[i][j] != 0) {
                    square[i][j] = 0;
                }
            }
        }
        count--;
    }

    /*
     * Клонирование текущего варианта разрезания в буферную матрицу
     */
    void cloneTmp() {
        for (int i = 0; i < p; i++) {
            squareTmp[i] = square[i].clone();
        }
    }

    /*
     * Печать результата в требуемом формате
     */
    public void printResult() {
        System.out.println(minCount);
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                if (square[i][j] > 0) {
                    System.out.println((i * step + 1) + " " + (j * step + 1) + " " + square[i][j] * step);
                }
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        SquarePuzzle squarePuzzle = new SquarePuzzle(scanner.nextShort());
        squarePuzzle.printResult();
    }
}