/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/UPDATEIT

    C++ (clang 8.0)

    Solution Description
    TODO

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
using namespace std;

#if 1

#include "Structures/BIT.cpp"

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        int U;
        cin >> N;
        cin >> U;

        BIT<int> v(N);

        for (int u = 0; u < U; ++u) {
            int l;
            int r;
            int val;
            cin >> l;
            cin >> r;
            cin >> val;

            v.add(l, val);
            v.add(r + 1, -val);
        }

        int Q;
        cin >> Q;

        for (int q = 0; q < Q; ++q) {
            int k;
            cin >> k;
            cout << v.sum(k);
            cout << endl;
        }

        v.clear();
    }

    return 0;
}

#else

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        int U;
        cin >> N;
        cin >> U;

        vector<int> v(N);

        for (int u = 0; u < U; ++u) {
            int l;
            int r;
            int val;
            cin >> l;
            cin >> r;
            cin >> val;

            v[l] += val;
            v[r + 1] -= val;
        }

        for (int n = 1; n < N; ++n) {
            v[n] += v[n - 1];
        }

        int Q;
        cin >> Q;

        for (int q = 0; q < Q; ++q) {
            int k;
            cin >> k;
            cout << v[k];
            cout << endl;
        }

        v.clear();
    }

    return 0;
}

#endif
