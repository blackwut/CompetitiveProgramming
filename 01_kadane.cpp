/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0

    Solution Description
    Iterate the array, if the sum is positive, add the i-th element to sum,
    otherwise replace sum with this element and go on iterating.
    Then compare the sum with the max, if the sum is larger, update max with
    sum.
    The max value will be the maximum sum of a sub-array since:
    1. The sum of each prefix sub-array of the maximum sum is positive,
       otherwise the prefix sub-array could be removed
    2. The value of the element before the first element of the maximum sum
       sub-array is negative

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

int kadane(const vector<int> & v)
{
    int sum = v.front();
    int max = sum;

    for (auto i = v.begin() + 1; i != v.end(); ++i) {
        const int val = *i;
        sum = (sum > 0) ? sum + val : val;
        if (sum > max) {
            max = sum;
        }
    }

    return max;
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

        int result = kadane(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
