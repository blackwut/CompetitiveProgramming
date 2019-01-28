/**
    Author:  Alberto Ottimo
    Problem: http://codeforces.com/problemset/problem/37/A?locale=en

    Solution Description
    

    Time  Complexity: O()
    Space Complexity: O()
*/

#include <iostream>
#include <algorithm> 
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> v;
    v.reserve(N);
    for (int n = 0; n < N; ++n) {
        int x;
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end());
    int currentHeight = 0;
    int maxHeight = 1;
    int currentBar = 0;
    int numBars= 0;

    for (int i = 0; i < N; ++i) {
        const int bar = v[i];
        
        if (bar > currentBar) {
            currentBar = bar;
            currentHeight = 0;
            numBars++;
        }
        currentHeight++;

        if (currentHeight > maxHeight) {
            maxHeight = currentHeight;
        }
    }

    cout << maxHeight;
    cout << " ";
    cout << numBars;
    cout << endl;

    v.clear();

    return 0;
}
