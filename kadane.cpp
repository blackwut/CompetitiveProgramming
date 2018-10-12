#include <bits/stdc++.h>
using namespace std;

int kadane(vector<int> & v)
{
    auto i = v.begin();
    int sum = (int) *i;
    int result = sum;

    for (++i; i != v.end(); ++i)
    {
        const int val = (int) *i;
        sum = (sum > 0) ? sum + val : val;
        if (sum > result) result = sum;
    }

    return result;
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

        int result = kadane(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
