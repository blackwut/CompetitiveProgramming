/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0

    Solution Description
    This problem is solved with dynamic programming.
    Let be v_j the max number of steps that can be made from position j.
    Create an array J of size N that will keep track of the minimum number of
    jumps needed to reach each position i. Initialize all values to INF except
    for J[0] = 0 since we are starting from the first position. The solution is
    found at J[N - 1].
    Suppose that we know the minimum number of jumps needed to reach each
    position up to i, say [J_0, ..., J_i]. We can calculate J_i+1 as
    min(J[i], J[j] + 1) if i <= j + v_j, iterating for j from 0 to i (excluded).
    In this way we are updating J_i+1 each time we found a better way to reach
    position i+1 starting from position j. The condition ensure that we are
    making a legal jump, that is a jump from j to at most j + v_j.

    Time  Complexity: O(N^2)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

constexpr int MAX = 0xBADCAFE;

int minJumps(const vector<int> & v)
{
    const int n = v.size();

    if (n == 0 or v[0] == 0) return MAX;

    vector<int> jumps(n, MAX);
    jumps[0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (i <= j + v[j]) {
                jumps[i] = min(jumps[i], jumps[j] + 1);
                break;
            }
        }
    }
    return jumps[n - 1];
} 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    vector<int> v;
    v.reserve(10000000);

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        v.resize(N);
        for (auto & val : v) {
            cin >> val;
        }

        const auto result = minJumps(v);
        cout << (result == MAX ? -1 : result)  << '\n';

        v.clear();
    }

    return 0;
}
