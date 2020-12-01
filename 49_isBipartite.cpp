/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/bipartite-graph/1

    Solution Description
    Color each node as the opposite color of its parent in breadth-first order.
    If a node discovers a neighbor with its own color, the graph is not a
    bipartite graph.

    Time  Complexity: O(V^2)
    Space Complexity: O(V^2)
*/

bool isBipartite(int G[][MAX], int V)
{
    // never visited: -1; red: 0; blue: 1
    vector<char> color(V, -1);

    for (int i = 0; i < V; ++i) {
        if (color[i] == -1) {
            color[i] = 0;
        }

        for (int j = 0; j < V; ++j) {
            if (G[i][j]) {
                if (color[j] == color[i]) {
                    return false;
                }
                if (color[j] == -1) {
                    color[j] = color[i] ^ 1;
                }
            }
        }
    }

    return true;
}
