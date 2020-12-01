/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/353/B?locale=en

    Solution Description
    Sort the values and divide equally the values that appear once in the two
    heaps. Then divide equally the remaining numbers in the two heaps.
    The maximum possible number of distinct four-digit numbers is the product
    between the number of distinct cubes in the two heaps.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Cube {
    int v;  // value
    int i;  // index

    inline bool operator<(const Cube & rhs) const { return v < rhs.v; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    N *= 2;

    vector<Cube> cubes(N);
    vector<int> freq(100);
    for (int n = 0; n < N; ++n) {
        int v;
        cin >> v;
        freq[v]++;
        cubes[n].v = v;
        cubes[n].i = n;
    }

    sort(cubes.begin(), cubes.end());

    vector<int> result(N);
    int heap[] = {0, 0};
    int i = 1;
    for (int n = 0; n < N; ++n) {
        const auto & c = cubes[n];
        const int f = freq[c.v];
        if (f == 1) {
            ++heap[i & 1];
            result[c.i] = 2 - (i & 1);
            ++i;
        }
    }

    for (int n = 0; n < N;) {
        const int fr = freq[cubes[n].v];
        if (fr > 1) {
            for (int f = 1; f <= fr; ++f, ++n) {
                const auto & c = cubes[n];
                if (f < 3) {
                    ++heap[i & 1];
                }
                result[c.i] = 2 - (i & 1);
                ++i;
            }
        } else {
            ++n;
        }
    }

    cout << heap[0] * heap[1] << '\n';
    for (const auto & i : result) {
        cout << i << " ";
    }
    cout << '\n';

    return 0;
}
