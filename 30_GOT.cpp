/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/GOT/

    Solution Description
    The problem can be restated as follows.
    Let A be the same tree of the problem with node values set to -1.
    We define two types of query:
    1) Change(x, c): assign the value c to the node x
    2) Query(a, b, c): check if the value c is present in the simple path (a, b)
    The problem is solved with offline queries.
    Consider the input tree nodes as queries of the first type, where x is the
    node itself and c is the node value. The queries provided by the problem are
    of the second type. Sort all queries in increasing order by value c, and in
    case of a tie, sort them by type (first type goes first). This way, when we
    answer queries of the second type, A will always have elements less than or
    equal to c, never greater. Let consider a query of second type
    Query(a, b, c), and let M be the maximum element of A in the simple path
    (a, b). If M < c, then we can be sure that there is not any c in this path.
    Otherwise there is a value c somewhere, and this is enough because we do not
    care about its position.
    The problem is solved with HLD and ST that solves Range Maximum Query for
    each heavy path.

    Time  Complexity: O((N + Q) log^2 N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr size_t MAX_N = 100000;
constexpr size_t MAX_M = 200000;

template<typename T, T (op)(const T &, const T &), T id>
struct SegmentTree
{
    int n;
    vector<T> tree;

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

    // Change the value of a single element
    void change(int p, const T v) {
        for (tree[p += n] = v; p > 1; p >>= 1) {
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

    // Using reserve() can prevent unnecessary reallocations
    void reserve(int n) {
        tree.reserve(2 * n);
    }

    // Remove all elements
    void clear() {
        n = 0;
        tree.clear();
    }
};

template <typename T, T (op)(const T &, const T &), T id, bool valuesOnNodes = false>
struct HLD
{
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

    void add_edge(int u, int v, const T cu = id, const T cv = id) {
        adj[u].push_back(v);
        cost[u].push_back((valuesOnNodes ? cv : cu));

        adj[v].push_back(u);
        cost[v].push_back(cu);
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

        int iMax = -1;  // index of the node with largest subtree
        int sMax = -1;  // subtree size
        for (int i = 0; i < n; ++i) {
            const int v = adj[u][i];
            if (v != p and sMax < subsize[v]) {
                iMax = i;
                sMax = subsize[v];
            }
        }

        // new node in the heavy path
        if (iMax != -1) {
            hld(adj[u][iMax], h, cost[u][iMax]);
        }

        // new heavy paths
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
    T path_query(int u, int v, const Func & fun) {
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

    void build(int u = 1, const T c = id) {
        super::build(u, c);
        st.build(super::vArray);
    }

    void change(int u, const T c) {
        st.change(super::vPos[u] + !valuesOnNodes, c);
    }

    T query(int u, int v) {
        return super::path_query(u, v, [this](const int u, const int v) {
                   return st.query(u, v + 1);
               });
    }

    void reserve(size_t n) {
        super::reserve(n);
        n++;
        st.reserve(n);
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

    inline bool operator<(const Query & rhs) const {
        return (c == rhs.c) ? type < rhs.type : c < rhs.c;
    }
};

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

        for (int i = 1; i <= N; ++i) {
            int c;
            cin >> c;
            Q.push_back({Query::Type::Change, i, -1, c, -1});
        }

        hld.resize(N);
        for (int i = 1; i < N; ++i) {
            int u;
            int v;
            cin >> u;
            cin >> v;
            hld.add_edge(u, v);
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

        result.resize(M);
        for (const auto & q : Q) {
            if (q.type == Query::Type::Change) {
                hld.change(q.u, q.c);
            } else {
                result[q.i] = (q.c <= hld.query(q.u, q.v));
            }
        }

        for (const auto & r : result) {
            cout << (r ? "Find" : "NotFind") << '\n';
        }

        result.clear();
        Q.clear();
        hld.clear();
    }

    return 0;
}
