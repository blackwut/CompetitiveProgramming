/**
    Author:  Alberto Ottimo
    Problem: 

    Solution Description
    

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(const vector<int> & v)
{
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

        cout << solution(v) << '\n';
    }

    return 0;
}
