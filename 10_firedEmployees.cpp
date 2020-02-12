/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/firing-employees/0/

    Solution Description
    TODO: complete

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define PRIMES_COUNT (200000)


vector<bool> createPrimes()
{
    vector<bool> primes(PRIMES_COUNT, true);
    for (int p = 2; p * p <= PRIMES_COUNT; ++p) {
        if (primes[p]) {                                     // if primes[p] is not changed, then it is a prime
            for (int i = p * p; i <= PRIMES_COUNT; i += p) { // update all multiples of p greater that are >= p^2 and less then n
                primes[i] = false;
            }
        }
    }

    return primes;
}

int firingEmployees(const vector<int> & v, const vector<bool> & primes)
{
    const int n = v.size();

    // add the position of each employee to his senior's list
    vector< vector<int> > ranks(n + 1, vector<int>());
    for (int i = 0; i < n; ++i) {
        ranks[v[i]].push_back(i + 1);
    }

    vector<int> seniors(n + 1, 0);
    stack<int> s;

    // calculate the number of seniors
    s.push(ranks[0].front());
    for (int i = 0; i < n; ++i) {
        vector<int> & subordinates = ranks[s.top()];
        s.pop();
        for (int sub : subordinates) {
            seniors[sub] = 1 + seniors[v[sub - 1]];
            s.push(sub);
        }
    }

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        if (seniors[i] && primes[seniors[i] + i]) {
            ++result;
        }
    }

    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<bool> primes = createPrimes();

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

        int result = firingEmployees(v, primes);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
