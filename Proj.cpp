#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Slate {
    int a, b, p;
    Slate(int a, int b, int p) : a(a), b(b), p(p) {}
};

#define max_value(a, b) (a > b ? a : b)

bool fits(int a, int b, int X, int Y) {
    return (a > 0 && b > 0) && ((a <= X && b <= Y) || (a <= Y && b <= X));
}

int knapsack(const std::vector<Slate>& slates, int X, int Y) {
    int numElements = slates.size();
    std::vector<std::vector<int>> k(X + 1, std::vector<int>(Y + 1, 0));

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            for (int n = 0; n < numElements; n++) {
                if (slates[n].a <= i && slates[n].b <= j) {
                    k[i][j] = max_value(k[i][j], k[i - slates[n].a][j] + k[slates[n].a][j - slates[n].b] + slates[n].p);
                }
            }
        }
    }
    return k[X][Y];
}

int main() {
    std::string userInput;
    int x, y, X, Y, n;

    std::getline(std::cin, userInput);
    std::istringstream iss(userInput);
    iss >> x >> y;
    X = x > y ? x : y;
    Y = x > y ? y : x;

    std::getline(std::cin, userInput);
    std::istringstream iss2(userInput);
    iss2 >> n;

    std::vector<Slate> slates;

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);

        int a, b, p, A, B;
        iss3 >> a >> b >> p;
        A = a > b ? a : b;
        B = a > b ? b : a;

        Slate newSlate(A, B, p);
        slates.push_back(newSlate);
    }

    std::sort(slates.begin(), slates.end(), [](const Slate& slate1, const Slate& slate2) {
        return slate1.a * slate1.b < slate2.a * slate2.b;
    });

    int maxPrice = knapsack(slates, X, Y);
    std::cout << maxPrice << std::endl;

    return 0;
}
