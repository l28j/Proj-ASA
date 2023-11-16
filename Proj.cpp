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
    Board(int a, int b, int p) : a(a), b(b), p(p) {
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

void sortDb(std::vector<Board>& Db) {
    std::sort(Db.begin(), Db.end(), compareByPricePerArea);
}

int calculateOutput(std::vector<Board>& Db, int X, int Y) { 
    if (Db.size() == 0) { return 0; }
    else {}
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

    std::getline(std::cin, userInput);
    std::istringstream iss2(userInput);
    iss2 >> n;

    std::vector<Board> Db;

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);
        int a, b, p;
        iss3 >> a >> b >> p;

        if ((a <= X && b <= Y) || (a <= Y && b <= X)) { addToDb(Db, a, b, p); }
    }

    sortDb(Db);

    //int maxPrice = calculateOutput(Db, X, Y);
    //std::cout << maxPrice << std::endl;
    showOutput(Db, X, Y, n);

    return 0;
}