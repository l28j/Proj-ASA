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

inline int max_value(int a, int b) {
    return std::max(a, b);
}

bool fitsVertically(int a, int b, int X, int Y) { return (a <= X && b <= Y) && (a > 0 && b > 0); }
bool fitsHorizontally(int a, int b, int X, int Y) { return (a <= Y && b <= X) && (a > 0 && b > 0); }
bool fits(int a, int b, int X, int Y) { return (fitsVertically(a, b, X, Y) || fitsHorizontally(a, b, X, Y)); }
bool allFits(int a, int b, int X, int Y) { return (fitsVertically(a, b, X, Y) && fitsHorizontally(a, b, X, Y)); }

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

                if ((i==a && j ==b) || (i==b && j==a)){
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

int result2(std::vector<std::vector<int>>& m, int X, int Y) {

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            
            for (int k = 0; k < i; k++) {
                m[i][j] = max_value(m[i][j], m[k][j] + m[i - k - 1][j]);
            }
            for (int k = 0; k < j; k++) {
                m[i][j] = max_value(m[i][j], m[i][k] + m[i][j - k - 1]);
            }



            //if (i == 0 && j == 0) { continue; }
            //else if (i == 0 && j > 0) { m[i][j] = max_value(m[i][j], m[i][j - 1] + m[i][Y - j]); }
            //else if (j == 0 && i > 0) { m[i][j] = max_value(m[i][j], m[i - 1][j] + m[X - i][j]); }

            //else {
                //m[i][j] = max_value(m[i][j], m[i - 1][j] + m[X - i][j]);
                //m[i][j] = max_value(m[i][j], m[i][j - 1] + m[i][Y - j]);
            //}
            //cut horizontal
            //if (i == 0 && j > 0) { m[i][j] = max_value(m[i][j], m[i][j - 1] + m[i][Y - j]); }
            //if (i == 0 && j > 0) { m[i][j] = max_value(m[i][j], result2(m,i,j - 1)); }
            //else if (i > 0 && j > 0) { m[i][j] = max_value(m[i][j], m[i - 1][j]); }

            //cut vertical
            //if (j == 0 && i > 0) { m[i][j] = max_value(m[i][j], m[i - 1][j]); }
            //else if (j > 0 && i > 0) { m[i][j] = max_value(m[i][j], m[i][j - 1]); }

            //fits slate
            
        }
    }
    //if (X == 0 || Y == 0) { return m[X][Y]; }
    return m[X - 1][Y - 1];
}

int result3(const std::map<std::string, Slate>& slatesMap, int X, int Y) {

    std::vector<std::vector<int>> values(X+1, std::vector<int>(Y+1, 0));   

    for (int i = 0 ; i <= X ; i ++) {
        for (int j = 0 ; j <= Y ; j ++) {
            
            std::stringstream ss;
            ss << i << "-" << j;
            std::string key = ss.str();

            if (slatesMap.find(key) != slatesMap.end()) {
                Slate slate = slatesMap.at(key);
                int p = slate.p;
                values[i][j] = max_value(values[i][j], p);
            }

            std::stringstream ss2;
            ss2 << j << "-" << i;
            std::string key2 = ss2.str();

            if (slatesMap.find(key2) != slatesMap.end()) {
                Slate slate = slatesMap.at(key2);
                int p = slate.p;
                values[i][j] = max_value(values[i][j], p);
            }
            else {
                for (int k = 0 ; k < i ; k ++) {
                    values[i][j] = max_value(values[i][j], values[k][j] + values[i-k][j]);
                }
                for (int k = 0 ; k < j ; k ++) {
                    values[i][j] = max_value(values[i][j], values[i][k] + values[i][j-k]);
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
    std::vector<std::vector<int>> m(X, std::vector<int>(Y, 0));

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, userInput);
        std::istringstream iss3(userInput);

        int p, a, b;
        iss3 >> a >> b >> p;

        if (fits(a, b, X, Y) && p > 0) {
            slates.emplace_back(a, b, p);
        }

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

    /*for (const auto& row : m) {
        // Iterate through each element in the row
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl; // Move to the next line after printing a row
    }*/

    //int maxPrice = result(slates, X, Y);
    int maxPrice2 = result2(m, X, Y);

    std::cout << maxPrice2 << std::endl;

    return 0;
}
