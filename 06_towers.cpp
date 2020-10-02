/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/problemset/problem/37/A?locale=en

    Solution Description
    Sort the array.
    The largest tower is determined counting how many bars have the same length.
    The minimal number of towers is determined counting how many distinct bars
    there are.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n];
    }

    sort(v.begin(), v.end());

    int h = 0;
    int hMax = 0;
    int barMax = 0;
    int numBars = 0;

    for (int i = 0; i < N; ++i) {
        const int bar = v[i];

        if (bar > barMax) {
            barMax = bar;
            h = 0;
            ++numBars;
        }
        ++h;

        if (h > hMax) {
            hMax = h;
        }
    }

    cout << hMax << ' ' << numBars << '\n';

    v.clear();

    return 0;
}
