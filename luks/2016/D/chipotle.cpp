#include <iostream>
#include <algorithm>

int main() {

    int cents        = 10000 + 1;
    int menu_size    = 4;
    int price_s[4]   = {139, 439, 899, 627};
    int cal_s[4]     = {150, 600, 550, 800};

    int * T     = new int[cents];
    int * price = new int[menu_size];
    int * cal   = new int[menu_size];


    for (int i = 0; i < menu_size; i++) {
         *(price + i) = *(price_s + i);
    }

    for (int i = 0; i < menu_size; i++) {
         *(cal + i) = *(cal_s + i);
    }

    for (int i = 0; i < cents; i++) {
       T[i] = 0;
    }


    for (int i = 1; i < cents; i++) {
        int max_cal = 0;
        for (int k = 0; k < menu_size; k++) {
            if ( (i - price[k] >= 0) && ((T[i - price[k]] > 0) || (i - price[k]) == 0) ) {

                if ( T[i - price[k]] + cal[k] > max_cal ) {
                    max_cal = T[ i - price[k] ] + cal[k];
                }
            }
        }

        T[i] = std::max(max_cal, T[i]);
    }

    std::cout << T[cents - 1]<< std::endl;

    delete [] T;
    delete [] price;
    delete [] cal;
    return 0;
}
