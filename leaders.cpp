/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0

    Solution Description
    Iterate the array in the reverse way, starting from the end, checking if
    the element is greater than the max. If that is true, consider this element 
    a leader.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> leaders(vector<int> & v)
{
    vector<int> result;

    auto r = v.rbegin();
    int max = (int) *r;
    result.push_back(max);

    while (++r != v.rend()) {
        const int val = (int) *r;
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
    int N;
    vector<int> v;

    cin >> T;
    
    while (T--)
    {
        cin >> N;
        v.reserve(N);
        while (N--)
        {
            int x;
            cin >> x;
            v.push_back(x);
        }

        vector<int> result = leaders(v);

        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << " ";
        }
        cout << endl;

        v.clear();
    }

    return 0;
}
