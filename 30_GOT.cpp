/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/GOT/

    Solution Description
    https://codeforces.com/blog/entry/22967?#comment-274508

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T, T (op)(const T &, const T &), T id>
struct SegmentTree {
/* Inspired by https://codeforces.com/blog/entry/18051 */
    int n;
    int h;
    vector<T> tree;
    vector<int> lazy;

    // Build from a given vector
    void build(const vector<T> & v) {
        n = static_cast<int>(v.size());
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

    // Using reserve() can prevent unnecessary reallocations
    void reserve(size_t n) {
        n++;
        tree.reserve(n);
        lazy.reserve(n);
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

    void clear() {
        n = 0;
        h = 0;
        tree.clear();
        lazy.clear();
    }
};

template <typename T, T (op)(const T &, const T &), T id, bool valuesOnNodes = false>
struct HLD {

    // Graph
    vector< vector<int> > adj;
    vector< vector<T> > cost;

    // HLD
    vector<int> head;
    vector<int> depth;
    vector<int> parent;
    vector<int> subsize;

    // Values
    int vSize;
    vector<int> vPos;
    vector<T> vArray;

    HLD() = default;
    ~HLD() = default;

    void reserve(size_t n) {
        n++;

        adj.reserve(n);
        cost.reserve(n);

        head.reserve(n);
        depth.reserve(n);
        parent.reserve(n);
        subsize.reserve(n);

        vPos.reserve(n);
        vArray.reserve(n);
    }

    void resize(size_t n) {
        n++;

        adj.resize(n);
        cost.resize(n);

        head.resize(n, -1);
        depth.resize(n, 0);
        parent.resize(n, -1);
        subsize.resize(n, 0);

        vSize = 0;
        vPos.resize(n, -1);
        vArray.resize(n, id);
    }

    void add_edge(int u, int v, const T c = id) {
        adj[u].push_back(v);
        cost[u].push_back(c);

        adj[v].push_back(u);
        cost[v].push_back(c);
    }

        // node u, parent p, depth d
    void dfs(int u, int p, int d = 0) {
        depth[u] = d;
        parent[u] = p;
        subsize[u] = 1;

        for (const auto & v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1);
                subsize[u] += subsize[v];
            }
        }
    }

    // node u, head h , cost c
    void hld(int u, int h, const T c = id) {
        head[u] = h;
        vPos[u] = vSize;
        vArray[vSize] = c;
        vSize++;

        const int n = adj[u].size();
        const int p = parent[u];

        int iMax = -1;  // index of node with maximum subtree
        int sMax = -1;  // subtree size
        for (int i = 0; i < n; ++i) {
            const int v = adj[u][i];
            if (v != p and sMax < subsize[v]) {
                iMax = i;
                sMax = subsize[v];
            }
        }

        // new node in the heavy chain
        if (iMax != -1) {
            hld(adj[u][iMax], h, cost[u][iMax]);
        }

        // new chains
        for (int i = 0; i < n; ++i) {
            const int v = adj[u][i];
            if (v != p and i != iMax) {
                hld(v, v, cost[u][i]);
            }
        }
    }

    void build(int u = 1, const T c = id) {
        dfs(u, -1);
        hld(u, u, c);
    }

    template <typename Func>
    T processPath(int u, int v, const Func & fun) {
        T ans = id;
        for (; head[u] != head[v]; u = parent[head[u]]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
            ans = op(ans, fun(vPos[head[u]], vPos[u]));
        }
        if (!valuesOnNodes and u == v) return ans;
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        ans = op(ans, fun(vPos[v] + !valuesOnNodes, vPos[u]));
        return ans;
    }

    void clear() {
        for (int i = 0; i <= vSize; ++i) {
            adj[i].clear();
            cost[i].clear();
        }

        head.clear();
        depth.clear();
        parent.clear();
        subsize.clear();

        vSize = 0;
        vPos.clear();
        vArray.clear();
    }
};


template <typename T, T (op)(const T &, const T &), T id, bool valuesOnNodes = false>
struct HLD_ext : HLD<T, op, id, valuesOnNodes> {

    using super = HLD<T, op, id, valuesOnNodes>;

    SegmentTree<T, op, id> st;

    void reserve(size_t n) {
        super::reserve(n);
        n++;
        st.reserve(n);
    }

    void build(int u = 1, const T c = id) {
        super::build(u, c);
        st.build(super::vArray);
    }

    void change(int u, const T v) {
        st.change(super::vPos[u], v);
    }

    T query(int u, int v) {
        return super::processPath(u, v, [this](const int u, const int v) {
                   return st.query(u, v + 1);
               });
    }

    void clear() {
        super::clear();
        st.clear();
    }
};

template <typename T>
struct Operator
{
    static T op(const T & a, const T & b) { return a > b ? a : b; };
    static const T id = -1;
};

struct Query {
    enum Type {
        Change = 0,
        Search = 1
    };
    Type type;
    int u;
    int v;
    int c;
    int i;

    inline bool operator<(const Query & rhs) const
    {
        return (c == rhs.c) ? type < rhs.type : c < rhs.c;
    }
};

#define MAX_N 100000
#define MAX_M 200000

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    HLD_ext<int, Operator<int>::op, Operator<int>::id, true> hld;
    hld.reserve(MAX_N);

    vector<Query> Q;
    Q.reserve(MAX_N + MAX_M);

    vector<bool> result;
    result.reserve(MAX_M);

    int N;
    int M;
    while (cin >> N >> M) {

        hld.resize(N);
        result.resize(M);

        for (int i = 1; i <= N; ++i) {
            int c;
            cin >> c;
            Q.push_back({Query::Type::Change, i, -1, c, -1});
        }

        for (int i = 1; i < N; ++i) {
            int u;
            int v;
            cin >> u;
            cin >> v;
            hld.add_edge(u, v, Operator<int>::id);
        }

        hld.build();

        for (int i = 0; i < M; ++i) {
            int u;
            int v;
            int c;
            cin >> u;
            cin >> v;
            cin >> c;
            Q.push_back({Query::Type::Search, u, v, c, i});
        }
        sort(Q.begin(), Q.end());

        for (const auto & q : Q) {
            if (q.type == Query::Type::Change) {
                hld.change(q.u, q.c);
            } else {
                result[q.i] = (q.c <= hld.query(q.u, q.v));
            }
        }

        for (int i = 0; i < M; ++i) {
            cout << (result[i] ? "Find" : "NotFind") << '\n';
        }

        result.clear();
        Q.clear();
        hld.clear();
    }

    return 0;
}
