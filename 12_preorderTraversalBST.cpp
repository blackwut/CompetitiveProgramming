/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/preorder-traversal-and-bst/0

    Solution Description
    https://www.geeksforgeeks.org/check-if-a-given-array-can-represent-preorder-traversal-of-binary-search-tree/
    

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

int preorderTraversal(const vector<int> & v)
{
    int root = numeric_limits<int>::min();
    stack<int> s;

    for (int & x : v) {
        if (x < root) return 0; 

        // keep removing all nodes smaller than current one
        // and make the last removed item as new root
        while (!s.empty() && s.top() < x) {
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
        vector<int> v;
        v.reserve(N);
        for (int n = 0; n < N; ++n) {
            int x;
            cin >> x;
            v.push_back(x);
        }

        int result = preorderTraversal(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
