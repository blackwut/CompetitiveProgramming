/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/424/B

    Solution Description
    For each entry calculate the distance from Tomsk location (0, 0).
    Sort them by distance in increasing order and select them greedily until the
    sum of population is at least one million.
    The solution is the distance of the last entry selected.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

struct Location
{
    int64_t d;
    int p;

    inline bool operator<(const Location & rhs) const { return d < rhs.d; };
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    int S;
    cin >> N;
    cin >> S;

    vector<Location> v(N);
    for (int n = 0; n < N; ++n) {
        int x;
        int y;
        int p;

        cin >> x;
        cin >> y;
        cin >> p;

        v[n].d = x * x + y * y;
        v[n].p = p;
    }

    sort(v.begin(), v.end());

    for (const auto & l : v) {
        S += l.p;
        if (S >= 1000000) {
            cout << setprecision(8) << sqrt(l.d) << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';

    return 0;
}
