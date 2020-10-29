/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/problemset/problem/579/B?locale=en

    Solution Description
    A team is a tuple (i, j, s), formed by teammate i, teammate j and strength
    s, which is the team strength of these teammates together.
    Sort all the teams by strength in decreasing order. Then iterate the sorted
    teams, assigning at each teammate the other teammate's id, only if both of
    them are not yet in a team.

    Time  Complexity: O(N^2)
    Space Complexity: O(N^2)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Team
{
    int i;
    int j;
    int s;

    Team(int i, int j, int s)
    : i(i)
    , j(j)
    , s(s)
    {}

    inline bool operator<(const Team & rhs) const { return s < rhs.s; };
};

vector<int> findTeamMembers(vector<Team> & v, int N)
{
    sort(v.rbegin(), v.rend());

    vector<int> teammates(2 * N);
    for (const Team & t: v) {
        // if both teammates are not in a team
        if (teammates[t.i] == 0 and teammates[t.j] == 0) {
            teammates[t.i] = t.j + 1; // store the id of its teammate j
            teammates[t.j] = t.i + 1; // store the id of its teammate i
        }
    }

    return teammates;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Team> teams;
    teams.reserve(N * (N - 1) / 2);
    for (int i = 0; i < (2 * N); ++i) {
        for (int j = 0; j < i; ++j) {
            int s;
            cin >> s;
            teams.emplace_back(i, j, s);
        }
    }

    const auto result = findTeamMembers(teams, N);
    for (const auto & i : result) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
