/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/trapping-rain-water/0

    Solution Description
    

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
using namespace std;

int auxRainWater(int & level, const int val) {
    if (val > level) {
        level = val;
    }
    return level - val;
}

int trappingRainWater(const std::vector<int> & vec) {
    auto left  = vec.begin();
    auto right = vec.end() - 1;

    int rain  = 0;
    int level = 0;

    while (left != right) {
        const int leftVal  = *left;
        const int rightVal = *right;
        if (leftVal <= rightVal) {
            rain += auxRainWater(level, leftVal);
            ++left;
        } else {
            rain += auxRainWater(level, rightVal);
            --right;
        }
    }
    return rain;
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

        int result = trappingRainWater(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
