/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0

    Solution Description
    Let be v[i] the i-th number of steps we can take from position i.
    Keep track of the number of steps (#steps), the maximum position we can
    reach (#max) and the number of jumps (#jumps) taken.
    The first element must be traversed, so #steps and #max are initialized with
    the first element value, and #jumps with 1.
    Iterate from the second element. For each element we check if we are at the
    end of the array (i == n-1), if so we return #jumps. We update #max with the
    maximum between #max and (i + v[i]), then we decrement #steps since we are
    taking a step. If we cannot take more steps (steps == 0) we must take a
    jump, hence we increment #jumps by 1.
    Then we checks if element (i + 1) is still reachable (i.e. i < #max). If so
    we update #steps with (#max - i), otherwise we conclude that the end of the
    array is not reachable and we return -1.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int minJumps(vector<int> & v)
{
    const int n = v.size();
    int steps = v[0];
    int maxSteps = v[0];
    int jumps = 1;

    for (int i = 1; i < n && steps > 0; ++i) {
        if (i == n - 1) return jumps;

        maxSteps = max(maxSteps, i + v[i]);

        --steps;
        if (steps == 0) {
            ++jumps;
            steps = maxSteps - i;
        }
    }
    return -1;
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

        int result = minJumps(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
