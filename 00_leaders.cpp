/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0

    Solution Description
    Iterate the array backward, checking if the i-th element is greater than
    the max. If it is true, update the max and consider this element a leader.

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
    result.push_back(max);  // The first element is always a leader

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
        vector<int> v;
        v.reserve(N);
        for (int n = 0; n < N; ++n) {
            int x;
            cin >> x;
            v.push_back(x);
        }

        vector<int> result = leaders(v);
        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << " ";
        }
        cout << endl;

        result.clear();
        v.clear();
    }

    return 0;
}
