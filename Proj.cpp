#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Slate {
    int a, b, p;
    Slate(int a, int b, int p) : a(a), b(b), p(p) {}
};

inline int max_value(int a, int b) {
    return std::max(a, b);
}

bool fits(int a, int b, int X, int Y) {
    return (a > 0 && b > 0) && ((a <= X && b <= Y) || (a <= Y && b <= X));
}

int result(const std::vector<Slate>& slates, int X, int Y) {
    
    
    int numElements = slates.size();
    std::vector<std::vector<int>> values(X+1, std::vector<int>(Y+1, 0));   

    for (int i = 0 ; i <= X ; i ++) {
        for (int j = 0 ; j <= Y ; j ++) {
            for (int k = 0 ; k < numElements ; k ++) {
                
                    Slate slate = slates[k];    
                    int a = slate.a;
                    int b = slate.b;
                    int p = slate.p;

                if (( i==a && j ==b) || (i==b && j==a)){
                    values[i][j] = max_value(values[i][j], p);
                }
                else if ((i >= a && j >= b) && ( i >= b && j >= a)) {
                    values[i][j] = max_value(values[i][j], 
                        max_value(values[i-a][j] + values[a][j], values[i-b][j] + values[b][j]));

                    values[i][j] = max_value(values[i][j],
                        max_value(values[i][j-a] + values[i][a], values[i][j-b] + values[i][b]));
                }

                else if (( i >= a && j >= b)){
                    values[i][j] = max_value(values[i][j],
                        max_value(values[i-a][j] + values[a][j], values[i][j-b] + values[i][b]));
                }
                else if (( i >= b && j >= a)){
                    values[i][j] = max_value(values[i][j],
                        max_value(values[i-b][j] + values[b][j], values[i][j-a] + values[i][a]));
                }            
            }
        }
    }

    return values[X][Y];
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

    std::vector<Slate> slates;

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);

        int p, A, B;
        iss3 >> A >> B >> p;

        if (fits(A, B, X, Y) && p > 0) {
            slates.emplace_back(A, B, p);
        }
    }

    int maxPrice = result(slates, X, Y);
    std::cout << maxPrice << std::endl;

    return 0;
}
