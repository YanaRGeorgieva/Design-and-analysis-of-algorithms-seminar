#include <bits/stdc++.h>
// Много ми хареса решението от този сайт
// https://www.geeksforgeeks.org/edit-distance-dp-5/ и 
// него ви прилагам като съм направила някои поправки.
const unsigned MAX = 1001;

int dp[MAX][MAX];

// Utility function to find the minimum of three numbers
int min(int x, int y, int z) { return std::min(std::min(x, y), z); }

int editDistTopDown(std::string str1, std::string str2, int m, int n)
{
    // If first string is empty, the only option is to
    // insert all characters of second string into first
    if (dp[m][n] != -1)
    {
        return dp[m][n];
    }
    else
    {
        int res = -1;
        if (m == 0)
        {
            res = n;
        }
        // If second string is empty, the only option is to
        // remove all characters of first string
        else if (n == 0)
        {
            res = m;
        }
        // If last characters of two strings are same, nothing
        // much to do. Ignore last characters and get count for
        // remaining strings.
        else if (str1[m - 1] == str2[n - 1])
        {
            res = editDistTopDown(str1, str2, m - 1, n - 1);
        }
        else
        {
            // If last characters are not same, consider all three
            // operations on last character of first string, recursively
            // compute minimum cost for all three operations and take
            // minimum of three values.
            res = 1 + min(editDistTopDown(str1, str2, m, n - 1),     // Insert
                          editDistTopDown(str1, str2, m - 1, n),     // Remove
                          editDistTopDown(str1, str2, m - 1, n - 1)  // Replace
                      );
        }
        dp[m][n] = res;
        return res;
    }
}

int editDistBottomUp(std::string str1, std::string str2, int m, int n)
{
    // Create a table to store results of subproblems
    int dp[m + 1][n + 1];

    // Fill d[][] in bottom up manner
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i == 0)
            {
                dp[i][j] = j;  // Min. operations = j
            }
            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j == 0)
            {
                dp[i][j] = i;  // Min. operations = i
            }
            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }

            // If the last character is different, consider all
            // possibilities and find the minimum
            else
            {
                dp[i][j] = 1 + min(dp[i][j - 1],       // Insert
                                   dp[i - 1][j],       // Remove
                                   dp[i - 1][j - 1]);  // Replace
            }
        }
    }

    return dp[m][n];
}

// Driver program
int main()
{
    std::string str1 = "hireoglypology";
    std::string str2 = "michaelangelo";

    printf("%d\n", editDistBottomUp(str1, str2, str1.length(), str2.length()));
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            dp[i][j] = -1;
        }
    }
    printf("%d\n", editDistTopDown(str1, str2, str1.length(), str2.length()));

    return 0;
}
