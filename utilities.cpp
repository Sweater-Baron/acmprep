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

//TODO: check if anything is out of bound
vector<int> sub_vec(const vector<int> &vec, int begin_index, int end_index) {

    vector<int>::const_iterator first = vec.begin() + begin_index;
    vector<int>::const_iterator last  = first + end_index;

    vector<int>  new_vec(first, last);         

    return new_vec;
}
