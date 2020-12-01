/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/652/D

    Solution Description
    The i-th segment is stored as a tuple <l_i, r_i, i>.
    Sort the segments by r_i and replace r_i with its rank.
    Sort again the segments in decreasing order by l_i.
    Make use of a BIT (Binary Index Tree) to keep track of the already visited
    segments. For each segment do the following:
    - add 1 at position r_i to the BIT
    - then get the sum in the range [0, r_i), that represents the number of
      nested segments

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
struct BIT
{
    vector<T> b;

    BIT(int n)
    : b(n + 1)
    {}

    void increment(int k, T a) { // b[k] += a
        const int n = b.size();
        for (++k; k < n; k += k & -k) {
            b[k] += a;
        }
    }

    T query(int k) { // sum in the range [0, k)
        T s = 0;
        for (++k; k > 0; k &= k - 1) {
            s += b[k];
        }
        return s;
    }
};

struct Seg
{
    int l;
    int r;
    int i;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Seg> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n].l;
        cin >> v[n].r;
        v[n].i = n;
    }

    // sort by right in increasing order and replace r_i with its rank
    auto compR = [](const Seg & lhs, const Seg & rhs) { return lhs.r < rhs.r; };
    sort(v.begin(), v.end(), compR);
    for (int n = 0; n < N; ++n) {
        v[n].r = n;
    }

    // sort by left in decreasing order
    auto compL = [](const Seg & lhs, const Seg & rhs) { return lhs.l > rhs.l; };
    sort(v.begin(), v.end(), compL);

    BIT<int> b(N);
    vector<int> result(N);
    for (int n = 0; n < N; ++n) {
        result[v[n].i] = b.query(v[n].r);
        b.increment(v[n].r, 1);
    }

    for (const auto & r : result) {
        cout << r << '\n';
    }

    return 0;
}
