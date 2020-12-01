#pragma once

//
// Modified code found at https://github.com/spaghetti-source/algorithm/blob/master/data_structure/fenwick_tree.cc
//

// Fenwick Tree (aka. binary indexed tree)
//
// Description:
//   A data structure that allows 
//     add(k,a):       b[k] += a
//     sum(k):         b[0] + ... + b[k-1]
//     lower_bound(a): min { k : sum(k) >= a }
//
// Algorithm:
//  [                    1000                     ]
//  [         100         ] [                     ]
//  [   010   ] [         ] [   110   ] [         ]
//  [001] [   ] [011] [   ] [101] [   ] [111] [   ]
//
//  - x[k] maintains the segment b[*,k).
//  - k + (k & (k + 1)) is the immediate ancestor of k
//  - k - (k & (k - 1)) is the rightmost left segment of k
//
// Complexity:
//   O(log n) access, n space.
//

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct BIT
{
    vector<T> b;

    BIT() = default;

    BIT(int n)
    : b(n + 1)
    {}

    BIT(int n, T a)
    : b(n + 1, a)
    {
        build(n);
    }

    BIT(const vector<T> v)
    : b(v.size() + 1)
    {
        const int n = v.size();
        for (int k = 0; k < n; ++k) {
            b[k + 1] = v[k];
        }
        build(n);
    }

    void build(int n) {
        b[0] = 0;
        for (int k = 1; k + (k & -k) <= n; ++k) {
            b[k + (k & -k)] += b[k];
        }
    }

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

    T query(int l, int r) { // sum in range [l, r)
        return query(r) - query(l - 1);
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
