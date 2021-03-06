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


//int find_pattern_index(vector<long> &pattern_memo, int window_size) {
//    int pattern_memo_size = pattern_memo.size();
//
//    vector<long>::const_iterator first = pattern_memo.begin();
//    vector<long>::const_iterator last  = first + window_size;
//    vector<long> window(first, last);
//    
//    for (int i = 1; i < pattern_memo_size - window_size; i++) {
//
//        vector<long>::const_iterator first = pattern_memo.begin() + i;
//        vector<long>::const_iterator last  = first + window_size;
//        vector<long> cur_window(first, last);
//
//        if (cur_window == window) {
//            return i;
//        }
//    }
//
//    return -1;
//}

int find_pattern_index(vector<long> &pattern_memo, int pattern) {
    int first_hit  = -1;
    int pattern_memo_size = pattern_memo.size();
    for (int i = 0; i < pattern_memo_size; i++) {

        if (pattern_memo.at(i) == pattern && first_hit != -1) {
            return i - first_hit; 
        }

        if (pattern_memo.at(i) == pattern && first_hit == -1) {
           first_hit = i; 
        }

    }

    return -1;
}


void solve(vector< vector<int>> &problems) {

    int problems_num = problems.size();
    
    for (int i = 0; i < problems_num; i++) {

        vector<long>        pattern_memo;
        unordered_set<long> pattern_memo_set;
        vector<int>         game_memo;
        vector<int>         oneproblem = problems[i];
        vector<int>         starting_moves;
        vector<int>::const_iterator first = oneproblem.begin()        + 1;
        vector<int>::const_iterator last  = first + oneproblem.size() - 1;

        // a vector includes all the moves
        vector<int>  moves(first, last);         

        long pattern         = 0;
        int  cur_pebble_num  = 0;
        int  pattern_dist    = -1;

        int  pebble_num      = oneproblem[0];
        int lost             = 0;
    
        game_memo.push_back(lost);

        while ( cur_pebble_num++ < pebble_num ) {
            
            int cur_result =  game_result_at( moves, game_memo, cur_pebble_num );
            
            if ( cur_pebble_num < 21) {
                pattern = pattern | (cur_result << (21  - 1 - cur_pebble_num));

            } else {
                pattern_memo.push_back(pattern);
                //pattern = (pattern >> 1) | (cur_result << (moves.size() - 1));
                pattern = (((pattern | (1 << (21 - 1))) ^ (1 << (21 - 1))) << 1) | cur_result; 
                //cout << hex << pattern << " ";
                int pattern_memo_size = pattern_memo.size();

                if ( pattern_memo_size > 0 ) {
                    pattern_dist = find_pattern_index(pattern_memo, pattern);
                }
            }
        }

        cout << pattern_dist << " ";
        
        cout << endl;

        for (int j: moves) {
            int position = pebble_num - j;
            int bitmap;

            if (position < pattern_dist)
                bitmap   = pattern_memo.at(position % pattern_dist);
            else
                bitmap   = game_memo.at(position);
            
            //cout << position << " " << " bitmap " << bitmap << endl;
            if ( !(bitmap & (1 << (moves.size() - 1)))) {
                starting_moves.push_back(j);
            }

        }
        /*
        if (starting_moves.size() == 0) {
            cout << "lose ";
        } else {
            cout << "one of theres: ";
            for (int j: starting_moves)  {
                cout << j << " ";
            }
        }
        cout << endl;
        */
    }
}


int main() {

    vector< vector<int> > problems = getProblem();

    solve(problems);

    return 0;
}
