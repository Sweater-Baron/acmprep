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


int game_result_at(vector<int> &moves, vector<int> &game_memo, int number) {

    int result;

    for (int i = 0; i < moves.size(); i++) {

        result = 0;

        int prev_lookup = number - moves[i];

        if (prev_lookup < 0)
            prev_lookup = number - 1;

        if (game_memo[prev_lookup] == 0) {
            result = 1;
            //cout << " number " << number << " prev_lookup " << prev_lookup << " moves[i] " << moves[i] << "  game_memo[prev_lookup] " << game_memo[prev_lookup] << " result "<< result<<endl;
            break;
        }

        //cout << " number " << number << " prev_lookup " << prev_lookup << " moves[i] " << moves[i] << "  game_memo[prev_lookup] " << game_memo[prev_lookup] << " result "<< result<<endl;
    }

    game_memo[number] = result;

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
        vector<int>         game_memo;
        vector<int>         oneproblem = problems[i];

        vector<int>::const_iterator first = oneproblem.begin() + 1;
        vector<int>::const_iterator last  = first + oneproblem.size() - 1;

        // a vector includes all the moves
        vector<int>  moves(first, last);         

        long pattern         = 0;
        int  save_pattern    = 0;
        int  cur_pebble_num  = 0;
        int  pattern_dist    = 0;

        int  pebble_num      = oneproblem[0];
    
        game_memo.push_back(0);
        game_memo.push_back(1);

        while ( cur_pebble_num++ < pebble_num ) {
            int cur_result =  game_result_at( moves, game_memo, cur_pebble_num );
            if ( cur_pebble_num <= moves.size()) {

                pattern = pattern | (cur_result >> cur_pebble_num);
                int number = 1 >> 4;
                cout << (1 >> 4) << " ";

            } else {
                pattern = (pattern << 1) | (cur_result >> moves.size());
                /*
                
                pattern_memo.push_back(pattern);
                pattern_memo_set.insert(pattern);

                if ( pattern_memo_set.find(pattern) != pattern_memo_set.end() ) {
                    pattern_dist = ( cur_pebble_num - find_pattern_index(pattern_memo, pattern) );
                    break;
                }
                */

            }
        }
        cout << endl;
        for (int i = 0; i < pattern_memo.size(); i++) {
            cout << pattern_memo[i] << endl;
        }
    }
    return 0;
}
