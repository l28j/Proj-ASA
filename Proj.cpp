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

struct Slate { 
    int a, b, p;
    Slate(int a, int b, int p) : a(a), b(b), p(p) {}
};

#define max_value(a, b) (a > b ? a : b)

bool fits (int a, int b, int X, int Y) {
    return (a <= X && b <= Y) || (a <= Y && b <= X);
}

int knapsack(std::vector<int> values, std::vector<std::pair<int, int>> dimensions, int X, int Y) {
    int numElements = dimensions.size();
    int maxArea = X * Y;
    
    std::vector<int> k(maxArea + 1, 0);

    for (int w = 1; w <= maxArea; w++) {
        
        k[w] = k[w - 1];  

        for (int i = 0; i < numElements; i++) {
            if (fit(dimensions[i].first, dimensions[i].second, X, Y)) {
                int area = dimensions[i].first * dimensions[i].second;
                int numRectangles = w / area; 
                k[w] = std::max(k[w], k[w - numRectangles * area] + numRectangles * values[i]);
            }
        }
    }
    return k[maxArea];
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

    std::vector<int> values;
    std::vector<Slate> slates;

    for (int i = 0; i < n; i++) {

        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);

        int a, b, p, A, B;
        iss3 >> a >> b >> p;
        A = a > b ? a : b;
        B = a > b ? b : a;

        if (fits(A, B, X, Y)) {
            Slate newSlate(A, B, p);
            slates.push_back(newSlate);
        }
    }

    std::sort(slates.begin(),slates.end(), [](const auto& slate1, const auto& slate2) {
        return slate1.a * slate1.b < slate2.a * slate2.b; });

    int maxPrice = knapsack(values, dimensions, X , Y);
    std::cout << maxPrice << std::endl;

    return 0;
}



        /*auto position = std::lower_bound(dimensions.begin(), dimensions.end(), std::make_pair(a, b), 
            [](const auto& a, const auto& b) { return a.first * a.second < b.first * b.second; });
        dimensions.insert(position, std::make_pair(a, b));
        int pos = *position;
        values.insert(values.begin() + pos, p);*/
