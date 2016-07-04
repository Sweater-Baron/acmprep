/*include*/
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/*It is a function that reads reach problem, each problem is stored as a 2D vector */
vector< vector<int> > getProblem() {
    vector< vector<int> > inputVec;
    string tmp;
    
    while (getline(cin, tmp)) {
        vector<int> nums;
        stringstream ss(tmp);
        int ti;
        while (ss >> ti)
            nums.push_back(ti);

        inputVec.push_back(nums);
    }
    
    return inputVec;
}

