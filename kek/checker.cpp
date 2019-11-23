#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <string>

#define assert_input(expr)    if (!(expr)) {cout << score << endl; return 0;}

using namespace std;

int main(int argc, char** argv) {
    ifstream input(argv[1]);
    ifstream output(argv[2]);
    ifstream answer(argv[3]);

    int score = 0;
    int candy[2];
    input >> candy[0] >> candy[1];

    int n;
    int candy_cnt = 0;
    assert_input(output >> n);
    bool block = false;
    char last_move = 'U';
    for (int i = 0; i < n; i++)
    {
        char move;
        assert_input(output >> move);
        if (last_move == move && last_move == 'T')
        {
            score = 0;
            cout << score << endl;
            return 0;
        }
        if (move == 'E')
        {
            if (candy[i % 2] == 0)
            {
                score = 0;
                cout << score << endl;
                return 0;
            }
            else
            {
                candy[i % 2]--;
                if (i % 2 == 0)
                    candy_cnt++;
            }
            block = false;
        }
        if (move == 'T')
        {
            if (candy[(i + 1) % 2] == 0 || block)
            {
                score = 0;
                cout << score << endl;
                return 0;
            }
            else
            {
                candy[(i + 1) % 2]--;
                candy[i % 2]++;
            }
            block = true;
        }
        if (move == 'W')
        {
            if (candy[i % 2] != 0 || (candy[(i + 1) % 2] != 0 && !block))
            {
                score = 0;
                cout << score << endl;
                return 0;
            }
            block = false;
        }
        last_move = move;
    }
    int res;
    answer >> res;

    if (res - candy_cnt <= 0)
        score = 2;
    else
        if (res - candy_cnt <= 3)
            score = 1;
        else
            score = 0;
    cout << score;
}