/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/6/C?locale=en

    Solution Description
    Iterate from both sides, Alice from the left and Bob from the right.
    At each iteration, accumulate the time spent to eat and the number of bars
    ate by both.
    Advance from left if Alice has spent less time than Bob, otherwise advance
    from right. In case of tie, Alice has the priority over Bob.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n];
    }

    int aliceTime = 0;
    int aliceBars = 0;
    int bobTime   = 0;
    int bobBars   = 0;

    auto left  = v.begin();
    auto right = v.end() - 1;

    while (left <= right) {
        if (aliceTime <= bobTime) {
            aliceTime += *left;
            ++aliceBars;
            ++left;
        } else {
            bobTime += *right;
            ++bobBars;
            --right;
        }
    }

    cout << aliceBars << ' ' << bobBars << '\n';

    return 0;
}
