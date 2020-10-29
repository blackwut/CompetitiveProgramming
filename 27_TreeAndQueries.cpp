/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/contest/375/problem/D

    Solution Description
    For each node v_i, define L_i and R_i as the left and the right index of its
    subtree (i.e. L_i is the index of v_i itself, R_i is the index of the
    right-most node in v_i's subtree).
    Convert all queries from (v_i, k_i) to (L_i, R_i, k_i).
    Let be F_c the number of nodes of color c and F_j the number of F_c that has
    value j.
    Using the Mo's Algorithm, offline queries are satisfied providing the add()
    and del() functions:
    - add(): extending the range by one means that a new node is considered,
             hence F_c has to be increased, where c is the color of the new
             node, and also F_j has to be increased by one, where j is exactly
             the value of F_c
    - del(): reducing the range by one means that F_j has to be decreased, where
             j is the value of F_c and then also F_c has to be decreased by one,
             where c is the color of the removed node

    Time  Complexity: O((N + Q) * SQRT(N))
    Space Complexity: O(MAX_C)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
struct SubtreeRanges
{
    vector< vector<T> > adj;
    vector<int> node;
    vector<int> L;
    vector<int> R;
    int pos;

    SubtreeRanges(size_t n)
    : adj(n)
    , node(n)
    , L(n)
    , R(n)
    , pos(0)
    {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void make(int u = 1, int p = -1) {
        node[pos] = u;
        L[u] = pos++;
        for (const auto & v : adj[u]) {
            if (v != p) {
                make(v, u);
            }
        }
        R[u] = pos;
    }
};

struct Query {
    int l;
    int r;
    int k;
    int i;

    inline bool operator<(const Query & rhs) const {
        constexpr int SQRT_N = 320;
        if (l / SQRT_N != rhs.l / SQRT_N) {
            return l < rhs.l;
        }
        return (r < rhs.r);
    }
};

inline void add(vector<int> & freq, vector<int> & color, const int & c)
{
    ++freq[++color[c]];
}

inline void del(vector<int> & freq, vector<int> & color, const int & c)
{
    --freq[color[c]--];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    int Q;
    cin >> N;
    cin >> Q;

    vector<int> c(N + 1);
    for (int n = 1; n <= N; ++n) {
        cin >> c[n];
    }

    SubtreeRanges<int> sr(N + 1);
    for (int n = 1; n < N; ++n) {
        int u;
        int v;
        cin >> u;
        cin >> v;
        sr.add_edge(u, v);
    }
    sr.make();

    vector<Query> q(Q);
    for (int i = 0; i < Q; ++i) {
        int v;
        int k;
        cin >> v;
        cin >> k;

        q[i].l = sr.L[v];
        q[i].r = sr.R[v];
        q[i].k = k;
        q[i].i = i;
    }

    // Mo's Algorithm
    sort(q.begin(), q.end());

    constexpr int MAX_C = 100004;
    vector<int> freq(MAX_C);
    vector<int> color(MAX_C);

    int l = 0;
    int r = 0;
    vector<int64_t> result(Q);
    for (const auto & x : q) {
        while (l < x.l) del(freq, color, c[sr.node[l++]]);
        while (l > x.l) add(freq, color, c[sr.node[--l]]);
        while (r < x.r) add(freq, color, c[sr.node[r++]]);
        while (r > x.r) del(freq, color, c[sr.node[--r]]);

        result[x.i] = freq[x.k];
    }

    for (const auto r : result) {
        cout << r << "\n";
    }

    return 0;
}
