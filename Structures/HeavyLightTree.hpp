#pragma once

#include <vector>
#include "SegmentTree.hpp"

using namespace std;

#include <iostream>
#include <iomanip>
#define DEBUGV(v) do {for(const auto & val : v) cout << setw(2) << val << " "; cout << endl;} while(0);

template<typename T>
struct HeavyLightTree
{
private:

    vector<vector<int>> adj;
    vector<vector<T>> edge;         // edges value

    int chainNumber;                // current chain number (see decompose() function)
    vector<int> chainHead;          // head of the chain of the node u
    vector<int> chainId;            // index of the chain of the node u TODO: check if needed or substitute with head (head of the chain)
    vector<int> chainSize;          // size of the chain of the node u

    vector<int> parent;             // parent of node u
    vector<int> depth;              // depth of node u
    vector<int> subtreeSize;        // size of the subtree of node u

    vector<int> pos;                // position of the node in the segment tree
    vector<T> value;              // values of the segment tree
    int size;                       // size of the segment tree

    SegmentTree<T> st;

    void dfs(int u, int p, int d)   // u = current node; p = parent; d = depth
    {
        parent[u] = p;
        depth[u] = d;
        subtreeSize[u] = 1;

        const int s = adj[u].size();
        for (int i = 0; i < s; ++i) {
            const int v = adj[u][i];
            if (v != p) {
                dfs(v, u, d + 1);
                subtreeSize[u] += subtreeSize[v];
            }
        }
    }

    void decompose(int u, int p, const T val) // u = current node; p = parent
    {
        if (chainHead[chainNumber] == -1) { // new chain
            chainHead[chainNumber] = u;
        }
        chainId[u] = chainNumber;   // update chain number of u
        chainSize[chainNumber]++;   // increment chain size
        pos[u] = size;              // update position in segment tree
        value[size] = val;          // add value to segment tree
        size++;                     // increase segment tree size

        const int s = adj[u].size();
        // find node with maximum subtree size
        int iMax = -1; // index in the adjacency list of node u
        int vMax = -1; // node value at iMax index
        for (int i = 0; i < s; ++i) {
            const int v = adj[u][i];
            if (v != p) {
                if (vMax == -1 || subtreeSize[v] > subtreeSize[vMax]) {
                    iMax = i;
                    vMax = v;
                }
            }
        }

        // new node in the heavy chain
        if (iMax != -1) {
            decompose(adj[u][iMax], u, edge[u][iMax]);
        }

        // new chains
        for (int i = 0; i < s; ++i) {
            if (adj[u][i] != p && i != iMax) {
                chainNumber++;
                decompose(adj[u][i], u, edge[u][i]);
            }
        }
    }

    T queryUp(int u, int v)
    {
#if 1
        int uChain;
        int vChain = chainId[v];
        T result = st.id;

        while (1) {
            uChain = chainId[u];

            if (uChain == vChain) {
                // if (u == v) break;

                // result = st.op(result, st.query(pos[chainHead]))
                if (u != v) {
                    result = st.op(result, st.query(pos[chainHead[vChain]], pos[u]));
                }
                break;
            }

            result = st.op(result, st.query(pos[chainHead[uChain]], pos[u] + 1));
            u = chainHead[uChain];
            u = parent[u];
        }
        return result;
#else
        int result = st.id;
        for (; chainHead[chainId[u]] != chainHead[chainId[v]]; v = parent[chainHead[chainId[v]]]) {
            if (depth[chainHead[chainHead[u]]] > depth[chainHead[v]]) {
                swap(u, v);
            }
            int val = st.query(pos[chainHead[chainId[u]]], pos[chainHead[chainId[v]]]);
            cout << "VAL: " << val << endl;
            result = st.op(result, val);
        }

        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        int val = st.query(pos[chainHead[chainId[u]]], pos[chainHead[chainId[v]]]);
        return st.op(result, val);
#endif
    }

public:

    HeavyLightTree(int n, function<T(const T &, const T &)> op, T id)
    : adj(n, vector<int>())
    , edge(n, vector<T>())
    , chainNumber(0)
    , chainHead(n, -1)
    , chainId(n, -1)
    , chainSize(n, -1)
    , parent(n, -1)
    , depth(n, -1)
    , subtreeSize(n, -1)
    , pos(n, -1)
    , value(n, 0)
    , size(0)
    , st(op, id)
    {}

    void addEdge(const int u, const int v, const T value)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge[u].push_back(value);
        edge[v].push_back(value);
    }

    int LCA(int u, int v)
    {
        while (chainHead[chainId[u]] != chainHead[chainId[v]]) {
            if (depth[chainHead[chainId[u]]] < depth[chainHead[chainId[v]]]) {
                v = parent[chainHead[chainId[v]]];
            } else {
                u = parent[chainHead[chainId[u]]];
            }
        }
        return depth[u] < depth[v] ? u : v;
    }

    void build()
    {
        dfs(0, -1, 0);
        decompose(0, -1, st.id);

        value.resize(size);
        st.build(value);
        // for (int i = 0; i < 20; ++i) {
        //     cout << setw(2) << i << " ";
        // }
        // cout << endl;
        // DEBUGV(chainHead);
        // DEBUGV(parent);
        // DEBUGV(depth);
        // DEBUGV(subtreeSize);
        // DEBUGV(value);
        // st.print();
    }

    T query(int u, int v)
    {
        int lca = LCA(u, v);
        int uResult = queryUp(u, lca);
        int vResult = queryUp(v, lca);

        return st.op(uResult, vResult);
    }

    void update(int u, T val)
    {
        st.update(pos[u], val);
    }
};