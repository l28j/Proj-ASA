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
    std::vector<int> k((X + 1) * (Y + 1), 0);

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            for (int n = 0; n < numElements; n++) {
                int currentA = slates[n].a;
                int currentB = slates[n].b;
                int temp = k[(i - currentA) * (Y + 1) + j] + k[currentA * (Y + 1) + j - currentB] + slates[n].p;

                if (currentA <= i && currentB <= j) {
                    k[i * (Y + 1) + j] = max_value(k[i * (Y + 1) + j], temp);
                }

                temp = k[(i - currentB) * (Y + 1) + j] + k[currentB * (Y + 1) + j - currentA] + slates[n].p;
                if (currentB <= i && currentA <= j) {
                    k[i * (Y + 1) + j] = max_value(k[i * (Y + 1) + j], temp);
                }
            }
        }
    }
    return k[X * (Y + 1) + Y];
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

        if (fits(A, B, X, Y) && p > 0) {
            Slate newSlate(A, B, p);
            slates.push_back(newSlate);
        }
    }

    std::sort(slates.begin(), slates.end(), [](const Slate& slate1, const Slate& slate2) {
        return slate1.a * slate1.b < slate2.a * slate2.b;
    });

    int maxPrice = knapsack(slates, X, Y);
    std::cout << maxPrice << std::endl;

    return 0;
}
