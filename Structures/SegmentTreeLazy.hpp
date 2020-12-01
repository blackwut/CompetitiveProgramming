#pragma once
#include <vector>

/*
    Inspired by https://codeforces.com/blog/entry/18051

    Example usage:
        template <typename T>
        struct Operator
        {
            static T op(const T & a, const T & b) { return a < b ? a : b; };
            static const T id = numeric_limits<T>::max();
        };
        ...
        SegmentTree<int, Operator<int>::op, Operator<int>::id> st;
*/

template<typename T, T (op)(const T &, const T &), T id>
struct SegmentTree
{
    int n;
    int h;
    vector<T> tree;
    vector<T> lazy;

    // Build with constant value v
    void build(int s, const T v) {
        n = s;
        h = sizeof(int) * 8 - __builtin_clz(n);
        tree.resize(2 * n, v);
        lazy.resize(n, 0);
        build();
    }

    // Build from a given vector
    void build(const vector<T> & v) {
        n = v.size();
        h = sizeof(int) * 8 - __builtin_clz(n);
        tree.resize(2 * n, id);
        lazy.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            tree[n + i] = v[i];
        }
        build();
    }

    // Build after manual initialization of values
    void build() {
        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Update all the parents of a given node
    void build(int p) {
        while (p > 1) {
            p >>= 1;
            tree[p] = op(tree[p << 1], tree[p << 1 | 1]) + lazy[p];
        }
    }

    // Helper function
    void apply(int p, const T v) {
        tree[p] += v;
        if (p < n) lazy[p] += v;
    }

    // Propagates changes from all the parents of a given node down the tree
    // Parents are exactly the prefixes of p in binary notation
    void push(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (lazy[i] != 0) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

    // Change the value of a single element
    void change(int p, const T v) {
        for (tree[p += n] = v; p > 1; p >>= 1) {
            tree[p >> 1] = op(tree[p], tree[p ^ 1]);
        }
    }

    // Add v to elements in the range [l, r)
    void increment(int l, int r, const T v) {
        l += n;
        r += n;
        int l0 = l;
        int r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, v);
            if (r & 1) apply(--r, v);
        }
        build(l0);
        build(r0 - 1);
    }

    // Query on range [l, r)
    T query(int l, int r) {
        l += n;
        r += n;
        push(l);
        push(r - 1);
        T resl = id;
        T resr = id;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = op(resl, tree[l++]);
            if (r & 1) resr = op(tree[--r], resr);
        }
        return op(resl, resr);
    }

    // Using reserve() can prevent unnecessary reallocations
    void reserve(int n) {
        tree.reserve(2 * n);
        lazy.reserve(n);
    }

    // Resize the Segment Tree with a constant value
    void resize(int n, const T a = id) {
        tree.resize(2 * n, a);
        lazy.resize(n);
    }

    // Remove all elements
    void clear() {
        n = 0;
        h = 0;
        tree.clear();
        lazy.clear();
    }
};
