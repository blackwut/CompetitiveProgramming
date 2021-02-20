#pragma once
#include <vector>

/*
    Inspired by https://codeforces.com/blog/entry/18051

    // Create an operator and instantiate the Segment-Tree
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
    vector<T> tree;

    // Build with constant value v
    void build(int s, const T v) {
        n = s;
        tree.resize(2 * n, v);
        build();
    }

    // Build from a given vector
    void build(const vector<T> & v) {
        n = v.size();
        tree.resize(2 * n, id);
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
            tree[p] = op(tree[p << 1], tree[p << 1 | 1]);
        }
    }

    // Change the value of a single element
    void change(int p, const T v) {
        for (tree[p += n] = v; p > 1; p >>= 1) {
            tree[p >> 1] = op(tree[p], tree[p ^ 1]);
        }
    }

    // Add v to a single element
    void increment(int p, const T v) {
        for (tree[p += n] += v; p > 1; p >>= 1) {
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
            if (l & 1) tree[l++] += v;
            if (r & 1) tree[--r] += v;
        }
        build(l0);
        build(r0 - 1);
    }

    // Query on range [l, r)
    T query(int l, int r) {
        l += n;
        r += n;
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
    }

    // Resize the Segment Tree with a constant value
    void resize(int n, const T a = id) {
        tree.resize(2 * n, a);
    }

    // Remove all elements
    void clear() {
        n = 0;
        tree.clear();
    }
};
