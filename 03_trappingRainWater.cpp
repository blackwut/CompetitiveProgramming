/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/trapping-rain-water/0

    Solution Description
    For each elevation point H_i, calculate the maximum elevation on its left
    [0...i] and do the same to its right [i...n]. Call them lMax and rMax
    respectively.
    The trapped water at the elevation point i with height H_i is:
    water = min(lMax, rMax) - H_i
    The total trapped water is obtained summing up the water at each point.

    Observing that the trapped water cannot be more than the minimum between the
    left maximum and the right maximum, the computation can be improved using
    two indices: one starting from the left side, that is incremented when the
    elevation is smaller than the right one; the other starting from the right
    side that is decremented when the elevation is smaller than the left one.
    At each iteration, if the left elevation is smaller than the right one,
    calculate max as the maximum between the current elevation and the previous
    max. Then compute the value of water as (water = max - H_i), and finally
    increment the left index.
    Otherwise, if the right elevation is smaller than the left one, calculate
    the max as the maximum between the current elevation and the previous max,
    Then compute the value of water as (water = max - H_i), and finally
    decrement the right index.
    Again, the total trapped water is obtained summing up the water at each
    elevation point.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T trappingRainWater(const std::vector<T> & v)
{
    auto left  = v.begin();
    auto right = v.end() - 1;

    T water = 0;
    T maxVal = 0;

    while (left != right) {
        const T leftVal  = *left;
        const T rightVal = *right;

        if (leftVal <= rightVal) {
            maxVal = max(maxVal, leftVal);
            water += maxVal - leftVal;
            ++left;
        } else {
            maxVal = max(maxVal, rightVal);
            water += maxVal - rightVal;
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

        cout << trappingRainWater(v) << '\n';
    }

    return 0;
}
