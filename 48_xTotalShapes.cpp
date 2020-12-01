/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/x-total-shapes/0

    Solution Description
    The provided matrix can be seen as a graph, in which each cell is a node
    with value 'O' or 'X', and it is connected with the upper, bottom, left and
    right node.
    For each node with value 'X', if it is not visited yet, compute BFS from it
    marking all connected node as visited.
    The number of computed BFS is the number of shapes in the provided matrix.

    Time  Complexity: O(N * M)
    Space Complexity: O(N * M)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

inline bool inside(const int x, const int y, const int n, const int m)
{
    return (0 <= x and x < n and 0 <= y and y < m);
}

int xTotalShapes(const vector< vector<char> > & v)
{
    const int n = v.size();
    const int m = v[0].size();
    const vector< pair<int, int> > dir = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    vector< vector<bool> > visited(n, vector<bool>(m, false));

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j] and v[i][j] == 'X') {
                ans++;
                // BFS
                queue< pair<int, int> > q;
                q.push({i, j});
                visited[i][j] = true;
                while (!q.empty()) {
                    const pair<int, int> p = q.front();
                    q.pop();
                    for (const auto & d : dir) {
                        const int x = p.first  + d.first;
                        const int y = p.second + d.second;
                        if (!inside(x, y, n, m)) continue;
                        if (!visited[x][y] and v[x][y] == 'X') {
                            q.push({x, y});
                            visited[x][y] = true;
                        }
                    }
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        int M;
        cin >> N;
        cin >> M;

        vector< vector<char> > v(N, vector<char>(M));
        for (int n = 0; n < N; ++n) {
            for (int m = 0; m < M; ++m) {
                cin >> v[n][m];
            }
        }

        cout << xTotalShapes(v) << '\n';
    }

    return 0;
}
