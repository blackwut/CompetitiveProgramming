/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/largest-even-number/0

    Solution Description
    The solution is a modification of the counting sort. It is enough to count
    the number of occurrences of each digit.
    Find the minimum even number (or odd number in case no even number found)
    and subtract 1 from the number of occurrences associated to it.
    Then start iterate from the greatest digit and print it "occurrences" times.
    Finally, print the minimum number found.

    Time  Complexity: O(N)
    Space Complexity: O(1)

    Where N is the number of digits of the number P
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        string P;
        cin >> P;

        // count the occurrences of each digit
        vector<int> occurences(10, 0);
        for (const char & c : P) {
            occurences[c - '0']++;
        }

        // find the minimum among odd digits in case an even digit is not found
        int min = 11;
        for (int i = 9; i >= 0; i -= 2) {
            if (occurences[i] > 0) {
                min = i;
            }
        }

        // find the minimum among even digits
        for (int i = 8; i >= 0; i -= 2) {
            if (occurences[i] > 0) {
                min = i;
            }
        }

        // decrement the occurrences of the minimum digit found
        occurences[min]--;

        for (int i = 9; i >= 0; --i) {
            for (int j = 0; j < occurences[i]; ++j) {
                cout << i;
            }
        }
        cout << min << '\n';
    }

    return 0;
}
