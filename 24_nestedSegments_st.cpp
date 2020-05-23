/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/652/D?locale=en

    Solution Description
    Sort the segments <l_i, r_i> by r_i and calculate the rank of each segment.
    Sort segments <l_i, r_i> in decreasing order by l_i.
    Make use of a ST (Segment Tree to keep) track, using the rank as index, of
    the already visited segments. For each segment processed, add 1 to
    the ST at its rank, then get the sum from 0 to its r_i, that is the number
    of nested segments.

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
#include "Structures/SegmentTree.hpp"
#else
#include <functional>

template<typename T>
struct SegmentTree
{
private:
    int n;
    vector<T> tree;
    function<T(const T &, const T &)> op;
    T id;

public:

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
            tree[n + 1] = val;
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
            tree[n + 1] = v[i];
        }

        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void update(int pos, T delta)
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
};
#endif


#define RANGE tuple<int, int, int>
#define R_LEFT    0
#define R_RIGHT   1
#define R_RANK    2

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    // <left, right, rank>
    vector< RANGE > v(N);
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
            return get<R_RIGHT>(lhs) < get<R_RIGHT>(rhs);
        });

    // tuple<left, sorted_rank_right, rank>
    for (int n = 0; n < N; ++n) {
        get<R_RIGHT>(v[n]) = n;
    }

    // sort by left in decreasing order
    sort(v.begin(), v.end(),
        [](const RANGE & lhs, const RANGE & rhs) {
            return get<R_LEFT>(lhs) > get<R_LEFT>(rhs);
        });

    auto sumOp = [](const int & lhs, const int & rhs){ return lhs + rhs; };
    SegmentTree<int> st(sumOp, 0);
    st.buildConstant(N, 0);

    for (int n = 0; n < N; ++n) {
        const int id = get<R_RIGHT>(v[n]);
        const int rank = get<R_RANK>(v[n]);
        results[rank] = st.query(0, id);
        st.update(id, 1);
    }

    for (int n = 0; n < N; ++n) {
        cout << results[n] << endl;
    }
    cout << endl;

    results.clear();
    v.clear();

    return 0;
}
