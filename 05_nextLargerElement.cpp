/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/next-larger-element/0

    Solution Description
    Iterate the array backwards. Make use of a stack to keep elements larger
    than the current one.
    For each element, iterate over the stack to find the first element larger
    than the current one, removing all elements that are smaller.
    If the element is found, it is stored in the result vector, otherwise it is
    stored the value -1.
    Then the current element is pushed into the stack.
    The solution is provided printing the result vector backwards.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int64_t> nextLargerElement(const vector<int64_t> & v)
{
    vector<int64_t> result;
    result.reserve(v.size());
    stack<int64_t> s;

    for (auto i = v.rbegin(); i != v.rend(); ++i) {
        int64_t r = -1;
        while (!s.empty()) {
            const int64_t val = s.top();
            if (val > *i) {
                r = val;
                break;
            }
            s.pop();
        }

        result.push_back(r);
        s.push(*i);
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
        cin >> N;

        vector<int64_t> v(N);
        for (int n = 0; n < N; ++n) {
            cin >> v[n];
        }

        vector<int64_t> result = nextLargerElement(v);
        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << ' ';
        }
        cout << '\n';

        result.clear();
        v.clear();
    }

    return 0;
}
