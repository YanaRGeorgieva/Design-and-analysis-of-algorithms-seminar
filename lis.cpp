#include <bits/stdc++.h>

const unsigned MAX = 1001;
int n, A[MAX], dp[MAX], dp2D[MAX][MAX], parent[MAX];

void input();
void prepareDP();
void printPath(const int&);
void lisBottomUp();
void lisTopDown();
int lisTopDownAux(int, int);

void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
}

void prepareDP()
{
    memset(dp, -1, MAX * sizeof(int));
    memset(parent, -1, MAX * sizeof(int));
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            dp2D[i][j] = -1;
        }
    }
}

void printPath(const int& i)
{
    if (i == -1)
    {
        return;
    }

    printPath(parent[i]);
    printf("%d ", A[i]);
}

void lisBottomUp()
{
    prepareDP();

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    int res = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }

        if (dp[i] > res)
        {
            res = dp[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        printPath(i);
        printf("\n");
    }
    printf("Longest increasing subsequence is with length %d.\n", res);
}

void lisTopDown()
{
    prepareDP();
    int res = lisTopDownAux(0, -1);
    printf("Longest increasing subsequence is with length %d.\n", res);
}

int lisTopDownAux(int previousIdx, int currentIdx)
{
    if (dp2D[previousIdx + 1][currentIdx] != -1)
    {
        return dp2D[previousIdx + 1][currentIdx];
    }
    else
    {
        int res = 0;
        if (currentIdx == n)
        {
            res = 0;
        }
        else
        {
            int include = 0;
            if (previousIdx < 0 || A[currentIdx] > A[previousIdx])
            {
                include = 1 + lisTopDownAux(currentIdx, currentIdx + 1);
            }

            int exclude = lisTopDownAux(previousIdx, currentIdx + 1);

            res = std::max(include, exclude);
        }
        dp2D[previousIdx + 1][currentIdx] = res;

        return res;
    }
}

/*
Example input:
8
5 2 8 6 3 6 9 7
*/
int main()
{
    input();
    lisBottomUp();
    lisTopDown();
    return 0;
}
