/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/276/C

    Solution Description
    To be sure that we obtain the maximum sum in all ranges [l, r], we try to
    place the maximum values of the input in that range.
    In order to do that, we sort the input values and place the maximum values
    in the most frequent queried positions.
    We construct the vector "f" (initially all entries set to 0) to store the 
    entry frequencies. For each query we add 1 to f[l - 1] and subtract 1 to
    f[r]. Then we prefix-sum the vector. In this way we generate the vector of
    frequencies in time proportional to the number of queries.
    Then we sort both the input vector and the frequencies vector.
    To calculate the result, we simply multiply each value of the input vector
    by the value in the frequencies vector at the same position and sum them up.

    Time  Complexity: O(Q + N log2 N) or O(Q + N) if O(N) sorter is used
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define uint uint64_t


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint N;
    uint Q;
    cin >> N;
    cin >> Q;

    vector<uint> v(N, 0);
    vector<uint> f(N + 1, 0);

    for (uint n = 0; n < N; ++n) {
        cin >> v[n];
    }

    for (uint q = 0; q < Q; ++q) {
        uint l;
        uint r;
        cin >> l;
        cin >> r;
        f[l - 1] += 1;
        f[r] -= 1;
    }

    for (uint n = 1; n < N; ++n) {
        f[n] += f[n - 1];
    }

    sort(v.begin(), v.end());
    sort(f.begin(), f.end() - 1);

    uint result = 0;
    for (uint n = 0; n < N; ++n) {
        result += v[n] * f[n];
    }

    cout << result;
    cout << endl;

    v.clear();
    f.clear();

    return 0;
}
