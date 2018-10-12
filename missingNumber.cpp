#include <bits/stdc++.h>
using namespace std;

int missingNumber(vector<int> & v)
{
    int sum = 0;
    for (auto i = v.begin(); i != v.end(); ++i) {
        sum += (int) *i;
    }

    const int size = v.size() + 1;
    return (size * (size + 1)) / 2 - sum;
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
        v.reserve(--N);
        while (N--)
        {
            int x;
            cin >> x;
            v.push_back(x);
        }

        int result = missingNumber(v);
        cout << result;
        cout << endl;

        v.clear();
    }

    return 0;
}
