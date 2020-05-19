/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/INVCNT/

    Solution Description
    In order to keep the space complexity linear respect to `n` and to avoid to
    deal with negative numbers, the input array is converted in an array that
    keeps the rank of each element.
    This conversion does not make any change in the answer.

    A Binary Index Tree (BIT) is used to keep track of the already considered
    elements.
    Iterate in reverse order the converted array:
    - the number of inversion of the current element `r` is the number of
      already considered rank values in the BIT that are smaller than `r`. This
      value is calculated with the function `getSum(r - 1)` that returns the
      sum from index 0 to (r - 1).
    - then update the BIT adding 1 at position `r` to keep track of the already
      counted rank

    The sum of the number of inversion of each rank, as described before, is
    the total number of inversion of the array.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define SUBMIT_ONLINE 1
#if !SUBMIT_ONLINE
#include "Structures/BIT.hpp"
#else
template <typename T>
struct BIT
{
    std::vector<T> x;

    BIT(size_t n) :
    x(n + 1)
    {}

    // initialize by a constant
    BIT(size_t n, T a) :
    x(n + 1, a)
    {
        x[0] = 0;
        for (int k = 1; k + (k & -k) <= n; ++k) {
            x[k + (k & -k)] += x[k];
        }
    }

    // initialize by a std::vector
    BIT(std::vector<T> y) :
    x(y.size() + 1)
    {
        for (int k = 0; k < y.size(); ++k) {
            x[k + 1] = y[k];
        }

        for (int k = 1; k + (k & -k) < x.size(); ++k) {
            x[k + (k & -k)] += x[k];
        }
    }

    void clear()
    {
        x.clear();
    }

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

    // sum b[l, r)
    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    // min { k : sum(k) >= a }; it requires b[k] >= 0
    int lower_bound(T a)
    {
        if (a <= 0) {
            return 0;
        }

        int k = x.size() - 1; 
        for (int s: {1, 2, 4, 8, 16}) {
            k |= (k >> s);
        }

        for (int p = ++k; p > 0; p >>= 1, k |= p) {
            if (k < x.size() && x[k] < a) {
                a -= x[k];
            } else {
                k ^= p;
            }
        }
        return k + 1;
    }

    // max { k : sum(k) <= a }; it requires b[k] >= 0
    int upper_bound(T a)
    {
        int k = x.size() - 1; 
        for (int s: {1, 2, 4, 8, 16}) {
            k |= (k >> s);
        }

        for (int p = ++k; p > 0; p >>= 1, k |= p) {
            if (k < x.size() && x[k] <= a) {
                a -= x[k];
            } else {
                k ^= p;
            }
        }
        return k;
    }

    void print()
    {
        for (auto & v : x) {
            std::cout << v << " ";
        }
    }
};
#endif

size_t BIT_inv(vector<int> & v, int n)
{
    // convert to rank
    vector<int> tmp(v);
    sort(tmp.begin(), tmp.end());

    for (size_t i = 0; i < n; ++i) {
        // update the value of v[i] with its rank in the ordered array
        v[i] = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin() + 1;
    }

    size_t invs = 0;
    BIT<size_t> b(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        invs += b.sum(v[i] - 1);
        b.add(v[i], 1);
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

        const size_t result = BIT_inv(v, N);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
