/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/problemset/problem/277/A?locale=en

    Solution Description
    Build an undirected graph with N + M nodes, where N are the employees and M
    are the languages. For each language spoken by an employee, add an edge
    between the employee and that language.
    For each employee node, if not visited yet, compute a DFS to find a
    connected component. The number of computed DFS are the number of connected
    components of the graph.
    The solution is the number of connected component minus 1. Actually, if all
    the employees speak no language, the result is N.

    Time  Complexity: O(N * M)
    Space Complexity: O(N * M)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Graph
{
    vector< vector<int> > adj;
    vector<bool> visited;

    Graph(size_t n)
    : adj(n)
    , visited(n, false)
    {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u) {
        visited[u] = true;
        for (const auto & v : adj[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    }

    int number_of_components(int N) {
        int ans = 0;
        for (int u = 0; u < N; ++u) {
            if (!visited[u]) {
                dfs(u);
                ans++;
            }
        }
        return ans;
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

    bool noLanguage = true;
    Graph g(N + M);

    for (int n = 0; n < N; ++n) {
        int K;
        cin >> K;

        if (K != 0) noLanguage = false;

        for (int k = 0; k < K; ++k) {
            int l;
            cin >> l;
            g.add_edge(n, N + l - 1);
        }
    }

    if (noLanguage) {
        cout << N << '\n';
        return 0;
    }

    cout << max(0, g.number_of_components(N) - 1) << '\n';

    return 0;
}