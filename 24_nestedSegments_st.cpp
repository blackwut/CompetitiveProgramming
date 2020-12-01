/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/652/D?locale=en

    Solution Description
    The i-th segment is stored as a tuple <l_i, r_i>.
    Sort the segments by r_i and replace r_i with its rank.
    Sort again the segments in decreasing order by l_i.
    Make use of a Segment Tree to keep track of the already visited segments.
    For each segment processed do the following:
    - add 1 at position r_i to the Segment Tree
    - then get the sum querying the range [0, r_i), that represents the number
      of nested segments

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

    // Build after manual initialization of values
    void build() {
        for (int i = n - 1; i > 0; --i) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
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
};

template <typename T>
struct Operator
{
    static T op(const T & a, const T & b) { return a + b; };
    static const T id = 0;
};

struct Seg
{
    int l;
    int r;
    int i;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Seg> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n].l;
        cin >> v[n].r;
        v[n].i = n;
    }

    // sort by right in increasing order and replace r_i with its rank
    auto compR = [](const Seg & lhs, const Seg & rhs) { return lhs.r < rhs.r; };
    sort(v.begin(), v.end(), compR);
    for (int n = 0; n < N; ++n) {
        v[n].r = n;
    }

    // sort by left in decreasing order
    auto compL = [](const Seg & lhs, const Seg & rhs) { return lhs.l > rhs.l; };
    sort(v.begin(), v.end(), compL);

    SegmentTree<int, Operator<int>::op, Operator<int>::id> st;
    st.build(N, 0);
    vector<int> result(N);
    for (int n = 0; n < N; ++n) {
        result[v[n].i] = st.query(0, v[n].r);
        st.increment(v[n].r, 1);
    }

    for (const auto & r : result) {
        cout << r << '\n';
    }

    return 0;
}
