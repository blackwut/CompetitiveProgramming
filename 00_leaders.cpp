/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0

    Solution Description
    Iterate the array backwards, if the i-th element is greater than max, update
    consider this element a leader and the new max.
    The last element is always a leader.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> leaders(const vector<int> & v)
{
    vector<int> result;
    int max = v.back();
    result.push_back(max);

    for (auto r = v.rbegin() + 1; r != v.rend(); ++r) {
        const int val = *r;
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

        vector<int> result = leaders(v);
        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << ' ';
        }
        cout << '\n';

        result.clear();
        v.clear();
    }

    return 0;
}
