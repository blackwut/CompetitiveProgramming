/**
    Author:  Alberto Ottimo
    Problem: https://www.spoj.com/problems/INVCNT/

    Solution Description
    In order to keep the space complexity linear respect to `n` and to avoid to
    deal with negative numbers, the input array is converted in an array that
    keeps the rank of each element.
    This conversion does not make any change in the answer as the greater
    elements remain greater and at same position.

    A Binary Index Tree (BIT) is used to keep track of the already considered
    elements.
    Iterate in reverse order the converted array:
    - the number of inversion of the current element `r` is the number of
      already considered rank values in the BIT that are smaller than `r`. This
      value is calculated with the function `getSum(r - 1)` that returns the
      sum from index 0 to (r - 1).
    - then update the BIT adding 1 at position `r` to keep track of the already
      counted rank

    The sum of the number of inversion of each rank, as described before, is
    the total number of inversion of the array.

    Time  Complexity: O(N log_2 N)
    Space Complexity: O(N)
*/

#include <iostream>
#include "Structures/BIT.cpp"

using namespace std;


void convertToRankArray(int * a, int n) 
{ 
    vector<int> tmp(a, a + n);
    sort(tmp.begin(), tmp.end());
  
    for (size_t i = 0; i < n; ++i) {
        // update the value of a[i] with its rank in the ordered array
        a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1; 
    } 
} 

size_t BIT_inv(int * a, size_t n)
{
    size_t invs = 0;
    convertToRankArray(a, n);

    BIT<int> b(n, 0);

    for (ssize_t i = n - 1; i >= 0; i--) {
        invs += b.getSum(a[i] - 1); 
        b.add(a[i], 1); 
    }
    return invs;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;

        int * a = (int *)malloc(N * sizeof(int));
        for (int n = 0; n < N; ++n) {
            cin >> a[n];
        }

        size_t result = BIT_inv(a, N);
        cout << result;
        cout << endl;

        free(a);
    }

    return 0;
}
