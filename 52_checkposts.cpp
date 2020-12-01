/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/427/C?locale=en

    Solution Description
    Compute the Strongly Connected Components (SCCs) of the graph representing
    the city (junctions are nodes, roads are edges).
    Let be m_i and c_i, respectively, the minimum cost and the number of nodes
    with cost equal to m_i in each Strongly Connected Component (SCC) i.
    The minimum possible money needed is the sum of m_i.
    The number of ways to ensure security is the product c_i.

    Time  Complexity: O(N + M)
    Space Complexity: O(N + M)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits>
using namespace std;

struct DirectGraph
{
    vector< vector<int> > g;
    vector< vector<int> > gt;
    vector<bool> visited;

    DirectGraph(size_t n)
    : g(n)
    , gt(n)
    , visited(n)
    {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gt[v].push_back(u);
    }

    void dfs_g(int u, stack<int> & s) {
        visited[u] = true;
        for (const auto & v : g[u]) {
            if (!visited[v]) {
                dfs_g(v, s);
            }
        }
        s.push(u);
    }

    void dfs_gt(int u, vector<int> & c) {
        visited[u] = true;
        c.push_back(u);

        for (const auto & v : gt[u]) {
            if (!visited[v]) {
                dfs_gt(v, c);
            }
        }
    }

    vector< vector<int> > get_components()
    {
        vector< vector<int> > components;
        stack<int> s;

        // DFS on G
        fill(visited.begin(), visited.end(), false);
        const int n = g.size();
        for (int u = 0; u < n; ++u) {
            if (!visited[u]) {
                dfs_g(u, s);
            }
        }

        // DFS on G^T considering nodes in decreasing order
        fill(visited.begin(), visited.end(), false);
        while (!s.empty()) {
            const int u = s.top();
            s.pop();

            if (!visited[u]) {
                vector<int> c;
                dfs_gt(u, c);
                components.push_back(c);
            }
        }
        return components;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> cost(N);
    for (int n = 0; n < N; ++n) {
        cin >> cost[n];
    }

    int M;
    cin >> M;

    DirectGraph dg(N);
    for (int m = 0; m < M; ++m) {
        int u;
        int v;
        cin >> u;
        cin >> v;

        dg.add_edge(u - 1, v - 1);
    }

    int64_t total = 0;
    int64_t ways = 1;
    const auto components = dg.get_components();
    for (const auto & c : components) {
        int m = numeric_limits<int>::max();
        int n = 0;
        for (const auto & u : c) {
            const int val = cost[u];
            if (val < m) {
                m = val;
                n = 0;
            }
            n += (val == m);
        }
        total += m;
        ways = (ways * n) % 1000000007;
    }

    cout << total << ' ' << ways << '\n';

    return 0;
}
