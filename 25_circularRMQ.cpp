/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/52/C

    Solution Description
    Make use of a SegmentTree with lazy propagation.
    Let l and r the left and the right index of the array respectively.
    Since we are simulating a Circular array, if l <= r we perform RMQ and INC
    from l to r, otherwise perform them from 0 to r and from l to N - 1.

    Time  Complexity: O(N + M log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <functional>
#include <cmath>
#include <sstream>
using namespace std;

template<typename T, T (op)(const T &, const T &), T id>
struct SegmentTree
{
    int n;
    int h;
    vector<T> tree;
    vector<T> lazy;

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
};

template <typename T>
struct Operator
{
    static T op(const T & a, const T & b) { return a < b ? a : b; };
    static const T id = numeric_limits<T>::max();
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int64_t> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n];
    }

    SegmentTree<int64_t, Operator<int64_t>::op, Operator<int64_t>::id> st;
    st.build(v);

    int M;
    cin >> M;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int m = 0; m < M; ++m) {
        bool RMQ = true;
        int l;
        int r;
        int64_t x = 0;

        string line;
        getline(cin, line);
        istringstream iss(line);

        iss >> l;
        iss >> r;
        if (!iss.eof()) {
            RMQ = false;
            iss >> x;
        }

        if (RMQ) {
            if (l <= r) {
                cout << st.query(l, r + 1) << '\n';
            } else {
                cout << Operator<int64_t>::op(st.query(0, r + 1),
                                              st.query(l, N)) << '\n';
            }
        } else { // INC
            if (l <= r) {
                st.increment(l, r + 1, x);
            } else {
                st.increment(0, r + 1, x);
                st.increment(l, N    , x);
            }
        }
    }

    return 0;
}
