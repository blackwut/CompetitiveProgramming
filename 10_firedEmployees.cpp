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
    bool isPrime(int n)
    {
        if (n <= 1) return false;
        if (n == 2) return true;

        const int sqrtn = sqrt(n);
        for (int i = 2; i <= sqrtn; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int firingEmployees(const vector<int> & v,  int n)
    {
        vector<int> ranks[n + 1];
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

        int result = 0;
        for (int i = 1; i <= n; ++i) {
            if (seniors[i] &&  isPrime(seniors[i] + i)) {
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

        v.clear();
    }

    return 0;
}
