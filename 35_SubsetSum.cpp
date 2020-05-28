/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/subset-sum-problem/0

    Solution Description
    Let be S the sum of all values. If is odd, there is no solution. Otherwise
    we can restate the problem as follows: check if there is a subset of the
    provided values such as the sum is equal to S/2.
    This problem is solved with dynamic programming.
    Create a boolean matrix K with (N+1) rows and (S/2+1) columns, where N is
    the number of values.  We can calculate each element of K as follows:
    - K[0][j] = F                                                  with j > 0
    - K[i][0] = T                                                  with i >= 0
    - K[i][j] = K[i -1][j - 1] OR K[i - 1][j - v[i]]               if j >= v[i]
    - K[i][j] = K[i -1][j - 1]                                     otherwise
    The row 0 is the empty set. Column j-th a subproblem with sum equal to j.
    The first line means that we have no items, so, if S/2 > 0, there is no
    solution.
    The second line means that we have to find a subset with sum = 0, so the
    solution is possible (the empty-set).
    The third one checks if a previous solution is already found OR if a
    solution with sum = j - v[i] is found and hence, adding the current value to
    the subset, a solution is found for sum = j.
    The forth one checks only for a previous solution since (j - v[i]) is a
    negative sum.

    The solution require a matrix with O(N * S) elements. The provided solution
    make use of an optimization in terms of space complexity. Since the
    algorithm need the previous and the current row of that matrix, we store
    only 2 * (S + 1) elements.

    Time  Complexity: O(N * S)
    Space Complexity: O(N + S)
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


bool subsetSum(const vector<int> & v)
{
    const int n = v.size();

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += v[i];
    }

    if (sum & 1) return false;

    sum /= 2;

    vector<bool> p(sum + 1, false);
    vector<bool> c(sum + 1, false);

    p[0] = c[0] = true;

    for (int i = 0; i < n; ++i) {
        swap(p, c);
        for (int j = 1; j <= sum; ++j) {
            c[j] = p[j] or (j >= v[i] ? p[j - v[i]] : false);
        }
    }

    return c[sum];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        vector<int> v(N);

        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        bool result = subsetSum(v);
        cout << (result ? "YES" : "NO");
        cout << endl;

        v.clear();
    }

    return 0;
}
