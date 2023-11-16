/**
 * Project 1 ASA
 * Project done by:
 * João Rodrigues - ist1106221
 * Mariana Santana - ist1106992
 * TL03
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Board {
    int a, b, p;
    float pricePerArea;
    Board(int a, int b, int p) : p(p) {
        a = a >= b ? a : b;
        b = a <= b ? a : b;
        pricePerArea = static_cast<double>(p) / (a * b);
    }
};

void addToDb(std::vector<Board>& Db, int a, int b, int p) {
    Board newBoard(a, b, p);
    Db.push_back(newBoard);
}

bool compareByPricePerArea(const Board& a, const Board& b) {
    return a.pricePerArea > b.pricePerArea;
}

bool fits(int a, int b, int X, int Y) {
    return ((a <= X && b <= Y) || (a <= Y && b <= X));
}

bool alwaysFits(int a, int b, int X, int Y) {
    return ((a <= X && b <= Y) && (a <= Y && b <= X));
}

int howManyFit(int X, int Y, int a, int b) {
    return (X * Y) / (a * b);
}

void sortDb(std::vector<Board>& Db) {
    std::sort(Db.begin(), Db.end(), compareByPricePerArea);
}

int calculateOutput(std::vector<Board>& Db, int X, int Y, int index) {

    Board& board = Db[index];

    if (fits(board.a, board.b, X, Y)) {
        int X1, Y1, X2, Y2;
        if (!alwaysFits(board.a, board.b, X, Y)) {
            int max = X > Y ? X : Y;
            int min = X < Y ? X : Y;
            int max2 = board.a > board.b ? board.a : board.b;
            int min2 = board.a < board.b ? board.a : board.b;
            int X1 = max;
            int Y1 = min2;
            int X2 = max;
            int Y2 = min - max2;
        }
        if (fitsVertically(board.a, board.b, X, Y)) {
            
        }
        else if (fitsHorizontally(board.a, board.b, X, Y)) {

        }
        else {

        }

        return calculateOutput(Db, X1, Y1, index) + calculateOutput(Db, X2, Y2, index);
    }

    else if (index == Db.size()) { return 0; }

    else { return calculateOutput(Db, X, Y, index++); }
}

void showOutput(std::vector<Board>& Db, int X, int Y, int n) {

    for (const Board& board : Db) {
        std::cout << "Db:";
        std::cout << board.a << " " << board.b << " " << board.p << " " << board.pricePerArea << std::endl;
    }

    std::cout << "X: " << X << std::endl;
    std::cout << "Y: " << Y << std::endl;
    std::cout << "N: " << n << std::endl;
}

int main() {

    std::string userInput;
    int X, Y, n;

    std::getline(std::cin, userInput);
    std::istringstream iss(userInput);
    iss >> X >> Y;
    X = X >= Y ? X : Y;
    Y = X <= Y ? X : Y;

    std::getline(std::cin, userInput);
    std::istringstream iss2(userInput);
    iss2 >> n;

    std::vector<Board> Db;

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);
        int a, b, p;
        iss3 >> a >> b >> p;

        if (fits(a, b, X, Y)) { addToDb(Db, a, b, p); }
    }

    sortDb(Db);

    int maxPrice = (Db.size() == 0) ? 0 : calculateOutput(Db, X, Y, 0);
    std::cout << maxPrice << std::endl;

    showOutput(Db, X, Y, n);

    return 0;
}