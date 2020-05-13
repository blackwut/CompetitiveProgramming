/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/missing-number-in-array/0

    Solution Description
    Be sum the prefix sum on the given array.
    Since the sum of numbers from 1 to N is totalSum = (N * (N + 1)) / 2
    hence the missingNumber = totalSum - sum

    Time  Complexity: O(N)
    Space Complexity: O(1)
*/

#include <iostream>
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

        int sum = 0;
        for (int n = 0; n < N - 1; ++n) {
            int x;
            cin >> x;
            sum += x;
        }

        const int totalSum = N * (N + 1) / 2;
        cout << totalSum - sum;
        cout << endl;
    }

    return 0;
}
