#include <bits/stdc++.h>
using namespace std;

const int INF = 1e7;

int main()
{
    ifstream fin("prinel.in");
    ofstream fout("prinel.out");
    int n, k;
    fin >> n >> k;
    vector<int> target(n), p(n);
    int i, maxim = -1;
    for (i = 0 ; i < n ; i++)
    {
        fin >> target[i];
        if (target[i] > maxim)
            maxim = target[i];
    }
    for (i = 0 ; i < n ; i++)
        fin >> p[i];
    vector<int> dist(maxim + 1, INF);
    dist[1] = 0;
    for (i = 1 ; i <= maxim ; i++)
        if (dist[i] < INF)
            for (int d = 1 ; d * d <= i ; d++)
                if (i % d == 0)
                {
                    int x1 = i + d;
                    if (x1 <= maxim)    
                        if (dist[i] + 1 < dist[x1])
                            dist[x1] = dist[i] + 1;
                    int x2 = i + (i / d);
                    if (x1 != x2)
                        if (x2 <= maxim)    
                            if (dist[i] + 1 < dist[x2])
                                dist[x2] = dist[i] + 1;
                }
    vector <int> dp(k + 1, 0);
    int j;
    for (i = 0 ; i < n ; i++)
    {
        int c = dist[target[i]];
        for (j = k ; j >= c ; j--)
            if (dp[j - c] + p[i] > dp[j])
                dp[j] = dp[j - c] + p[i];
    }
    maxim = 0;
    for (i = 0 ; i <= k ; i++)
        if (dp[i] > maxim)
            maxim = dp[i];
    fout << maxim << endl;
    fin.close();
    fout.close();
    return 0;
}
