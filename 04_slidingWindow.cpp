/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0

    Solution Description
    This solution make use of a double ended queue that stores indices of the
    elements inside the current window, "sorted" by element value.
    Each time the window moves, elements no longer in the window are removed.
    Then, the new index is pushed to the back of the queue and all indices
    referring to elements smaller than the new element are removed from the
    back of the queue.
    In this way all the elements in the queue are only the right-leaders of the
    current window.
    The max value in each window (sub-array) is the element pointed by the index
    obtained calling front() on the queue at each step.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

template <typename T>
vector<T> maxsSubarray(const vector<T> & v, int K)
{
    vector<T> result;
    result.reserve(v.size() - K + 1);
    std::deque<T> d;

    for (int i = 0; i < v.size(); ++i) {
        // Removes elements no longer in the window
        while (!d.empty() and d.front() <= i - K) {
            d.pop_front();
        }

        // Removes elements smaller than the current one
        while (!d.empty() and v[d.back()] <= v[i]) {
            d.pop_back();
        }

        // Add the current element
        d.push_back(i);

        // Store the max element of the window into result
        if (i >= K - 1) {
            result.push_back(v[d.front()]);
        }
    }

    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        int N;
        int K;
        cin >> N;
        cin >> K;

        vector<int> v(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        const auto result = maxsSubarray(v, K);
        for (const auto & i : result) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
