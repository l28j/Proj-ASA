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

#define max_value(a, b) (a > b ? a : b)

bool fit (int a, int b, int X, int Y) {
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
    int X, Y, n;

    std::getline(std::cin, userInput);
    std::istringstream iss(userInput);
    iss >> X >> Y;                          

    std::getline(std::cin, userInput);
    std::istringstream iss2(userInput);
    iss2 >> n;

    std::vector<int> values;
    std::vector<std::pair<int, int>> dimensions;

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);
        int a, b, p;
        iss3 >> a >> b >> p;
        values.push_back(p);
        dimensions.push_back(std::make_pair(a, b));
    }                       

    int maxPrice = knapsack(values, dimensions, X , Y);
    std::cout << maxPrice << std::endl;

    return 0;
}
