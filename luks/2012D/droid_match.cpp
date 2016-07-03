#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstring>
#include <unordered_set>

using namespace std;

vector< vector<int> > getProblem() {
    vector< vector<int> > problem;
    string tmp;
    
    while (getline(cin, tmp)) {
        vector<int> nums;
        stringstream ss(tmp);

        int each_item;
        while (ss >> each_item)
            nums.push_back(each_item);

        problem.push_back(nums);
    }
    
    return problem;
}


char game_result_at(vector<int> &moves, vector<char> &game_memo, int number) {
    char result;
    for (int i = 0; i < moves.size(); i++) {
        result &= game_memo[ number - moves[i] ];
        game_memo[number] = result;
    }

    return result;
}


int find_pattern_index(vector<long> &pattern_memo, long pattern) {
    int index = -1;
    for (int i = 0; i < pattern_memo.size(); i++) {
        if ( pattern_memo[i] == pattern ) {
            index = i;
        }
    }

    return index;
}


int main() {
    vector< vector<int> > problems = getProblem();

    for (int i = 0; i < problems.size(); i++) {

        vector<long>        pattern_memo;
        unordered_set<long> pattern_memo_set;
        vector<char>        game_memo;
        vector<int>         oneproblem = problems[0];

        vector<int>::const_iterator first = oneproblem.begin() + 1;
        vector<int>::const_iterator last  = first + oneproblem.size();
        vector<int>  moves(first, last);
        
        long pattern         = 0;
        int  save_pattern    = 0;
        int  cur_pebble_num  = 0;
        int  pattern_dist    = 0;
        int  pebble_num      = oneproblem[0];
    
        while ( cur_pebble_num++ < oneproblem[0]) {
            int cur_result =  game_result_at(moves, game_memo, cur_pebble_num);

            if ( cur_pebble_num >= moves.size()) {

                pattern = pattern | (cur_result >> cur_pebble_num);

            } else {

                pattern = pattern << 1 | (cur_result >> moves.size());
                pattern_memo.push_back(pattern);
                pattern_memo_set.insert(pattern);

                if ( pattern_memo_set.find(pattern) != pattern_memo_set.end() ) {
                    pattern_dist = ( cur_pebble_num - find_pattern_index(pattern_memo, pattern) );
                    break;
                }

            }
        }

        for (int i = 0; i < pattern_memo.size(); i++) {
            cout << pattern_memo[i] << endl;
        }
    }
    return 0;
}
