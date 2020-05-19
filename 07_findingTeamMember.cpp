/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/problemset/problem/579/B?locale=en

    Solution Description
    A team is a tuple (i, j, s), formed by the teammate i, the teammate j and
    the strength s, which is the team strength considering these teammates.
    Sort by strength all the teams in decreasing order. Then iterate the sorted
    teams, assigning at each teammate the other teammate's id, only if both of
    them are not yet in a team.

    Time  Complexity: O(N^2)
    Space Complexity: O(N^2)

    Where N is the number of teams to find.
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Team
{
    int i;
    int j;
    int s;

    Team(int i, int j, int s) :
    i(i),
    j(j),
    s(s)
    {}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<Team> teams;
    teams.reserve( N * (N - 1) / 2 );

    for (int i = 0; i < (2 * N); ++i) {
        for (int j = 0; j < i; ++j) {
            int s;
            cin >> s;
            teams.emplace_back(i, j, s);
        }
    }

    sort(teams.begin(), teams.end(),
        [](const Team & lhs, const Team & rhs) { return lhs.s > rhs.s; });

    vector<int> teammates( 2 * N );

    for(const Team & t: teams) {
        // if both teammates are not in a team
        if(teammates[t.i] == 0 and teammates[t.j] == 0) {
            teammates[t.i] = t.j + 1; // store the id of its teammate j
            teammates[t.j] = t.i + 1; // store the id of its teammate i
        }
    }

    for (const auto & i : teammates ) {
        cout << i << " ";
    }
    cout << endl;

    teammates.clear();
    teams.clear();

    return 0;
}
