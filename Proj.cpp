#include <iostream>
#include <sstream>
#include <vector>

bool fitsVertically(int a, int b, int X, int Y) { return (a <= X && b <= Y); }
bool fitsHorizontally(int a, int b, int X, int Y) { return (a <= Y && b <= X); }
bool allFits(int a, int b, int X, int Y) { return (fitsVertically(a, b, X, Y) && fitsHorizontally(a, b, X, Y)); }

int calcMaxPrice(std::vector<std::vector<int>>& m, int X, int Y) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < i; k++) {
                m[i][j] = std::max(m[i][j], m[k][j] + m[i - k - 1][j]);
            }
            for (int k = 0; k < j; k++) {
                m[i][j] = std::max(m[i][j], m[i][k] + m[i][j - k - 1]);
            }
        }
    }
    return m[X - 1][Y - 1];
}

int main() {

    std::string userInput;
    int X, Y, n;
    
    scanf("%d %d", &X, &Y);
    scanf("%d", &n);
    
    std::vector<std::vector<int>> m(X, std::vector<int>(Y, 0));

    for (int i = 0; i < n; i++) {

        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);

        if (a > 0 && b > 0 && p > 0) {
            if (allFits(a, b, X, Y)) {
                m[a-1][b-1] = std::max(m[a-1][b-1], p);
                m[b-1][a-1] = std::max(m[b-1][a-1], p);
            }
            else if (fitsVertically(a, b, X, Y)) {
                m[a-1][b-1] = std::max(m[a-1][b-1], p);
            }
            else if (fitsHorizontally(a, b, X, Y)) {
                m[b-1][a-1] = std::max(m[b-1][a-1], p);
            }
        }
    }

    int maxPrice = calcMaxPrice(m, X, Y);
    printf("%d\n", maxPrice);
    return 0;
}