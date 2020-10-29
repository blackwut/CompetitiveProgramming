/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0

    Solution Description
    Iterate the array backwards, if the i-th element is greater than max,
    consider this element a leader and the new max.
    The last element is always a leader.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

template <T>
vector<T> leaders(const vector<T> & v)
{
    vector<T> result;
    T max = v.back();
    result.push_back(max);

    for (auto r = v.rbegin() + 1; r != v.rend(); ++r) {
        const T val = *r;
        if (val >= max) {
            max = val;
            result.push_back(val);
        }
    }

    return result;
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

        const auto result = leaders(v);
        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << ' ';
        }
        cout << '\n';
    }

    return 0;
}
