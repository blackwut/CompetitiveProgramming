/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/MST/

    Solution Description
    Solved with Kruskal's algorithm.

    Time  Complexity: O(M Log M)
    Space Complexity: O(M)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int i;
    int j;
    int w;

    inline bool operator<(const Edge & rhs) const { return w < rhs.w; }
};

struct UnionFind
{
    vector<int> parent;

    UnionFind(size_t n)
    : parent(n, -1)
    {}

    int root(int u) {
        if (parent[u] < 0) return u;
        return parent[u] = root(parent[u]);
    }

    bool unite(int u, int v) {
        u = root(u);
        v = root(v);

        if (u == v) return false;

        if (parent[u] > parent[v]) {
            swap(u, v);
        }
        parent[u] += parent[v];
        parent[v] = u;
        return true;
    }

    bool find(int u, int v) {
        return root(u) == root(v);
    }

    int size(int u) {
        return -parent[root(u)];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    int M;
    cin >> N;
    cin >> M;

    vector<Edge> edges(M);
    for (int m = 0; m < M; ++m) {
        cin >> edges[m].i;
        cin >> edges[m].j;
        cin >> edges[m].w;
    }
    sort(edges.begin(), edges.end());

    UnionFind set(N);
    int64_t result = 0;
    for (const auto & e : edges) {
        if (set.unite(e.i, e.j)) {
            result += e.w;
        }
    }

    cout << result << '\n';

    return 0;
}
