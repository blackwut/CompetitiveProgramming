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
#include <cmath>

using namespace std;

#define ONE_MILLION     (1000000)


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    int S;
    cin >> N;
    cin >> S;

    vector< pair<int64_t, int> > v(N);

    for (int n = 0; n < N; ++n) {
        int x;
        int y;
        int p;

        cin >> x;
        cin >> y;
        cin >> p;

        v[n].first = x * x + y * y;
        v[n].second = p;
    }

    sort(v.begin(), v.end(),
        [](const pair<int64_t, int> & a, const pair<int64_t, int> & b) {
            return a.first < b.first;
        }
    );

    for (const auto & l : v) {
        S += l.second;
        if (S >= ONE_MILLION) {
            cout.precision(8);
            cout << sqrt(l.first);
            cout << endl;
            break;
        }
    }

    if (S < ONE_MILLION) {
        cout << -1;
        cout << endl;
    }

    v.clear();

    return 0;
}
