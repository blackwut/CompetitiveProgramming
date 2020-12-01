/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/contest/86/problem/D

    Solution Description
    Let be K_s the number of occurrences of a value s and P the power of the
    sub-array calculated as sum over s of (K_s)^2 * s.
    This solution is based on Mo's Algorithm. The add() and del() functions for
    a value s are defined as follows:
    - add(): extend the range by 1 means that the power of a sub-array goes from
             (K_s)^2 * s to (K_s + 1)^2 * s, hence the difference between these
             two terms is (2 * K_s + s)
    - del(): reduce the range by 1 means that the power of a sub-array goes from
             (K_s)^2 * s to (K_s - 1)^2 * s, hence the difference between these
             two terms is -(2 * K_s + s)

    Time  Complexity: O((N + Q) * SQRT(N))
    Space Complexity: O(MAX_V)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr size_t MAX_V = 1000004;

struct Query
{
    int l;
    int r;
    int i;

    inline bool operator<(const Query & rhs) const {
        constexpr int SQRT_N = 1000;
        if (l / SQRT_N != rhs.l / SQRT_N){
            return l < rhs.l;
        }
        return (r < rhs.r) ^ (l / SQRT_N & 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    int Q;
    cin >> N;
    cin >> Q;

    vector<int> v(N + 1);
    for (int n = 1; n <= N; ++n) {
        cin >> v[n];
    }

    vector<Query> q(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> q[i].l;
        cin >> q[i].r;
        q[i].i = i;
    }

    // Mo's Algorithm
    sort(q.begin(), q.end());

    int l = 0;
    int r = 0;
    int64_t ret = 0;
    vector<int> c(MAX_V);
    vector<int64_t> result(Q);

    const auto add = [&](int p){ return (int64_t)2 * c[v[p]]++ * v[p] + v[p]; };
    const auto del = [&](int p){ return (int64_t)2 * --c[v[p]] * v[p] + v[p]; };

    for (const auto & x : q) {
        while (l < x.l) ret -= del(l++);
        while (l > x.l) ret += add(--l);
        while (r < x.r) ret += add(++r);
        while (r > x.r) ret -= del(r--);

        result[x.i] = ret;
    }

    for (const auto & r : result) {
        cout << r << '\n';
    }

    return 0;
}
