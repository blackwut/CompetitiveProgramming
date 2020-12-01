/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence/0

    Solution Description
    The problem is solved with dynamic programming. Let be A[1, N] a strings
    with N characters and B[1, N] the reversed string of A.
    The LPS (Longest Palindromic Subsequence) is calculated as followings:
     - 0                                                         if i > j
     - 1                                                         if i == j
     - 2 + LPS(i, j - 1)                                         if A[i] == B[j]
     - max(LPS(i - 1, j), LPS(i, j - 1))                         otherwise
    The first line is because the two substrings have different size.
    The second line is because we are comparing two characters at the same
    position.
    The third one means that, since we found the same character but in different
    position, we could extend the longest palindromic sequence by pre-pending
    and appending this character, hence we extend by two the LPS.
    The forth one bring ahead the max LPS.

    The solution requires a matrix with O(N^2) elements. The provided solution
    makes use of an optimization in terms of space complexity. Since the
    algorithm needs the previous and the current row of that matrix, we store
    only 2 * (N + 1) elements.

    Time  Complexity: O(N^2)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LPS(const string & a)
{
    const int n = a.size();

    vector<int> p(n);
    vector<int> c(n);

    for (int i = n - 2; i >= 0; --i) {
        swap(p, c);
        p[i + 1] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]) {
                c[j] = 2 + p[j - 1];
            } else {
                c[j] = max(p[j], c[j - 1]);
            }
        }
    }

    return c[n - 1];
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        string a;
        cin >> a;

        cout << LPS(a) << '\n';
    }

    return 0;
}
