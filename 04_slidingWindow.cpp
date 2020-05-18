/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0

    Solution Description
    This solution make use of a double ended queue that stores indices of the
    elements inside the current window, "sorted" by element value.
    Each time an index i is pushed to the back of the queue, all indices
    referring to elements smaller than the one pointed by i are removed from
    back.
    Each time the window moves, all the indices outside the window are removed
    from front.
    In this way all the elements in the queue are only the right-leaders of the
    current window.
    For each window, the element pointed by the front index in the queue is
    stored in a vector.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

vector<int> maxsSubarray(const vector<int> & v, int K)
{
    vector<int> result;
    result.reserve(v.size() - K + 1);
    std::deque<int> d;

    for (int i = 0; i < v.size(); ++i) {

        // Removes elements no longer in the window
        while (!d.empty() and d.front() <= i - K) {
            d.pop_front();
        }

        // Removes elements smaller than the current element
        while (!d.empty() and v[d.back()] <= v[i]) {
            d.pop_back();
        }

        // Add the current element
        d.push_back(i);

        // Store the max element in the window into result
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

        vector<int> result = maxsSubarray(v, K);
        for (auto i = result.begin(); i != result.end(); ++i) {
            cout << *i << " ";
        }
        cout << endl;

        result.clear();
        v.clear();
    }

    return 0;
}
