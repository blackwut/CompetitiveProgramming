#pragma once
#include <vector>

/*
    Inspired by https://sites.google.com/site/indy256/algo/heavy_light

    // Create an operator, a subclass of the HLD and instantiate the subclass
    template <typename T>
    struct Operator
    {
        static T op(const T & a, const T & b) { return a < b ? a : b; };
        static const T id = numeric_limits<T>::max();
    };
    ...
    template <typename T, T (op)(const T &, const T &), T id, bool valuesOnNodes = false>
    struct HLD_ext : HLD<T, op, id, valuesOnNodes> {

        using super = HLD<T, op, id, valuesOnNodes>;
        SegmentTree<T, op, id> st;

        T query(int u, int v) {
            T ans = 0;
            super::path_query(u, v, [&](const int u, const int v) {
                ans += st.query(u, v);
                return id;
            });
            return ans;
        }
        ...
    }
    ...
    HLD_ext<int, Operator<int>::op, Operator<int>::id, true> hld;
*/

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
