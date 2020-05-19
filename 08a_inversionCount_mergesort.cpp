/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/INVCNT/
    Compiler: C++ (gcc 8.3), C++14 (gcc 8.3), C++14 (clang 8.0)

    Solution Description
    Using Divide & Conquer approach to calculate the number of inversions.
    This algorithm is based on Mergesort. The vector is split into two equal
    parts (left and right)
    Suppose that the number of inversions in both arrays is known, the number
    of total inversions is calculated as:
    invs = invs(left) + invs(right) + invs(merge(left, right))
    The number of inversions at each step in the merge process are:
    if v[i] > v[j] there are (m – i) inversions.
    Summing them together we have the number of inversions.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>

using namespace std;

size_t _merge_inv(vector<int> & v,
                  vector<int> & tmp,
                  const size_t l,
                  const size_t m,
                  const size_t r)
{
    size_t invs = 0;
    size_t i = l;
    size_t j = m;
    size_t k = l;

    while ( (i < m) && (j < r) ){
        if (v[i] <= v[j]) {
            tmp[k++] = v[i++];
        } else {
            tmp[k++] = v[j++];
            invs += (m - i);
        }
    }

    while (i < m) {
        tmp[k++] = v[i++];
    }

    while (j < r) {
        tmp[k++] = v[j++];
    }

    for (k = l; k < r; ++k) {
        v[k] = tmp[k];
    }

    return invs;
}

size_t _mergesort_inv(vector<int> & v,
                      vector<int> & tmp,
                      const size_t l,
                      const size_t r)
{
    size_t invs = 0;

    if (l < r) {
        const size_t m = l + (r - l) / 2;
        invs  = _mergesort_inv(v, tmp, l, m);
        invs += _mergesort_inv(v, tmp, m + 1, r);
        invs += _merge_inv(v, tmp, l, m + 1, r + 1);
    }

    return invs;
}

size_t mergesort_inv(vector<int> & v,
                     const size_t n)
{
    vector<int> tmp(v);
    return _mergesort_inv(v, tmp, 0, n - 1);
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

        const size_t result = mergesort_inv(v, N);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
