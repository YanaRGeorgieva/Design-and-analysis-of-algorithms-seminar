#include <bits/stdc++.h>
const int MAX = 1000001;
int N;
int dp[MAX];

void input();
void cleanDPandPrepare();
int fibExp(int);
int fibMemoRec(int);
int fibMemoRecAux(int);
int fibIterLinSpace(const int&);
int fibIterConstSpace(const int&);

void input() { scanf("%d", &N); }

void cleanDPandPrepare()
{
    for (int i = 0; i < MAX; i++)
    {
        dp[i] = -1;
    }
    dp[1] = dp[2] = 1;
}

int fibExp(int n)
{
    if (n <= 0)
    {
        fprintf(stderr, "Invalid Fibonacci index!\n");
        return -1;
    }
    else if (n <= 2)
    {
        return 1;
    }
    else
    {
        return fibExp(n - 1) + fibExp(n - 2);
    }
}

int fibMemoRec(int n)
{
    cleanDPandPrepare();
    return fibMemoRecAux(n);
}

int fibMemoRecAux(int n)
{
    if (dp[n] != -1)
    {
        return dp[n];
    }
    else
    {
        int tmp;
        if (n <= 0)
        {
            fprintf(stderr, "Invalid Fibonacci index!\n");
            exit(-1);
        }
        else if (n <= 2)
        {
            tmp = 1;
        }
        else
        {
            tmp = fibMemoRecAux(n - 1) + fibMemoRecAux(n - 2);
        }
        dp[n] = tmp;
        return dp[n];
    }
}

int fibIterLinSpace(const int& n)
{
    if (n <= 0)
    {
        fprintf(stderr, "Invalid Fibonacci index!\n");
        return -1;
    }

    cleanDPandPrepare();

    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int fibIterConstSpace(const int& n)
{
    if (n <= 0)
    {
        fprintf(stderr, "Invalid Fibonacci index!\n");
        return -1;
    }
    int prev, prevPrev;
    prev = prevPrev = 1;
    for (int i = 3; i <= n; i++)
    {
        int curr = prev + prevPrev;
        prevPrev = prev;
        prev = curr;
    }
    return prev;
}

int main()
{
    input();
    printf("--------------------\n");
    printf("%d\n", fibExp(N));
    printf("%d\n", fibMemoRec(N));
    printf("%d\n", fibIterLinSpace(N));
    printf("%d\n", fibIterConstSpace(N));
    return 0;
}