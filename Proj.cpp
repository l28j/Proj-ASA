#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

struct Slate {
    int a, b, p;
    Slate(int a, int b, int p) : a(a), b(b), p(p) {}
};

int max_value(int a, int b) { return std::max(a, b); }

bool fitsVertically(int a, int b, int X, int Y) { return (a <= X && b <= Y) && (a > 0 && b > 0); }
bool fitsHorizontally(int a, int b, int X, int Y) { return (a <= Y && b <= X) && (a > 0 && b > 0); }
bool fits(int a, int b, int X, int Y) { return (fitsVertically(a, b, X, Y) || fitsHorizontally(a, b, X, Y)); }
bool allFits(int a, int b, int X, int Y) { return (fitsVertically(a, b, X, Y) && fitsHorizontally(a, b, X, Y)); }

int result2(std::vector<std::vector<int>>& m, int X, int Y) {

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < i; k++) {
                m[i][j] = max_value(m[i][j], m[k][j] + m[i - k - 1][j]);
            }
            for (int k = 0; k < j; k++) {
                m[i][j] = max_value(m[i][j], m[i][k] + m[i][j - k - 1]);
            }
        }
    }
    return m[X - 1][Y - 1];
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
    
    std::vector<std::vector<int>> m(X, std::vector<int>(Y, 0));

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);

        int p, a, b;
        iss3 >> a >> b >> p;

        if (allFits(a, b, X, Y) && p > 0) {
            m[a-1][b-1] = max_value(m[a-1][b-1], p);
            m[b-1][a-1] = max_value(m[b-1][a-1], p);
        }
        else if (fitsVertically(a, b, X, Y) && p > 0) {
            m[a-1][b-1] = max_value(m[a-1][b-1], p);
        }
        else if (fitsHorizontally(a, b, X, Y) && p > 0) {
            m[b-1][a-1] = max_value(m[b-1][a-1], p);
        }
    }

    int maxPrice2 = result2(m, X, Y);
    std::cout << maxPrice2 << std::endl;

    return 0;
}
