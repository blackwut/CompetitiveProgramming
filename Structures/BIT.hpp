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
