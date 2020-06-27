#pragma once

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template<typename T>
struct SegmentTree
{
private:
    int n;
    vector<T> tree;

public:
    function<T(const T &, const T &)> op;
    T id;

    SegmentTree(function<T(const T &, const T &)> binaryOperation,
                const T identityValue)
    : op(binaryOperation),
      id(identityValue)
    {}

    void buildConstant(const int size, const T & val)
    {
        n = size;
        tree.resize(2 * n, id);
        for(int i = 0; i < n; ++i) {
            tree[n + i] = val;
        }

        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void build(const vector<T> & v)
    {
        n = v.size();
        tree.resize(2 * n, id);
        for(int i = 0; i < n; ++i) {
            tree[n + i] = v[i];
        }

        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void update(int pos, T val)
    {
        tree[n + pos] = val;

        for (int i = pos + n; i > 1; i >>= 1) {
            tree[i >> 1] = op(tree[i], tree[i ^ 1]);
        }
    }

    void updateDelta(int pos, T delta)
    {
        tree[n + pos] += delta;

        for (int i = pos + n; i > 1; i >>= 1) {
            tree[i >> 1] = op(tree[i], tree[i ^ 1]);
        }
    }

    T query(int l, int r)
    {
        T result = id;

        l += n;
        r += n;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) result = op(result, tree[l++]);
            if (r & 1) result = op(result, tree[--r]);
        }
        return result;
    }

    void print()
    {
        cout << "SegmentTree" << endl;
        for (const auto & v : tree) {
            cout << v << " ";
        }
        cout << endl;
    }
};
