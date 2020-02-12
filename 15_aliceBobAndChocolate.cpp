/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/6/C?locale=en

    Solution Description
    TODO: complete
    TODO: doesnt work

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int eat_chocolate(const vector<int> & v)
{
    const int n = v.size();
    const int total = accumulate(v.begin(), v.end(), 0);
    int sum = 0;
    int i = 0;
    while (i < n && sum < (total - sum)) {
        sum += v[i++];
    }

    if (i != 0 && sum < (total - sum)) {
        --i;
    }
    return i;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> v;
    v.reserve(N);
    for (int n = 0; n < N; ++n) {
        int x;
        cin >> x;
        v.push_back(x);
    }

    int result = eat_chocolate(v);
    cout << result << " " << (N - result);
    cout << endl;

    v.clear();

    return 0;
}
