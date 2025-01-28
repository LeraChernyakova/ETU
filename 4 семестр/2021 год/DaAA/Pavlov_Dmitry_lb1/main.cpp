#include <bits/stdc++.h>
#include <ctime>

using Matrix = std::vector<std::vector<int>>;
using Point = std::pair<int, int>;

struct Square {
    Square() = default;
    Square(int x, int y, int w)
            : x(x), y(y), w(w) {}

    int x = 0;
    int y = 0;
    int w = 0;
};

using Squares = std::vector<Square>;

struct BacktrackingArgs {
    BacktrackingArgs(Matrix b, int sc, Squares cs)
            : board(b), squareCnt(sc), curSquares(cs) {}

    Matrix board;
    int squareCnt;
    Squares curSquares;
};
void drawMap(std::vector<std::vector<int> > map){

    for(auto it = map.begin();it!=map.end();it++){
        for(auto it1=it->begin();it1!=it->end();it1++){
            std::cout<<(char)(*it1<=9?*it1 + '0':*it1-10 + 'a');
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }

}

void addSquare(Matrix& board, const Square& square) {
    for (int i = square.x; i < square.x + square.w; ++i)
        for (int j = square.y; j < square.y + square.w; ++j)
            board[i][j] = 1;
}

void printAnswer(int& answer, Squares& squares) {
    std::cout << answer << std::endl;
    for (size_t i = 0; i < squares.size(); ++i) {
        std::cout << squares[i].x + 1 << " " << squares[i].y + 1 << " " << squares[i].w << std::endl;
    }
}

bool isFit(const int& n, const Matrix& board, const Square& placeSquare) {
    auto w = placeSquare.w;
    return (placeSquare.x + w < n) &&
           (placeSquare.y + w < n) &&
           (board[placeSquare.x + w][placeSquare.y + w] == 0) &&
           (board[placeSquare.x + w][placeSquare.y] == 0) &&
           (board[placeSquare.x][placeSquare.y + w] == 0);
}

void backtracking(const int& n, Matrix board, int squareCount, int& curMin, Squares currentSquares, Squares& resultSquares) {
    std::stack<BacktrackingArgs> candidates;
    candidates.emplace(board, squareCount, currentSquares);
    while (!candidates.empty()) {
        auto curArgs = candidates.top();
        candidates.pop();

        if (curArgs.squareCnt >= curMin)
            continue;

        bool isFull = true;
        Point placeCrd = {-1, -1};
        for (int x = 0; x < n / 2 + 1; ++x) {
            for (int y = 0; y < n / 2 + 1; ++y) {
                if (curArgs.board[x][y] == 0) {
                    placeCrd = {x, y};
                    isFull = false;
                    break;
                }
            }
            if (placeCrd.first > -1) {
                break;
            }
        }

        if (isFull) {
            curMin = curArgs.squareCnt;
            resultSquares = curArgs.curSquares;
            continue;
        }

        if (curArgs.squareCnt + 1 >= curMin)
            continue;

        for (int w = 0; w < n - 1; ++w) {
            int startX = placeCrd.first;
            int startY = placeCrd.second;
            if (isFit(n, curArgs.board, Square(placeCrd.first, placeCrd.second, w))) {
                for (int x = startX; x <= placeCrd.first + w; ++x) {
                    curArgs.board[x][placeCrd.second + w] = curArgs.squareCnt + 1;
                }
                for (int y = startY; y <= placeCrd.second + w; ++y) {
                    curArgs.board[placeCrd.first + w][y] = curArgs.squareCnt + 1;
                }
                ++startX;
                ++startY;

                curArgs.curSquares.push_back(Square({placeCrd.first, placeCrd.second, w + 1}));
                candidates.emplace(curArgs.board, curArgs.squareCnt + 1, curArgs.curSquares);
                curArgs.curSquares.pop_back();
            } else {
                break;
            }
        }
    }
}

// n - even number
void evenCase(int n, int& answer, Squares& squares) {
    squares = {
            { 0, 0, n / 2 },
            { 0, n / 2, n / 2 },
            { n / 2, 0, n / 2 },
            { n / 2, n / 2, n / 2 }
    };
    answer = 4;
}

// n - prime number
void primeCase(int n, Matrix& board, int& answer, Squares& currentSquares, Squares& resultSquares) {
    // Container for fixed squares
    Squares fixedSquares;

    addSquare(board, Square(n - n / 2, 0, n / 2));
    fixedSquares.emplace_back(n - (n / 2), 0, n / 2);

    addSquare(board, Square(0, n - n / 2, n / 2));
    fixedSquares.emplace_back(0, n - n / 2, n / 2);

    addSquare(board, Square(n / 2, n / 2, n / 2 + 1));
    fixedSquares.emplace_back(n / 2, n / 2, n / 2 + 1);

    // Empiric optimizations
    if (n >= 5) {
        // Fix 2 squares with sizes 1x1 and 2x2 (near "big" squares)
        board[n / 2 - 1][n / 2] = 1;
        fixedSquares.emplace_back(n / 2 - 1, n / 2, 1);

        addSquare(board, Square(n / 2 - 1, n / 2 - 2, 2));
        fixedSquares.emplace_back(n / 2 - 1, n / 2 - 2, 2);
    }

    if (n >= 13) {
        // Fix 1 square with size 3x3
        addSquare(board, Square(n / 2 - 4, n / 2 - 2, 3));
        fixedSquares.emplace_back(n / 2 - 4, n / 2 - 2, 3);
    }

    if (n >= 23) {
        // Fix 1 square with size 5x5
        addSquare(board, Square(n / 2 - 4, n / 2 - 7, 5));
        fixedSquares.emplace_back(n / 2 - 4, n / 2 - 7, 5);
    }

    backtracking(n, board, fixedSquares.size(), answer, currentSquares, resultSquares);

    // Consider almost placed squares
    std::copy(fixedSquares.begin(), fixedSquares.end(), std::back_inserter(resultSquares));
}

// n % m == 0
void multipleOfMCase(int m, int n, Matrix& board, int& answer, Squares& currentSquares, Squares& resultSquares) {
    int k = n / m;
    primeCase(m, board, answer, currentSquares, resultSquares);
    for (auto& square : resultSquares) {
        square.x *= k;
        square.y *= k;
        square.w *= k;
    }
}

void printElapsedTime(const std::clock_t& start) {
    std::cout.precision(10);
    std::cout << std::fixed << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;
}

void solve(int& n, Squares& resultSquares) {
    int answer = 4 + 2 * (n / 2) + 1;
    Squares currentSquares;

    std::set<int> primes {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    std::clock_t clk = clock();

    if (n % 2 == 0) {
        evenCase(n, answer, resultSquares);
        printAnswer(answer, resultSquares);
        printElapsedTime(clk);
        return;
    }

    Matrix board(n);
    for (int i = 0; i < n; ++i)
        board[i] = std::vector<int>(n, 0);


    if (primes.count(n) > 0) {
        primeCase(n, board, answer, currentSquares, resultSquares);
    } else if (n % 3 == 0) {
        multipleOfMCase(3, n, board, answer, currentSquares, resultSquares);
    } else if (n % 5 == 0) {
        multipleOfMCase(5, n, board, answer, currentSquares, resultSquares);
    }

    printAnswer(answer, resultSquares);
    printElapsedTime(clk);
}

int main() {
    int n;
    std::cin >> n;

    Squares resSquares;
    solve(n, resSquares);
    return 0;
}