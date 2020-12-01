/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/596/B?locale=en

    Solution Description
    The solution can be found with a greedy approach. The minimum number of
    operation is the sum of the absolute values of differences between
    consecutive elements.

    Time  Complexity: O(N)
    Space Complexity: O(1)
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    int64_t result = 0;
    int b0 = 0;
    int b1 = 0;

    for (int n = 0; n < N; ++n) {
        cin >> b1;
        result += abs(b1 - b0);
        b0 = b1;
    }

    cout << result << '\n';

    return 0;
}
