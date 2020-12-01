/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/edit-distance/0

    Solution Description
    The problem is solved with dynamic programming.
    Let be A[1, N] and B[1, M] the two strings with N and M characters
    respectively.
    Create a matrix K with (N+1) rows and (M+1) columns. Each element K[i][j]
    represents the minimum number of operations required to edit A[1, i]
    to match B[1, j].
    We can calculate each element of such matrix as follows:
    - K[0][j] = j                                                j >= 0
    - K[i][0] = i                                                i >= 0
    - K[i][j] = K[i-1][j-1]                                      if A[i] == B[i]
    - K[i][j] = min(K[i][j-1], K[i-1][j-1], K[i-1][j]) + 1       otherwise
    The first line ensure that if A is the empty string, or it is totally
    different from B, for each j we have exactly j operation required.
    The second line has the same purpose, but now B is the empty string or it is
    totally different from A.
    The third one, since A[i] and B[j] are equal, copy the previous result in
    which A[i-1] and B[j-1] were equal after the minimum edit operations.
    The forth one consider an edit operation since A[i] != B[j], so it takes the
    minimum operations calculated previously and add 1 (the current edit).

    The solution requires a matrix with O(N * M) elements. The provided solution
    make use of an optimization in terms of space complexity. Since the
    algorithm needs the previous and the current row of that matrix, we store
    only 2 * (M + 1) elements.

    Time  Complexity: O(N * M)
    Space Complexity: O(N + M)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int editDistance(const string & a, const string & b)
    {
        const int n = a.size();
        const int m = b.size();

        vector<int> p(m + 1);
        vector<int> c(m + 1);

        for (int j = 0; j <= m; ++j) {
            c[j] = j;
        }

        for (int i = 1; i <= n; ++i) {
            swap(p, c);
            p[0] = i - 1;
            c[0] = i;
            for (int j = 1; j <= m; ++j) {
                if (a[i - 1] == b[j - 1]) {
                    c[j] = p[j - 1];
                } else {
                    c[j] = min({p[j - 1], p[j], c[j - 1]}) + 1;
                }
            }
        }

        return c[m];
    }
};

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
        Solution s;
        cout << s.editDistance(a, b) << '\n';
    }

    return 0;
}
