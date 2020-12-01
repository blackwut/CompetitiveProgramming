/**
    Author:  Alberto Ottimo
    Problem: https://codeforces.com/problemset/problem/320/A?locale=en

    Solution Description
    Consider a dictionary D of strings in which each string is not a suffix of
    the other strings.
    Let consider the given number as a string and call it S. The problem is to
    split S in pieces which are elements of D.
    The solution can be found with a greedy approach. Sort the dictionary D by
    string's length in decreasing order. Check if at least one string in D is a
    prefix of S. If a string in D is a prefix of S, remove that prefix and keep
    going with the process. If none of the strings in D is a prefix of S, then
    the provided number is not a magic number.

    Time  Complexity: O(|S| * |D|)
    Space Complexity: O(|S| + (sum of |d_i| in D))
*/

#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    bool b = true;
    size_t i = 0;
    while (i < s.size()) {
        if (s[i] == '1' and s[i + 1] == '4' and s[i + 2] == '4') {
            i += 3;
            continue;
        }
        if (s[i] == '1' and s[i + 1] == '4') {
            i += 2;
            continue;
        }
        if (s[i] == '1') {
            i += 1;
            continue;
        }
        b = false;
        break;
    }

    cout << (b ? "YES" : "NO") << '\n';

    return 0;
}
