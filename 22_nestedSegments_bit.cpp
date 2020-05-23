/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/652/D

    Solution Description
    Sort the segments <l_i, r_i> by r_i and calculate the rank of each segment.
    Sort segments <l_i, r_i> in decreasing order by l_i.
    Make use of a BIT (Binary Index Tree) to keep track, using the rank as
    index, of the already visited segments. For each segment processed, add 1 to
    the BIT at its rank, then get the sum from 0 to to its r_i, that is the
    number of nested segments.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

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


//            tuple<left, right, rank>
#define RANGE tuple<int, int, int>
#define LEFT    0
#define RIGHT   1
#define RANK    2

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector< RANGE > v(N);
    BIT<int> b(N);
    vector<int> results(N);

    for (int n = 0; n < N; ++n) {
        int left;
        int right;
        cin >> left;
        cin >> right;
        v[n] = make_tuple(left, right, n);
    }

    // sort by right in increasing order
    sort(v.begin(), v.end(),
        [](const RANGE & lhs, const RANGE & rhs) {
            return get<RIGHT>(lhs) < get<RIGHT>(rhs);
        });

    // tuple<left, sorted_rank_right, rank>
    for (int n = 0; n < N; ++n) {
        get<RIGHT>(v[n]) = n;
    }

    // sort by left in decreasing order
    sort(v.begin(), v.end(),
        [](const RANGE & lhs, const RANGE & rhs) {
            return get<LEFT>(lhs) > get<LEFT>(rhs);
        });

    for (int n = 0; n < N; ++n) {
        const int right = get<RIGHT>(v[n]);
        const int rank = get<RANK>(v[n]);
        results[rank] = b.sum(right);
        b.add(right, 1);
    }

    for (int n = 0; n < N; ++n) {
        cout << results[n] << endl;
    }

    results.clear();
    b.clear();
    v.clear();

    return 0;
}
