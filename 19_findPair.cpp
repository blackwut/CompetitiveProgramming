/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/160/C

    Solution Description
    Sort all the values. If there are only distinct values, the K-th pair is
    <a_i, a_j> where i = (K - 1)/N and j = (K - 1).
    Otherwise, j is calculated differently. Let be l the number of values
    smaller than a_i, and let be r the number of values equal to a_i. The K-th
    pair is <a_i, a_j> where i is calculated as before, and
    j = (K - 1 - l * N) / r.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    uint64_t K;
    cin >> N;
    cin >> K;

    vector<int> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n];
    }

    sort(v.begin(), v.end());

    const uint64_t i = (K - 1) / N;
    const int first = v[i];

    uint64_t l = 0;  // number of values less than first
    for (l = 0; l < N; ++l) {
        if (v[l] == first) break;
    }

    uint64_t r = 0;  // number of values equal to first
    for (r = l; r < N; ++r) {
        if (v[r] != first) break;
    }
    r -= l;

    const uint64_t j = (K - 1 - l * N) / r;
    const int second = v[j];
    cout << first << ' ' << second << '\n';

    return 0;
}
