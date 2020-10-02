/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/313/B?locale=en

    Solution Description
    Construct an array such as:
    - a[0] = 0;
    - a[i] = 1 iff input[i - 1] = input[i], otherwise 0

    Prefix sum over the previous array to make each query in constant time.
    Query in the form [l, r] solved with (sums[r - 1] - sums[l - 1])

    Time  Complexity: O(N) preprocessing O(1) query time
    Space Complexity: O(N)
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    const int n = s.length();
    vector<int> sums(n);

    sums[0] = 0;
    for (int i = 1; i < n; ++i) {
        sums[i] = sums[i - 1] + (s[i - 1] == s[i]);
    }

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int l;
        int r;
        cin >> l;
        cin >> r;
        cout << sums[r - 1] - sums[l - 1] << '\n';
    }

    sums.clear();

    return 0;
}
