/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/UPDATEIT/

    Solution Description
    Let be L and R respectively the left position and the right position of the
    range [L, R] (both included) where we update the array with the value v.
    Create an array with N + 1 elements with value 0.
    Each update is made by adding v at position L and -v at position R + 1.
    Then prefix sum the array.
    Each query is computed in constant time getting the value at the requested
    position.

    The previous solution can be solved similarly with Binary Index Tree (BIT).

    Array Solution
    Time  Complexity: O(U + N + Q)
    Space Complexity: O(N)

    BIT Solution
    Time  Complexity: O((U + Q) * log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

#define ARRAY_SOLUTION 1
#if ARRAY_SOLUTION

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        int U;
        cin >> N;
        cin >> U;

        vector<int> b(N + 1);
        for (int u = 0; u < U; ++u) {
            int l;
            int r;
            int v;
            cin >> l;
            cin >> r;
            cin >> v;
            b[l] += v;
            b[r + 1] -= v;
        }

        for (int i = 1; i < N; ++i) {
            b[i] += b[i - 1];
        }

        int Q;
        cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int i;
            cin >> i;
            cout << b[i] << '\n';
        }
    }

    return 0;
}

#else // BIT solution

template <typename T>
struct BIT
{
    vector<T> b;

    void increment(int k, T a) { // b[k] += a
        const int n = b.size();
        for (++k; k < n; k += k & -k) {
            b[k] += a;
        }
    }

    T query(int k) { // sum in the range [0, k)
        T s = 0;
        for (++k; k > 0; k &= k - 1) {
            s += b[k];
        }
        return s;
    }

    void reserve(int n) {
        b.reserve(n + 1);
    }

    void resize(int n, const T a) {
        b.resize(n + 1, a);
    }

    void clear() {
        b.clear();
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    BIT<int> b;
    b.reserve(10000);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        int U;
        cin >> N;
        cin >> U;

        b.resize(N, 0);
        for (int u = 0; u < U; ++u) {
            int l;
            int r;
            int v;
            cin >> l;
            cin >> r;
            cin >> v;
            b.increment(l, v);
            b.increment(r + 1, -v);
        }

        int Q;
        cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int i;
            cin >> i;
            cout << b.query(i) << '\n';
        }

        b.clear();
    }

    return 0;
}

#endif
