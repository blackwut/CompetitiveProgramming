/**
    Author:  Alberto Ottimo
    Problem: 

    Solution Description
    

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
using namespace std;

void solution(const vector<int> & v)
{
    // auto i = v.begin();
    // auto r = v.rbegin();
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

        int result = solution(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
