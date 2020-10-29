/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/INVCNT/
    Compiler: C++ (gcc 8.3), C++14 (gcc 8.3), C++14 (clang 8.0)

    Solution Description
    This solution is based on Binary Indexed Tree (BIT).
    In order to keep the space complexity linear respect to N and to avoid to
    deal with negative numbers, the input array is sorted and then is converted
    in an array that keeps the rank of each element. This conversion does not
    make any change in the answer.

    The BIT is used to keep track of the already considered elements.
    Iterate in reverse order the converted array:
    - the number of inversion of the current element r is the number of already
      considered rank values in the BIT that are smaller than r
    - then update the BIT adding 1 at position r to keep track of the already
      counted rank

    The sum of the number of inversion of each rank is the total number of
    inversion of the array.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
struct BIT
{
    vector<T> b;

    BIT(size_t n)
    : b(n + 1)
    {}

    void increment(int k, T a) { // b[k] += a
        const int n = static_cast<int>(b.size());
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
};

template <typename T>
size_t BIT_inv(vector<T> & v, int n)
{
    // convert to rank
    vector<T> tmp(v);
    sort(tmp.begin(), tmp.end());
    for (auto & val : v) {
        val = lower_bound(tmp.begin(), tmp.end(), val) - tmp.begin();
    }

    size_t invs = 0;
    BIT<size_t> b(n);
    for (int i = n - 1; i >= 0; --i) {
        invs += b.query(v[i]);
        b.increment(v[i], 1);
    }

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

        vector<int> v(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        cout << BIT_inv(v, N) << '\n';
    }

    return 0;
}
