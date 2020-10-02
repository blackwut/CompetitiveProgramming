/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/UPDATEIT/

    Solution Description
    Let be L and R the left position and the right position respectively of the
    range [L, R] (both included) where we update the array with the value V.
    Create an array with N + 1 elements with value 0.
    Each update can be made adding V at position L and -V at position R + 1.
    Then prefix sum the array.
    Each query can be found in constant time getting the value at the requested
    position.

    The previous solution can be solved similarly with Binary Index Tree (BIT).

    Array Solution
    Time  Complexity: O(N + Q)
    Space Complexity: O(N)

    BIT Solution
    Time  Complexity: O((U + Q) * log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

#define ARRAY_SOLUTION 0
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
            cout << b[i] << endl;
        }

        b.clear();
    }

    return 0;
}

#else // BIT solution
template <typename T>
struct BIT
{
    std::vector<T> x;

    BIT(size_t n)
    : x(n + 1)
    {}

    // b[k] += a
    void add(int k, T a)
    {
        for (++k; k < x.size(); k += k & -k) {
            x[k] += a;
        }
    }
  
    // sum b[0,k)
    T sum(int k)
    {
        T s = 0;
        for (++k; k > 0; k &= k - 1) {
            s += x[k];
        }
        return s;
    }

    void clear()
    {
        x.clear();
    }
};

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

        BIT<int> b(N);
        for (int u = 0; u < U; ++u) {
            int l;
            int r;
            int v;
            cin >> l;
            cin >> r;
            cin >> v;
            b.add(l, v);
            b.add(r + 1, -v);
        }

        int Q;
        cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int i;
            cin >> i;
            cout << b.sum(i) << '\n';
        }

        b.clear();
    }

    return 0;
}

#endif
