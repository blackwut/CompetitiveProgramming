/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/next-larger-element/0

    Solution Description
    Iterating in the reverse way the array of elements. Make use of a stack to
    keep elements larger than the current one.
    For each element in the array, iterate over the stack to find the first
    greater element, removing all elements that are smaller.
    If no element is greater than the current one, the value -1 is stored in the
    result vector.
    Then the current element is pushed into the stack.

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
        vector<int64_t> v;
        v.reserve(N);
        for (int n = 0; n < N; ++n) {
            int64_t x;
            cin >> x;
            v.push_back(x);
        }

        vector<int64_t> result = nextLargerElement(v);
        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << " ";
        }
        cout << endl;

        result.clear();
        v.clear();
    }

    return 0;
}
