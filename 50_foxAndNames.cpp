/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/510/C?locale=en

    Solution Description
    Create a graph in which nodes are lowercase Latin letters and  edges are
    formed by considering the leftmost mismatch characters of two consecutive
    strings.
    This graph represent the the order of letters followed to sort authors.
    If this graph is cyclic, such order is impossible. Otherwise the order of
    letters can be computed traversing the graph with DFS starting from the last
    mismatch character of the last string.

    Time  Complexity: O(L) where L is the sum of all string's lengths
    Space Complexity: O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DirectGraph
{
    enum Color : char {White, Grey, Black};

    vector< vector<int> > adj;
    vector<char> color;
    vector<char> path;
    bool acyclic;

    DirectGraph(size_t n)
    : adj(n)
    , color(n, Color::White)
    , acyclic(true)
    {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        color[u] = Color::Grey;
        for (const auto & v : adj[u]) {
            if (color[v] == Color::Grey) {
                acyclic = false;
                return;
            }
            if (color[v] == Color::White) {
                dfs(v);
            }
        }
        color[u] = Color::Black;
        path.push_back(char('a' + u));
    }

    vector<char> compute_path() {
        for (int i = adj.size() - 1; i >= 0; --i) {
            if (color[i] == Color::White) {
                dfs(i);
            }
            if (!acyclic) {
                return {};
            }
        }
        return path;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    DirectGraph dg('z' - 'a' + 1);

    string A;
    string B;
    cin >> A;
    for (int n = 1; n < N; ++n) {
        cin >> B;
        // find the leftmost mismatch characters
        int i = 0;
        while (A[i] == B[i]) i++;

        if (A[i]) {
            dg.add_edge(A[i] - 'a', (B[i] ? B[i] : A[i]) - 'a');
        }
        swap(A, B);
    }

    const auto result = dg.compute_path();
    if (result.empty()) {
        cout << "Impossible\n";
        return 0;
    }

    for (int i = result.size() - 1; i >= 0; --i) {
        cout << (char)result[i];
    }
    cout << '\n';

    return 0;
}
