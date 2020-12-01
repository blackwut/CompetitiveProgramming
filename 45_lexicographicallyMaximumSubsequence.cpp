/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/196/A?locale=en

    Solution Description
    Scan the string from right to left and store the current maximum in a stack.
    The solution is provided by printing the values in the stack.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    char max = 'a' - 1;
    stack<char> result;
    for (int i = s.size() - 1; i >= 0; --i) {
        const char c = s[i];
        if (c >= max) {
            max = c;
            result.push(c);
        }
    }

    while (!result.empty()) {
        cout << result.top();
        result.pop();
    }
    cout << '\n';

    return 0;
}
