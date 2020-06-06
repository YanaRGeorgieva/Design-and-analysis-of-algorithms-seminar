#include <bits/stdc++.h>
const int MAX = 1000001;
int N;
int dp[MAX];
int p[MAX];

void input();
void cleanDPandPrepare();
int cutRodExp(int);
int cutRodMemo(int);
int cutRodMemoAux(int);
int cutRodIter(const int&);

void input()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &p[i]);
    }
}

void cleanDPandPrepare()
{
    for (int i = 0; i < MAX; i++)
    {
        dp[i] = INT_MIN;
    }
    dp[0] = 0;
}

int cutRodExp(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    else
    {
        int tmp = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            tmp = std::max(tmp, p[i] + cutRodExp(n - i));
        }
        return tmp;
    }
}

int cutRodMemo(int n)
{
    cleanDPandPrepare();
    return cutRodMemoAux(n);
}

int cutRodMemoAux(int n)
{
    if (dp[n] != INT_MIN)
    {
        return dp[n];
    }
    else
    {
        int tmp;
        if (n <= 0)
        {
            tmp = 0;
        }
        else
        {
            tmp = INT_MIN;
            for (int i = 1; i <= n; i++)
            {
                tmp = std::max(tmp, p[i] + cutRodMemoAux(n - i));
            }
            return tmp;
        }
        dp[n] = tmp;
        return dp[n];
    }
}

int cutRodIter(const int& n)
{
    cleanDPandPrepare();

    for (int i = 1; i <= n; i++)
    {
        int tmp = INT_MIN;
        for (int j = 1; j <= i; j++)
        {
            tmp = std::max(tmp, p[j] + dp[(i - j)]);
        }
        dp[i] = tmp;
    }

    return dp[n];
}

int main()
{
    /*
    Example input:
    8
    1 5 8 9 10 17 17 20
    */
    input();
    printf("--------------------\n");
    printf("%d\n", cutRodExp(N));
    printf("%d\n", cutRodMemo(N));
    printf("%d\n", cutRodIter(N));
    return 0;
}