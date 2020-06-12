#include <bits/stdc++.h>

const unsigned MAX = 1001;

int dp[MAX][MAX], n, S, coins[MAX];

int subsetSumTopDownAux(int, int);
void subsetSumTopDown();
void subsetSumBottomUp();
void input();
void clean();

void subsetSumTopDown()
{
    clean();
    subsetSumTopDownAux(n, S);
    printf("Can the sum S be obtained? %d\n", dp[n][S]);
}

int subsetSumTopDownAux(int idx, int S)
{
    if (dp[idx][S] != -1)
    {
        return dp[idx][S];
    }
    else
    {
        int res = -1;
        if (S == 0)
        {
            res = 1;
        }
        else if (S < 0)
        {
            res = 0;
        }
        else if (idx <= 0 && S >= 1)
        {
            res = 0;
        }
        else
        {
            int include, exclude;
            include = exclude = 0;
            if (idx > 0)
            {
                exclude = subsetSumTopDownAux(idx - 1, S);
            }
            if (idx > 0 && S >= coins[idx - 1])
            {
                include = subsetSumTopDownAux(idx - 1, S - coins[idx - 1]);
            }
            res = std::max(exclude, include);
            dp[idx][S] = res;
        }
        return res;
    }
}

void subsetSumBottomUp()
{
    clean();

    int max = std::max(n, S);
    for (int i = 1; i <= max; i++)
    {
        dp[i][0] = 1;
        dp[0][i] = 0;
    }
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= S; j++)
        {
            int include = dp[i - 1][j];
            int exclude = (coins[i - 1] <= j) ? dp[i - 1][j - coins[i - 1]] : 0;
            dp[i][j] = std::max(include, exclude);
        }
    }

    printf("Can the sum S be obtained? %d\n", dp[n][S]);
}

void input()
{
    scanf("%d %d", &n, &S);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }
}

void clean()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            dp[i][j] = -1;
        }
    }
}

/*
Example input:
8 45
10 50 21 75 3 7 10 18
*/
int main()
{
    input();
    subsetSumBottomUp();
    subsetSumTopDown();
}
