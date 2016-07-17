#include <iostream>

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;
    int * p = new int[n];
    int ** schedule = new int * [n];

    for (int i = 0; i < n; i++) {
        *(schedule + 1) = new int[n];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
           std::cin >> schedule[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << p[i] <<  " ";
    }
    std::cout <<  std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << << std::endl;
        }
    }
    return 0;
}

