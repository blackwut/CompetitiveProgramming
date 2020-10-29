/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/firing-employees/0/

    Solution Description
    For each employee calculate the number of seniors.
    Then count the number of employees whose the sum of their rank and the
    number of his/her seniors is a prime number.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

class Solution {
public:

    vector<bool> createPrimes(int max)
    {
        vector<bool> primes(max, true);
        primes[0] = false;
        primes[1] = false;

        for (int p = 2; p * p <= max; ++p) {
            if (primes[p]) {
                for (int i = p * p; i <= max; i += p) {
                    primes[i] = false;
                }
            }
        }

        return primes;
    }

    int firingEmployees(const vector<int> & v,  int n)
    {
        vector< vector<int> > ranks;
        ranks.resize(n + 1);
        for (int i = 0; i < n; ++i) {
            ranks[v[i]].push_back(i + 1);
        }

        vector<int> seniors(n + 1, 0);
        stack<int> s;

        // for each employee calculate the number of seniors
        s.push(ranks[0].front()); // Mr. Alfred
        for (int i = 0; i < n; ++i) {
            const auto subordinates = ranks[s.top()];
            s.pop();
            for (const int & sub : subordinates) {
                seniors[sub] = seniors[v[sub - 1]] + 1;
                s.push(sub);
            }
        }

        const auto is_prime = createPrimes(2 * n + 1);
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            if (seniors[i] &&  is_prime[seniors[i] + i]) {
                ++result;
            }
        }

        return result;
    }
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

        vector<int> v(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        Solution sol;
        cout << sol.firingEmployees(v, N) << '\n';
    }

    return 0;
}
