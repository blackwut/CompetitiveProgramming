/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/160/C

    Solution Description
    TODO

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define uint uint64_t

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint N;
    uint K;
    cin >> N;
    cin >> K;

    vector<int> v(N);

    for (uint n = 0; n < N; ++n) {
        cin >> v[n];
    }

    sort(v.begin(), v.end());

    const uint i = (K - 1) / N;
    const int first = v[i];

    uint l = 0;
    for(l = 0; l < N; ++l){
        if(v[l] == first) break;
    }

    uint r = 0;
    for (uint n = l; n < N; ++n, ++r) {
        if (v[n] != first) break;
    }

    const uint j = (K - 1 - l * N) / r;
    const int second = v[j];
    cout << first << " " << second << endl;

    v.clear();

    return 0;
}
