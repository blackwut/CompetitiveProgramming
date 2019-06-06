/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/INVCNT/

    Solution Description
    Using Divide and Conquer approach to calculate the number of inversions.
    This algorithm is based on mergesort, so we split the array in two
    (call them left and right) with equal number.
    Suppose we know the number of inversions in both arrays. The number of total
    inversions is calculated as:
    invs = invs(left) + invs(right) + invs(merge(left, right))
    The number of inversions at each step in the merge process are:
    if a[i] > a[j], then there are (m – i) inversions.
    Summing them together we have the number of inversions in the merge phase.

    Time  Complexity: O(N log_2 N)
    Space Complexity: O(N)
*/

#include <iostream>
using namespace std;

size_t _merge_inv(int * a, int * tmp, size_t l, size_t m, size_t r)
{
    size_t invs = 0;
    size_t i = l;
    size_t j = m;
    size_t k = l;

    while ( (i < m) && (j < r) ){
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            invs += (m - i);
        }
    }

    while (i < m) {
        tmp[k++] = a[i++];
    }

    while (j < r) {
        tmp[k++] = a[j++];
    }

    for (k = l; k < r; ++k) {
        a[k] = tmp[k];
    }

    return invs;
}

size_t _mergesort_inv(int * a, int * tmp, size_t l, size_t r)
{
    size_t invs = 0;
    if (l < r) {
        size_t m = l + (r - l) / 2;
        invs  = _mergesort_inv(a, tmp, l, m);
        invs += _mergesort_inv(a, tmp, m + 1, r);
        invs += _merge_inv(a, tmp, l, m + 1, r + 1);
    }
    return invs;
}

size_t mergesort_inv(int * a, size_t n)
{
    int * tmp = (int *)malloc(n * sizeof(int));
    size_t invs = _mergesort_inv(a, tmp, 0, n - 1);
    free(tmp);
    return invs;
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

        int * a = (int *)malloc(N * sizeof(int));
        for (int n = 0; n < N; ++n) {
            cin >> a[n];
        }

        size_t result = mergesort_inv(a, N);
        cout << result;
        cout << endl;

        free(a);
    }

    return 0;
}
