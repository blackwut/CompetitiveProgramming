#include <bits/stdc++.h>
using namespace std;

void solution(vector<int> & v)
{
    // auto r = v.begin();
    // auto r = v.rbegin();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    int N;
    vector<int> v;

    cin >> T;
    
    while (T--)
    {
        cin >> N;
        v.reserve(N);
        while (N--)
        {
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
