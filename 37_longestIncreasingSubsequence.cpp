/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0

    Solution Description
    The problem is solved with dynamic programming.
    Let be A[1, n] the sequence of numbers and LIS(i - 1) the Longest Increasing
    Subsequence with last element A[i - 1].
    We can compute LIS(i) as:
    - 1 + max(LIS(j) | j < i and A[j] < A[i])                          j >= 1
    - 1                                                                otherwise
    The first line means that we are extending the a previous LIS(j) with j < i
    by 1 with the current value A[i] when A[j] < A[i]. Otherwise A[i] is a new
    starting value of a LIS.
    The solution is the maximum between all LIS(i).

    Time  Complexity: O(N^2)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LIS(const vector<int> & v)
{
    const int n = v.size();

    int m = 0;
    vector<int> c(n);

    for (int i = 0; i < n; ++i) {
        c[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (v[j] < v[i] and c[i] < c[j] + 1) {
                c[i] = c[j] + 1;
            }
        }
        m = max(m, c[i]);
    }

    return m;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    vector<int> v;
    v.reserve(1000);

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        v.resize(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        cout << LIS(v) << '\n';
    }

    return 0;
}
