/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0

    Solution Description
    Sort meetings by finishing time and take them greedily, that is select the
    first meeting, then keep selecting the next meeting that start after the
    finish of the current one.
    The greedy solution is optimal:
    Let x the first meeting in the greedy solution X. Suppose that there is an
    optimal solution Y that differ from X and does not include x. Let be y the
    first meeting of Y. Since x ends before y, {x} U Y \ {y} is still optimal.
    So we can state that exchanging x with y and repeating inductively that
    process we can obtain a solution that is still optimal.

    Time  Complexity: O(N log N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Meeting
{
    int s;  // start
    int f;  // finish
    int p;  // position

    inline bool operator<(const Meeting & rhs) const { return f < rhs.f; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        vector<Meeting> meetings(N);
        vector<int> result;

        for (int n = 0; n < N; ++n) {
            cin >> meetings[n].s;
        }

        for (int n = 0; n < N; ++n) {
            cin >> meetings[n].f;
            meetings[n].p = n;
        }

        sort(meetings.begin(), meetings.end());

        Meeting current = meetings[0];
        result.push_back(current.p);
        for (int n = 1; n < N; ++n) {
            if (current.f < meetings[n].s) {
                current = meetings[n];
                result.push_back(current.p);
            }
        }

        for (const auto & r : result) {
            cout << r + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}
