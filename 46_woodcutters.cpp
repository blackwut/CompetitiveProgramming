/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/contest/545/problem/C?locale=en

    Solution Description
    Fell the leftmost tree to the left. This is always possible and it doesn't
    worse the answer.
    Then try to fell the next tree to the left. If it is possible, do it since
    it doesn't worse the answer. If it isn't possible, fell it to the right if
    there is enough space.
    The last step is correct because felling a tree to the right may only
    prevent the fell of the next tree. So we can state that exchanging one tree
    to the next one, or vice versa, doesn't worse the answer.
    The greedy strategy adopted is hence optimal.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Tree {
    int x;
    int h;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    if (N < 3) {
        cout << N << '\n';
        return 0;
    }

    vector<Tree> trees(N);
    for (int n = 0; n < N; ++n) {
        cin >> trees[n].x;
        cin >> trees[n].h;
    }

    // cut always the first tree
    int last = trees[0].x;
    int cut = 1;

    for (int n = 1; n < N - 1; ++n) {
        const int x = trees[n].x;
        const int h = trees[n].h;
        if (x - h > last) {
            last = x;
            ++cut;
        } else if (x + h < trees[n + 1].x) {
            last = x + h;
            ++cut;
        } else {
            last = x;
        }
    }

    // cut always the last tree
    ++cut;

    cout << cut << '\n';

    return 0;
}
