#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");
    int n, k;
    fin >> n >> k;
    vector<long long> g(n);
    int i;
    for (i = 0; i < n; i++)
        fin >> g[i];
    long long left = 0, right = 0;
    for (i = 0 ; i < n; i++)
    {
        right += g[i];
        if (g[i] > left)
            left = g[i];
    }
    long long answer = -1;
    while (left <= right)
    {
        long long mid = (left + right) / 2, nrf = 1, gc = 0;
        for (i = 0; i < n; i++)
        {
            if (gc + g[i] > mid)
            {
                nrf++;
                gc = 0;
            }
            gc += g[i];
        }
        if (nrf <= k)
        {
            answer = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    fout << answer << endl;
    fin.close();
    fout.close();
    return 0;
}
