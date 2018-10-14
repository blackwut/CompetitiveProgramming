/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/missing-number-in-array/0

    Solution Description
    Be sum = "prefix sum on the given array".
    Since the sum of numbers from 1 to N is nsum = (N * (N + 1)) / 2
    hence the missingNumber = nsum - sum

    Time  Complexity: O(N)
    Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

int missingNumber(vector<int> & v)
{
    int sum = 0;
    for (auto i = v.begin(); i != v.end(); ++i) {
        sum += (int) *i;
    }

    const int size = v.size() + 1;
    return (size * (size + 1)) / 2 - sum;
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
        v.reserve(--N);
        while (N--)
        {
            int x;
            cin >> x;
            v.push_back(x);
        }

        int result = missingNumber(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
