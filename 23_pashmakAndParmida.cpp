/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/459/D?locale=en

    Solution Description
    Replace each value of the provided array A with its rank in the sorted
    array. Equal values will have the same rank value.
    Compute the suffix array S in which each entry S[i] stores the number of
    occurrences of A[i] in the suffix A[i + 1, n].
    Make use of a Binary Indexed Tree (BIT) to store at each position i the
    number of elements in S that have value i. The function BIT.query(k) returns
    the number of times f(i, n, A[i]) is smaller or equal to k.
    We want to compute the number of times that f(1, i, A[i]) > f(j, n, A[i])
    with the condition i < j.
    Processing the array A from left to right, f(j, n, A[i]) < k can be computed
    calling BIT.query(k - 1). Substituting k with f(1, i, A[i]) we have the
    previous inequality but without the condition i < j. To enforce this
    condition, the contribution S[1, i] has to be removed. This is simply done
    by subtracting 1 from the BIT at position S[i].

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

    // replace values with ranks
    vector<int> tmp(v);
    sort(tmp.begin(), tmp.end());
    for (auto & val : v) {
        val = lower_bound(tmp.begin(), tmp.end(), val) - tmp.begin();
    }

    BIT<int> b(N);
    vector<int> freq(N);
    vector<int> suff(N);
    for (int n = N - 1; n >= 0; --n) {
        const int f = freq[v[n]]++;
        suff[n] = f;
        b.increment(f, 1);
    }

    fill(freq.begin(), freq.end(), 0);

    int64_t result = 0;
    for (int n = 0; n < N; ++n) {
        b.increment(suff[n], -1);
        const int f = freq[v[n]]++;
        result += b.query(f - 1);
    }

    cout << result << '\n';

    return 0;
}


