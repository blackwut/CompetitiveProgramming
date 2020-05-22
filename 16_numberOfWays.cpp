/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/466/C?locale=en

    Solution Description
    Let be total the sum of the values in the vector. If total is not divisible
    by 3, then there are 0 ways to split the vector in three parts. Otherwise
    compute the vector c which stores at each position the number of suffixes
    that sum up to total/3. Then scan the vector keeping the sum up to the
    current value at position i. If this sum is equal to total/3, add c[i + 2]
    to the result.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>

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

    int64_t total = 0;
    for (const auto & x : v) {
        total += x;
    }

    if (total % 3) {
        cout << 0 << endl;
        v.clear();
        return 0;
    }

    total = total / 3;

    vector<int> c(N);
    int64_t sum = 0;

    for (int n = N - 1; n >= 0; --n) {
        sum += v[n];
        if (sum == total) {
            c[n] = 1;
        }
    }

    for (int n = N - 1; n > 0; --n) {
        c[n - 1] += c[n];
    }

    int64_t result = 0;
    sum = 0;
    for (int n = 0; n < N - 2; ++n) {
        sum += v[n];
        if (sum == total) {
            result += c[n + 2];
        }
    }

    cout << result;
    cout << endl;

    v.clear();

    return 0;
}
