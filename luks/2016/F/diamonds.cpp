#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector< vector<double> > getInput() {
    vector< vector<double> > inputVec;
    string tmp;
    
    while (getline(cin, tmp)) {
        vector<double> nums;
        stringstream ss(tmp);
        double ti;
        while (ss >> ti)
            nums.push_back(ti);

        inputVec.push_back(nums);
    }
    
    return inputVec;
}


int main() {
    vector< vector<double> > inputVec = getInput();
    int len = inputVec.size();
    int * mem = new int[len];

    memset(mem, 1, len);
    
    for (int i = 0; i < len; i++) {
        mem[i] = 1;
    }

    double * c = new double[len];
    double * w = new double[len];

    for (int i = 0; i < len; i++) {
        c[i] = inputVec[i][0];
        w[i] = inputVec[i][1];
    }

    for (int i = 1; i < len; i++) {
        for (int j = 0; j < i; j++) {
            if (c[i] > c[j] && w[i] < w[j]) {
                mem[i] = max(mem[j] + 1, mem[i]);
            } 
        }
    }

    for (int i = 0; i < len; i++) {
        cout << mem[i] << endl;
    }

    return 0;
}
