/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/problemset/problem/579/B?locale=en

    Solution Description
    

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Team
{
    size_t i;
    size_t j;
    int32_t s;

    Team(size_t i, size_t j, size_t s) :
    i(i),
    j(j),
    s(s)
    {}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t N;
    cin >> N;
    vector<Team> teams;
    teams.reserve( N * (N - 1) / 2 );

    for (size_t i = 0; i < (2 * N); ++i) {
        for (size_t j = 0; j < i; ++j) {
            int32_t s;
            cin >> s;
            teams.emplace_back(i, j, s);
        }
    }

    sort(teams.begin(), teams.end(),
        [](const Team & l, const Team & r) { return l.s > r.s; });

    vector<size_t> teammate( 2 * N );

    for(Team & t: teams) {
        if(teammate[t.i] == 0 and teammate[t.j] == 0) {
            teammate[t.i] = t.j + 1;
            teammate[t.j] = t.i + 1; 
        }
    }

    for (auto i = teammate.begin(); i < teammate.end(); ++i ) {
        cout << *i << " ";
    }
    cout << endl;

    teammate.clear();
    teams.clear();

    return 0;
}
