/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/preorder-traversal-and-bst/0

    Solution Description
    In the pre-order traversal of BST, each root of any subtree is processed
    before any of its child nodes.
    Create an empty stack and set the root as -INF (e.g. INT_MIN).
    Iterate the provided array:
    - if the current element is smaller than root, return false
    - otherwise remove elements smaller than the current element and update the
      root with it
    - finally, push the current node into the stack.
    If the first condition is never false, the provided array represents a
    pre-order traversal of a BST.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

template <typename T>
int preorderTraversal(const vector<T> & v)
{
    T root = numeric_limits<T>::min();
    stack<T> s;

    for (const auto & x : v) {
        if (x < root) return 0;
        while (!s.empty() and s.top() < x) {
            root = s.top();
            s.pop();
        }
        s.push(x);
    }

    return 1;
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

        vector<int> v(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        cout << preorderTraversal(v) << '\n';
    }

    return 0;
}
