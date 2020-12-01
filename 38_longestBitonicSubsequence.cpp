/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence/0

    Solution Description
    Compute the arrays of LIS (Longest Increasing Subsequence) and the LDS
    (Longest Decreasing Subsequence) of the provided sequence.
    The LBS (Longest Bitonic Subsequence) is found combining the two arrays as
    LBS(i) = LIS(i) + LDS(i) - 1 and then calculate the maximum of all LBS(i).

    Time  Complexity: O(N^2)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> LIS(const vector<int> & v)
    {
        const int n = v.size();

        vector<int> c(n);

        for (int i = 0; i < n; ++i) {
            c[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (v[j] < v[i] and c[i] < c[j] + 1) {
                    c[i] = c[j] + 1;
                }
            }
        }

        return c;
    }

    int LongestBitonicSequence(vector<int> & v)
    {
        const int n = v.size();

        vector<int> lis = LIS(v);
        reverse(v.begin(), v.end());
        vector<int> lds = LIS(v);
        reverse(lds.begin(), lds.end());

        int m = 0;
        for (int i = 0; i < n; ++i) {
            m = max(m, lis[i] + lds[i] - 1);
        }
        return m;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    vector<int> v;
    v.reserve(200);

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        v.resize(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        Solution s;
        cout << s.LongestBitonicSequence(v) << '\n';

        v.clear();
    }

    return 0;
}
