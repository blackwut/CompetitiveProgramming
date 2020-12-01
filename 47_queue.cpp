/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/141/C?locale=en

    Solution Description
    Sort people in increasing order by a_i, that is the number of people who are
    higher and stand in the queue in front of person i.
    Check if a_i is less than or equal to i to ensure that there are at least
    a_i people in front of person i.
    Now estimate the height of people processing them from left to right.
    In front of person i, there are a_i people taller than him and (i - a_i)
    shorter, then the height of person i can be estimated as (i - a_i + 1).
    Directly setting the estimated height will make the solution wrong. In order
    to solve this problem, people with height greater or equal to person i has
    to be increased by 1.

    Time  Complexity: O(N^2)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Person
{
    char name[12];  // name of him/her
    int n;          // taller people in front of him/her
    int h;          // estimated height of him/her

    inline bool operator<(const Person & rhs) const { return n < rhs.n; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Person> people(N);
    for (int n = 0; n < N; ++n) {
        cin >> people[n].name;
        cin >> people[n].n;
    }

    sort(people.begin(), people.end());

    for (int n = 0; n < N; ++n) {
        if (people[n].n > n) {
            cout << -1 << '\n';
            return 0;
        }
        people[n].h = n - people[n].n + 1;
        for (int i = 0; i < n; ++i) {
            if (people[i].h >= people[n].h) {
                people[i].h++;
            }
        }
    }

    for (const auto & p : people) {
        cout << p.name << ' ' << p.h << '\n';
    }

    return 0;
}
