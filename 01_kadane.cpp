/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0

    Solution Description
    Iterate the array, if the sum is positive, add the i-th element to sum,
    otherwise replace sum with this element. Then compare the sum with max, if
    it is larger, update max with it.

    The max value will be the maximum sum of a sub-array, since:
    1. The sum of each prefix sub-array of the maximum sum is positive,
       otherwise the prefix sub-array could be removed
    2. The value of the element before the first element of the maximum sum
       sub-array is negative

    Time  Complexity: O(N)
    Space Complexity: O(1)
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        int val;
        cin >> val;
        
        int sum = val;
        int max = val;
        for (int n = 1; n < N; ++n) {
            cin >> val;
            sum = (sum > 0) ? sum + val : val;
            max = sum > max ? sum : max;
        }

        cout << max << '\n';
    }

    return 0;
}
