#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int MostCal(const vector<int> &prices, const vector<int> &calories, double money) {
    int row_size = static_cast<int>(money * 100) + 1, col_size = static_cast<int>(prices.size());

    vector< vector<int> > T;

    // intitalize memorization table
    for (int i = 0; i < col_size; i++) {
        vector<int> tempV(row_size, 0);
        T.push_back(tempV);
    }

    // recusive relation
    for (int i = 1; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            try {
                if (j - prices.at(i) >= 0) {
                    T[i][j] = std::max(T[i-1][j], T[i][j - prices.at(i)] + calories.at(i));
                } else {
                    T[i][j] = T[i-1][j];
                }

            } catch(const std::out_of_range& oor) {
                std::cout << i  << " " << j << std::endl;
            }
        }
    }

    return T[col_size - 1][row_size - 1];
}

int main (void) {
    int ncandies = -99;
    double money;
    while (ncandies != 0) {
        cin >> ncandies >> money;
        /*std::cout << ncandies << " " << money << std::endl;*/
        vector<int> prices(1,0), calories(1,0);
        for (int i = 0; i < ncandies; i++) {
            int cal;
            double price;
            cin >> cal >> price;
            /*std::cout << cal << " " << price << std::endl;*/
            calories.push_back(cal);
            prices.push_back(static_cast<int> (price * 100));
        }

        if (ncandies != 0)
            cout << MostCal(prices, calories, money) << endl;
    }

    return 0;
}
