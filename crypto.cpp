#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    ifstream fin("crypto.in");
    ofstream fout("crypto.out");
    int n, l;
    string k, s;
    fin >> n >> l >> k >> s;
    set<char> distinct_chars;
    for (char c : s)
        distinct_chars.insert(c);
    int m = distinct_chars.size();
    int dp[100001][11];
    int i, j;
    for (i = 0 ; i <= n ; i++)
        for (j = 0 ; j <= l ; j++)
            dp[i][j] = 0;
    dp[0][0] = 1;
    for (i = 0 ; i < n ; i++)
        for (j = 0 ; j < l ; j++)
        {
            //nu extind prefixul din s
            if (k[i] == '?')
                dp[i + 1][j] = (dp[i + 1][j] + 1LL * dp[i][j] * m) % MOD;
            else
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
            //extind prefixul din s
            if (k[i] == '?' || k[i] == s[j])
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % MOD;
        }
    for (i = 0 ; i < n ; i++)
        if (k[i] == '?')
            dp[i + 1][l] = (dp[i + 1][l] + 1LL * dp[i][l] * m) % MOD;
        else
            dp[i + 1][l] = (dp[i + 1][l] + dp[i][l]) % MOD;
    fout << dp[n][l] << endl;
    fin.close();
    fout.close();
    return 0;
}
