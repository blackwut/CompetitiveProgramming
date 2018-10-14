/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0

    Solution Description
    Iterate the array and sum the elements if the sum remains positive. If not
    replace sum with the current element and go on iterating.
    Compare the sum with the max, if the sum is larger, update max with sum.
    The max value will be the maximum sum of a sub-array because:
    1. The sum of each prefix sub-array of the maximum sum is positive,
       otherwise the prefix sub-array could be removed
    2. The value of the element before the first element of the maximum sum
       sub-array is negative

    Time  Complexity: O(N)
    Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

int kadane(vector<int> & v)
{
    auto i = v.begin();
    int sum = (int) *i;
    int max = sum;

    for (++i; i != v.end(); ++i)
    {
        const int val = (int) *i;
        sum = (sum > 0) ? sum + val : val;
        if (sum > max) max = sum;
    }

    return max;
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

        int result = kadane(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
