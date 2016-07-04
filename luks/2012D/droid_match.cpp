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


int find_pattern_index(vector<long> &pattern_memo, int window_size) {
    int pattern_memo_size = pattern_memo.size();

    vector<long>::const_iterator first = pattern_memo.begin();
    vector<long>::const_iterator last  = first + window_size;
    vector<long> window(first, last);
    
    for (int i = 1; i < pattern_memo_size - window_size; i++) {

        vector<long>::const_iterator first = pattern_memo.begin() + i;
        vector<long>::const_iterator last  = first + window_size;
        vector<long> cur_window(first, last);

        if (cur_window == window) {
            return i;
        }
    }

    return -1;
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
     // int  save_pattern    = 0;
        int  cur_pebble_num  = 0;
        int  pattern_dist    = -1;

        int  pebble_num      = oneproblem[0];
        int win              = 0;
        int lost             = 1;
    
        game_memo.push_back(win);
        game_memo.push_back(lost);

        while ( cur_pebble_num++ < pebble_num ) {

            int cur_result =  game_result_at( moves, game_memo, cur_pebble_num );
            int moves_size = moves.size();

            if ( cur_pebble_num <= moves_size) {
                pattern = pattern | (cur_result << cur_pebble_num);

            } else {
                pattern = (pattern >> 1) | (cur_result << moves.size());
                pattern_memo.push_back(pattern);
                
                int pattern_memo_size = pattern_memo.size();

                cout << pattern << " ";

                if ( pattern_memo_size > moves_size ) {
                    pattern_dist = find_pattern_index(pattern_memo, moves_size);
                }

                if (pattern_dist != -1) {
                    cout << "pattern distance " << pattern_dist << endl;
                    break;
                }
            }
        } 
    }
    return 0;
}
