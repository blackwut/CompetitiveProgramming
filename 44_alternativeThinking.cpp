/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/603/A?locale=en

    Solution Description
    The longest alternating subsequence can be found easily with a greedy
    strategy. It is sufficient to count the number of digit that differ from the
    previous one.
    The problem asks to find the longest alternating subsequence after a flip
    operation, that is a change of all '0' to '1' and vice versa of a contiguous
    substring. A flip operation with arbitrary length increases the length of an
    alternating subsequence by exactly 2 iff there are two equal consecutive
    digits (e.g. 00 or 11). This condition is always true for the longest
    alternating subsequences smaller than N. The solution is thus the minimum
    between the longest alternating subsequence plus 2 and N.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    string s;

    cin >> N;
    cin >> s;

    int longest = 1;
    for (int n = 1; n < N; ++n) {
        if (s[n - 1] != s[n]) {
            longest++;
        }
    }

    cout << min(N, longest + 2) << '\n';

    return 0;
}