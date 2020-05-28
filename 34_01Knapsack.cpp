/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/KNAPSACK/

    Solution Description
    The problem is solved with dynamic programming.
    Let be w_i and v_i the weight and value of each i-th item respectively.
    Create a matrix K with (N+1) rows and (S+1) columns, where N is the number
    of items and S the maximum capacity. Each element K[i][j] in this matrix
    represent the maximum value calculated using items from 1 to i and with j
    weight at maximum.
    We can calculate each element of such matrix as follows:
    - K[0][j] = 0
    - K[i][0] = 0
    - K[i][j] = max( k[i - 1][j], k[i][j - w[i]] + v[i])
    The first line means that we have no items, so no value.
    The second line means that we have no capacity, so no value.
    The third one calculate the maximum between the previous calculated value,
    not including the current item, and the value of the current item plus the
    value calculated with (j - w[i]) maximum capacity.
    The solution can be found at K[N + 1][S + 1]

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


int knapsack01(const vector<int> & w, const vector<int> & v, const int S)
{
    if (S == 0) return 0;

    vector<int> p(S + 1);
    vector<int> c(S + 1);

    const int n = v.size();
    for (int i = 0; i < n; ++i) {
        swap(p, c);
        for (int j = 1; j <= S; ++j) {
            c[j] = max(p[j], (j >= w[i]) ? p[j - w[i]] + v[i] : 0);
        }
    }

    return c[S];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int S;
    cin >> S;

    int N;
    cin >> N;

    vector<int> w(N);
    vector<int> v(N);

    for (int n = 0; n < N; ++n) {
        cin >> w[n];
        cin >> v[n];
    }

    int result = knapsack01(w, v, S);
    cout << result;
    cout << endl;

    v.clear();
    w.clear();

    return 0;
}
