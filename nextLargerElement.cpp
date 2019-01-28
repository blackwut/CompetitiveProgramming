/**
    Author:  Alberto Ottimo
    Problem: https://practice.geeksforgeeks.org/problems/next-larger-element/0

    Solution Description
    Iterating in the reverse way the provided array of elements. Make use of a
    stack in order to keep all elements after the current one.
    If there is no "next greater element", -1 is stored in the result vector.
    Otherwise iterate over the stack to find the first greater element of the 
    current one removing all elements smaller the current one. If no element is
    greater than the current one, it is stored -1 in the result vector.
    In any case, the current element is pushed into the stack because is the
    next element in the next iteration.

    Time  Complexity: O(N)
    Space Complexity: O(N)
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextLargerElement(const vector<int> & v)
{
    vector<int> result;
    result.reserve(v.size());
    stack<int> s;

    for (auto i = v.rbegin(); i != v.rend(); ++i) {
        int r = -1;
        while (!s.empty()) {
            const int val = s.top();
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
        vector<int> v;
        v.reserve(N);
        for (int n = 0; n < N; ++n) {
            int x;
            cin >> x;
            v.push_back(x);
        }

        vector<int> result = nextLargerElement(v);
        for (auto r = result.rbegin(); r != result.rend(); ++r) {
            cout << *r << " ";
        }
        cout << endl;

        result.clear();
        v.clear();
    }

    return 0;
}
