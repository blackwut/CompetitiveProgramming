/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/652/D

    Solution Description
    TODO

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include "Structures/BIT.cpp"
using namespace std;

#define RANGE tuple<int, int, int>

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> v;
    vector< tuple<int, int, int> > ranges(N);
    BIT<int> b(2 * N);

    for (int n = 0; n < N; ++n) {
        int l;
        int r;
        cin >> l;
        cin >> r;

        v.push_back(l);
        v.push_back(r);
        ranges[n] = RANGE(l, r, n);
    }

    sort(v.begin(), v.end());

    // rescaling ranges
    for (int n = 0; n < N; ++n) {
        get<0>(ranges[n]) = (int) (std::lower_bound(v.begin(), v.end(), get<0>(ranges[n])) - v.begin());
        get<1>(ranges[n]) = (int) (std::lower_bound(v.begin(), v.end(), get<1>(ranges[n])) - v.begin());
    }

    // sorting ranges (by left ends) in increasing order
    sort(ranges.begin(), ranges.end(),
        [](const RANGE & a, const RANGE & b) {
            return get<0>(a) < get<0>(b);
        }
    );

    // construct the BIT
    for (int n = 0; n < N; ++n) {
        const int r = get<1>(ranges[n]);
        b.add(r, 1);
    }

    // construct results and update BIT accordingly
    vector<int> results(N);
    for (int n = 0; n < N; ++n) {
        const int index = get<2>(ranges[n]);
        const int r = get<1>(ranges[n]);
        results[index] = b.sum(r - 1);
        b.add(r, -1);
    }

    for (int n = 0; n < N; ++n) {
        cout << results[n];
        cout << endl;
    }

    results.clear();
    b.clear();
    ranges.clear();
    v.clear();

    return 0;
}
