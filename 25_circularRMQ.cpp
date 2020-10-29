/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/52/C

    Solution Description
    Make use of a SegmentTree with lazy propagation.
    Let l and r the left and the right index of the array respectively.
    Since we are simulating a Circular array, if l <= r we make RMQ and INC
    from l to r, otherwise make them from 0 to r and from l to N - 1.

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

template<typename T>
struct SegmentTreeLazy
{
private:

#define LEFT(i)     ((i << 1) + 1)
#define MID(i, j)   ((l) + ((r) - (l)) / 2)
#define RIGHT(i)    ((i << 1) + 2)

    size_t n;
    vector<T> tree;
    vector<T> lazy;
    function<T(const T &, const T &)> op;
    T id;

    void build(const vector<T> & v, size_t l, size_t r, size_t i)
    {
        // out of range
        if (l > r) return;

        // leaf
        if (l == r) {
            tree[i] = v[l];
            return;
        }

        const size_t m = MID(l, r);
        build(v, l,     m, LEFT(i));
        build(v, m + 1, r, RIGHT(i));
        tree[i] = op(tree[LEFT(i)], tree[RIGHT(i)]);
    }

    void updateRangeUtil(size_t l,  size_t r,
                         size_t ul, size_t ur,
                         size_t i, T diff)
    {
        if (lazy[i] != 0) {
            tree[i] += lazy[i];
            if (l != r) {
                lazy[LEFT(i)]  += lazy[i];
                lazy[RIGHT(i)] += lazy[i];
            }
            lazy[i] = 0;
        } 

        // out of range
        if (l > r or l > ur or r < ul) return;

        // total overlap
        if (l >= ul and r <= ur) {
            tree[i] += diff;
            if (l != r) {
                lazy[LEFT(i)]  += diff;
                lazy[RIGHT(i)] += diff;
            }
            return;
        }

        // partial overlap
        const size_t m = MID(l, r);
        updateRangeUtil(l,     m, ul, ur, LEFT(i),  diff);
        updateRangeUtil(m + 1, r, ul, ur, RIGHT(i), diff);
        tree[i] = op(tree[LEFT(i)], tree[RIGHT(i)]);
    }

    T query(size_t l, size_t r, size_t ql, size_t qr, size_t i)
    {
        if (lazy[i] != 0) {
            tree[i] += lazy[i];
            if (l != r) {
                lazy[LEFT(i)]  += lazy[i];
                lazy[RIGHT(i)] += lazy[i];
            }
            lazy[i] = 0;
        } 

        // out of range
        if (l > r or l > qr or r < ql) return id;

        // total overlap
        if (l >= ql and r <= qr) return tree[i];

        // partial overlap
        const size_t m = MID(l, r);
        return op(query(l,     m, ql, qr, LEFT(i)),
                  query(m + 1, r, ql, qr, RIGHT(i))
               );
    }

    size_t nextPowerOfTwo(size_t v)
    {
        return size_t(1) << static_cast<size_t>(ceil(log2(v)));
    }

public:

    SegmentTreeLazy(function<T(const T &, const T &)> binaryOperation,
                    const T identityValue)
    : op(binaryOperation)
    , id(identityValue)
    {}

    ~SegmentTreeLazy() { tree.clear(); lazy.clear(); }

    void build(const vector<T> & v)
    {
        n = v.size();
        const size_t nn = nextPowerOfTwo(n);
        tree.resize(2 * nn - 1, id);
        lazy.resize(2 * nn - 1, 0);

        build(v, 0, n - 1, 0);
    }

    void updateRange(size_t l, size_t r, T diff) 
    {
        updateRangeUtil(0, n - 1, l, r, 0, diff);
    }

    T query(size_t l, size_t r)
    {
        return query(0, n - 1, l, r, 0);
    }
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

    auto op = [](const int64_t & lhs, const int64_t & rhs) {
                  return (lhs < rhs) ? lhs : rhs;
              };
    SegmentTreeLazy<int64_t> st(op, numeric_limits<int64_t>::max());
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
                cout << st.query(l, r) << '\n';
            } else {
                cout << op(st.query(0, r), st.query(l, N - 1)) << '\n';
            }
        } else { // INC
            if (l <= r) {
                st.updateRange(l, r, x);
            } else {
                st.updateRange(0, r    , x);
                st.updateRange(l, N - 1, x);
            }
        }
    }

    v.clear();

    return 0;
}
