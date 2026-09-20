#include <bits/stdc++.h>
using namespace std;

struct Stock {
    int act, min, max;
};

const int INF = 1e7;

int main()
{
    ifstream fin("stocks.in");
    ofstream fout("stocks.out");
    int n, b, l;
    fin >> n >> b >> l;
    vector<Stock> stocks(n);
    int i, j;
    for (i = 0; i < n; i++)
        fin >> stocks[i].act >> stocks[i].min >> stocks[i].max;
    int dp[501][101];
    for (i = 0; i <= b; i++)
        for (j = 0; j <= l; j++)
            dp[i][j] = -INF;
    dp[0][0] = 0;
    int k;
    int aux[501][101];
    for (k = 0 ; k < n ; k++)
    {
        int c = stocks[k].max - stocks[k].act;
        int p = stocks[k].act - stocks[k].min;
        for (i = 0 ; i <= b ; i++)
            for (j = 0 ; j <= l ; j++)
                aux[i][j] = dp[i][j];
        for (i = 0 ; i <= b ; i++)
            for (j = 0 ; j <= l ; j++)
                if (dp[i][j] >= 0)
                    if (i + stocks[k].act <= b && j + p <= l)
                        if (dp[i][j] + c > dp[i + stocks[k].act][j + p])
                            aux[i + stocks[k].act][j + p] = dp[i][j] + c;
        for (i = 0 ; i <= b ; i++)
            for (j = 0 ; j <= l ; j++)
                dp[i][j] = aux[i][j];
    }
    int maxim = 0;
    for (i = 0 ; i <= b ; i++)
        for (j = 0 ; j <= l ; j++)
            if (dp[i][j] > maxim)
                maxim = dp[i][j];
    fout << maxim << endl;
    fin.close();
    fout.close();
    return 0;
}
