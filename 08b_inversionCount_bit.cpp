/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/INVCNT/
    Compiler: C++ (gcc 8.3), C++14 (gcc 8.3), C++14 (clang 8.0)

    Solution Description
    This solution is based on Binary Index Tree (BIT).
    In order to keep the space complexity linear respect to N and to avoid to
    deal with negative numbers, the input array is converted in an array that
    keeps the rank of each element. This conversion does not make any change
    in the answer.

    A BIT is used to keep track of the already considered elements.
    Iterate in reverse order the converted array:
    - the number of inversion of the current element r is the number of already
      considered rank values in the BIT that are smaller than r. This value is
      calculated with the function getSum(r - 1) that returns the sum from index
      0 to (r - 1).
    - then update the BIT adding 1 at position r to keep track of the already
      counted rank

    The sum of the number of inversion of each rank, as described before, is
    the total number of inversion of the array.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
struct BIT
{
    std::vector<T> x;

    // initialize by a constant
    BIT(size_t n, T a) : x(n + 1, a) {
        x[0] = 0;
        for (int k = 1; k + (k & -k) <= n; ++k) {
            x[k + (k & -k)] += x[k];
        }
    }

    void clear() {
        x.clear();
    }

    // b[k] += a
    void add(int k, T a) {
        for (++k; k < x.size(); k += k & -k) {
            x[k] += a;
        }
    }
  
    // sum b[0,k)
    T sum(int k) {
        T s = 0;
        for (++k; k > 0; k &= k - 1) {
            s += x[k];
        }
        return s;
    }
};

size_t BIT_inv(vector<int> & v, int n)
{
    // convert to rank
    vector<int> tmp(v);
    sort(tmp.begin(), tmp.end());
    for (size_t i = 0; i < n; ++i) {
        v[i] = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin() + 1;
    }

    size_t invs = 0;
    BIT<size_t> b(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        invs += b.sum(v[i] - 1);
        b.add(v[i], 1);
    }

    b.clear();

    return invs;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        vector<int> v(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        cout << BIT_inv(v, N) << '\n';

        v.clear();
    }

    return 0;
}
