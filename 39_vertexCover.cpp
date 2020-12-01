/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/PT07X/

    Solution Description
    The problem can be restated as the number of nodes N of the tree minus the 
    LIST (Largest Independent Set on Trees) of the tree.

    The LIST problem is solved using dynamic programming.
    Consider a tree and perform a bottom up traversal. For each node u, we could
    add its children in the independent set but not its grandchildren and vice
    versa.
    The LIST of each node u can be calculated as:
    - 1                                                           if u is a leaf
    - max(sum_{v in C_u} LIST(v), 1 + sum_{v in G_v} LIST(v))     otherwise
    The first line is the base case in which the LIST of a single node is 1.
    In the second line we take the maximum between the sum of LIST of its
    children and the sum of LIST of its grandchildren + 1 (because skipping u's
    children means that we must add u in the LIST).

    At first, the time complexity seems O(N^2), but since each vertex u is
    processed only a constant number of times (i.e. at most three times: u
    itself, u's parent and u's grandparent), the time complexity is O(N).

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LIST(const vector< vector<int> > & adj,
         vector<int> & dp,
         int u, int p)
{
    if (dp[u] != -1) return dp[u];

    int maxChild = 0;
    int maxGrand = 0;

    for (const auto & v : adj[u]) {
        if (v != p) {
            maxChild += LIST(adj, dp, v, u);
            for (const auto & vv : adj[v]) {
                if (vv != u) {
                    maxGrand += LIST(adj, dp, vv, v);
                }
            }
        }
    }

    dp[u] = max(1 + maxGrand, maxChild);
    return dp[u];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector< vector<int> > adj(N + 1);
    for (int n = 1; n < N; ++n) {
        int u;
        int v;
        cin >> u;
        cin >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(N + 1, -1);
    cout << N - LIST(adj, dp, 1, 1) << '\n';

    return 0;
}
