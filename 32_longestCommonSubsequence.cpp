/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0

    Solution Description
    The problem is solved with dynamic programming.
    Let be A[1, N] and B[1, M] two strings with N and M characters respectively.

    Suppose that we already know the followings:
     - LCS(A[1, i-1], B[1, j-1])
     - LCS(A[1, i  ], B[1, j-1])
     - LCS(A[1, i-1], B[1, j  ])

    We can compute LCS(A[1, i], B[1, j]) as follows:
     - 0                                                     if i and j are zero
     - LCS(A[1, i-1], B[1, j-1]) + 1                         if A[i] == B[j]
     - max(LCS(A[1, i-1], LCS(B[1, j]), LCS(A[1, i], LCS(B[1, j-1]))   otherwise

    The first line is for boundary reason.
    The second line is because we are extending the previous LCS knowing that
    A[i] and B[j] are equal, hence a new character must be added to the LCS.
    Since A[i] and B[j] are not equal, the third line permits to go on keeping
    the best result up to now.

    The solution requires a matrix with N * M elements. The provided solution
    makes use of an optimization in terms of space complexity. Since the
    algorithm needs the previous and the current row of that matrix, we store
    only 2 * M elements.

    Time  Complexity: O(N * M)
    Space Complexity: O(N + M)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LCS(const string & a, const string & b)
{
    const int n = a.size();
    const int m = b.size();

    vector<int> p(m + 1);
    vector<int> c(m + 1);

    for (int i = 0; i < n; ++i) {
        swap(p, c);
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                c[j + 1] = p[j] + 1;
            } else {
                c[j + 1] = max(c[j], p[j + 1]);
            }
        }
    }

    return c[m];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int n;
        int m;
        string a;
        string b;

        cin >> n;
        cin >> m;
        cin >> a;
        cin >> b;

        cout << LCS(a, b) << '\n';
    }

    return 0;
}
