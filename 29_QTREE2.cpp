/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/QTREE2/

    Solution Description
    Decompose the tree with HLD and construct a ST that solves Range Sum Query
    (RSQ) for each heavy path.
    The DIST operation is solved by the `path query` in which `fun` is the RSQ
    and `op` is the sum function.
    The KTH operation is solved by finding the LCA node, let say l. If the LCA
    is the k-th node on the path (a, b), return it. Otherwise locate the k-th
    node either on the path (a, l) or (b, l) depending on the number of the
    nodes in the two paths toward the LCA.

    Time  Complexity: O(N + Q log^2 N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

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
    using super::head;
    using super::depth;
    using super::parent;

    SegmentTree<T, op, id> st;

    void build(int u = 1, const T c = id) {
        super::build(u, c);
        st.build(super::vArray);
    }

    T query(int u, int v) {
        return super::path_query(u, v, [this](const int u, const int v) {
                   return st.query(u, v + 1);
               });
    }

    int lca(int u, int v) {
        for (; head[u] != head[v]; u = parent[head[u]]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
        }
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        return u;
    }

    int parent_up(int u, int v, int k) {
        while (k) {
            if (head[u] == head[v]) {
                for (int i = 0; i < k - 1; ++i) {
                    u = parent[u];
                }
                return u;
            }

            const int diff = depth[u] - depth[head[u]] + 1;
            if (k <= diff) {
                for (int i = 0; i < k - 1; ++i) {
                    u = parent[u];
                }
                return u;
            }

            k -= diff;
            u = parent[head[u]];
        }

        return -1;
    }

    int find_node(int u, int v, int k) {
        if (u == v) return u;

        const int l = lca(u, v);
        const int diff = depth[u] - depth[l] + 1;

        // find LCA
        if (k == diff) return l;

        // find k-th on path u -> LCA
        if (k < diff)  return parent_up(u, l, k);

        // find k-th on path v -> LCA
        k = depth[u] + depth[v] - 2 * (depth[l] - 1) - k;
        return parent_up(v, l, k);
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
    static T op(const T & a, const T & b) { return a + b; };
    static const T id = 0;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    HLD_ext<int, Operator<int>::op, Operator<int>::id> hld;
    hld.reserve(10000);

    while (T--) {
        int N;
        cin >> N;

        hld.resize(N);
        for (int i = 1; i < N; ++i) {
            int u;
            int v;
            int c;
            cin >> u;
            cin >> v;
            cin >> c;
            hld.add_edge(u, v, c);
        }
        hld.build();

        while (1) {
            char s[24];
            cin >> s;

            // DONE
            if (s[1] == 'O') break;

            // DIST a b
            if (s[1] == 'I') {
                int a;
                int b;
                cin >> a;
                cin >> b;
                cout << hld.query(a, b) << '\n';
            }

            // KTH  a b k
            if (s[1] == 'T') {
                int a;
                int b;
                int c;
                cin >> a;
                cin >> b;
                cin >> c;
                cout << hld.find_node(a, b, c) << '\n';
            }
        }

        hld.clear();
    }

    return 0;
}
