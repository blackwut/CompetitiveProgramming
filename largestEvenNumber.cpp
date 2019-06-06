/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/largest-even-number/0

    Solution Description
    The solution is a modification of the counting sort. It is enough to count
    the number of occurrences. 
    Find the minimum even number (or odd number in case no even number found)
    and subtract 1 from the number of occurrences associated to it.
    Then start iterate from the last digit and print it "occurrences" times.
    Finally print the minimum number found.

    Time  Complexity: O(N) where N is the number of digits in the number P
    Space Complexity: O(1)
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

        // Count the occurrences of each digit
        size_t occurences[10] = {0};
        for (char & c : P) {
            occurences[c - '0']++;
        }

        // Find the minimum among odd digits in case an even digit is not found
        size_t min = 11;
        for (ssize_t i = 9; i >= 0; i -= 2) {
            if (occurences[i] > 0) {
                min = i;
            }
        }

        // Find the minimum among even digits
        for (ssize_t i = 8; i >= 0; i -= 2) {
            if (occurences[i] > 0) {
                min = i;
            }
        }

        // Decrement the occurrence of the minimum digit found
        occurences[min]--;

        // Print the solution
        for (ssize_t i = 9; i >= 0; --i) {
            for (size_t j = 0; j < occurences[i]; ++j) {
                cout << i;
            }
        }
        cout << min;
        cout << endl;
    }

    return 0;
}
