/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/missing-number-in-array/0

    Solution Description
    Be sum = "prefix sum on the given array".
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

    for (int i = 0; i < T; ++i) {
        int N;
        cin >> N;
        const int totalSum = N * (N + 1) / 2;
        int sum = 0;
        for (int j = 0; j < N - 1; ++j) {
            int x;
            cin >> x;
            sum += x;
        }
        cout << totalSum - sum;
        cout << endl;
    }

    return 0;
}
