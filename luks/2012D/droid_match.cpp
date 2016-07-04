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
    int move_size = moves.size();
    //int game_memo_size = game_memo.size();
    
    for (int i = 0; i < move_size; i++) {
        result = 0;
        int prev_lookup = number - moves[i];

        if (prev_lookup < 0)
            prev_lookup = number - 1;

        int prev_result;

        try {
            prev_result = game_memo.at( prev_lookup );
        } catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << " index is " << prev_lookup << '\n';
        }

        if ( prev_result == 0) {
            result = 1;
            break;
        }
    }

    try {
        game_memo.push_back(result);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: DOWN" << oor.what() << " index is " << number << '\n';
    }

    return result;
}


int find_pattern_index(vector<long> &pattern_memo, long pattern) {
    int index = -1;

    int pattern_memo_size = pattern_memo.size();
    for (int i = 0; i < pattern_memo_size; i++) {
        if ( pattern_memo[i] == pattern ) {
            index = i;
        }
    }

    return index;
}


int main() {

    vector< vector<int> > problems = getProblem();

    int problems_num = problems.size();
    
    for (int i = 0; i < problems_num; i++) {

        vector<long>        pattern_memo;
        unordered_set<long> pattern_memo_set;
        vector<int>         game_memo;
        vector<int>         oneproblem = problems[i];

        vector<int>::const_iterator first = oneproblem.begin() + 1;
        vector<int>::const_iterator last  = first + oneproblem.size() - 1;

        // a vector includes all the moves
        vector<int>  moves(first, last);         

        long pattern         = 0;
        //int  save_pattern    = 0;
        int  cur_pebble_num  = 0;
        //int  pattern_dist    = 0;

        int  pebble_num      = oneproblem[0];
        int win              = 0;
        int lost             = 1;
    
        game_memo.push_back(win);
        game_memo.push_back(lost);

        while ( cur_pebble_num++ < pebble_num ) {
            int cur_result =  game_result_at( moves, game_memo, cur_pebble_num );
            int moves_size = moves.size();
            cout << cur_result << " ";
            if ( cur_pebble_num <= moves_size) {

                pattern = pattern | (cur_result >> cur_pebble_num);
                /*
                int number = 1 >> 4;
                cout << number << " ";
                */

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
        int pattern_memo_size = pattern_memo.size();
        for (int i = 0; i < pattern_memo_size; i++) {
            cout << pattern_memo[i] << endl;
        }
    }
    return 0;
}
