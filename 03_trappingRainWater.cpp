/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/trapping-rain-water/0

    Solution Description
    For each elevation point i, calculate the maximum elevation on its left
    [0...i] and do the same to the right [i...n]. Call them lMax and rMax
    respectively.
    The trapped water in the elevation point i with height H_i is:
    water = min(lMax, rMax) - H_i
    The total trapped water is obtained summing up the water of each point.

    Observing that the trapped water cannot be more than the minimum between the
    left and the right maximum, the computation can be improved using two
    indices. One starting from the left side, that is increased when the
    elevation is less than the right one. One starting from the right side that
    is decremented when the elevation is less than the left one.
    At each iteration, if the left elevation is less than the right one,
    calculate the maximum between the current elevation and the previous max.
    Then compute the value of water as before (water = max - H_i), and finally
    increment the left index.
    If the right elevation is less than the left one, calculate the maximum
    between the current elevation and the previous max, calculate the value of
    water and decrement the right index.
    Again the total is obtained summing up the water at each point.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int trappingRainWater(const std::vector<int> & vec)
{
    auto left  = vec.begin();
    auto right = vec.end() - 1;

    int water = 0;
    int max = 0;

    while (left != right) {
        const int leftVal  = *left;
        const int rightVal = *right;

        if (leftVal <= rightVal) {
            max = MAX(max, leftVal);
            water += max - leftVal;
            ++left;
        } else {
            max = MAX(max, rightVal);
            water += max - rightVal;
            --right;
        }
    }

    return water;
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

        int result = trappingRainWater(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
