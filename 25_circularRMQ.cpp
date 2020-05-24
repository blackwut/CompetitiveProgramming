/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/52/C

    Solution Description
    Make use of a SegmentTree with lazy propagation.
    Let l and r the left and the right index of the array respectively.
    Since we are simulating a Circular array, if l <= r we make RMQ and INC
    from l to r, otherwise make them from 0 to r and from l to size - 1.

    Time  Complexity: O( N + M log N )
    Space Complexity: O( N )
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

#define SUBMIT_ONLINE 1
#if !SUBMIT_ONLINE
#include "Structures/SegmentTreeLazy.hpp"
#else
#include <functional>
#include <cmath>

using namespace std;

#define LEFT(i)     ((i << 1) + 1)
#define RIGHT(i)    ((i << 1) + 2)
#define PARENT(i)   ((i - 1) >> 1)

template<typename T>
struct SegmentTreeLazy
{
private:
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

        const size_t m = l + (r - l) / 2;
        build(v, l, m, LEFT(i));
        build(v, m + 1, r, RIGHT(i));

        tree[i] = op(tree[LEFT(i)], tree[RIGHT(i)]);
    }

    void updateRangeUtil(size_t i, size_t l, size_t r, size_t ul, size_t ur, T diff)
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
        if (l > r || l > ur || r < ul) return;

        // total overlap
        if (l >= ul && r <= ur) {

            tree[i] += diff;

            if (l != r) {
                lazy[LEFT(i)]  += diff;
                lazy[RIGHT(i)] += diff;
            }

            return;
        }

        // partial overlap
        const size_t m = l + (r - l) / 2;
        updateRangeUtil(LEFT(i),  l,       m, ul, ur, diff);
        updateRangeUtil(RIGHT(i), m + 1, r,   ul, ur, diff);
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
        if (l > r || l > qr || r < ql) return id;

        // total overlap
        if (l >= ql && r <= qr) return tree[i];

        // partial overlap
        const size_t m = l + (r - l) / 2;
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
    : op(binaryOperation),
      id(identityValue)
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
        updateRangeUtil(0, 0, n - 1, l, r, diff);
    }

    T query(size_t l, size_t r) 
    {
        return query(0, n - 1, l, r, 0);
    }

    void print()
    {
        for (const auto & x : tree) {
            cout << x << " ";
        }
        cout << endl;
    }
};

#endif

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

    auto minOp = [](const int64_t & lhs, const int64_t & rhs){ return (lhs < rhs) ? lhs : rhs; };
    SegmentTreeLazy<int64_t> st(minOp, numeric_limits<int64_t>::max());
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


        int64_t res;

        if (RMQ) {
            if (l <= r) {
                res = st.query(l, r);
            } else {
                res = minOp(st.query(0, r), st.query(l, N - 1));
            }
            cout << res;
            cout << endl;
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
