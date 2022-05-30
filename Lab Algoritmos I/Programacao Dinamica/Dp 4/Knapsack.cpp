#include <vector>
#include <iostream>
#include <algorithm>

int main ()
{

    int n, W;
    std::cin >> n >> W;

    std::vector<std::vector<long long>> items(n+1, std::vector<long long>(2));

    //read matrix
    for (int i = 1; i <= n; i++)
    {
        std::cin >> items[i][0] >> items[i][1];
    }
    

    std::vector<std::vector<long long>> dp(n+1, std::vector<long long>(W+1));

    for (int i = 0; i <= n; i++)
    {
        long long wi = items[i][0];
        long long vi = items[i][1];

        for (int j = 0; j <= W; j++)
        {
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(j >= wi)
            {
                long long int last = dp[i-1][j];
                long long int now = vi + dp[i-1][j-wi];
                dp[i][j] = std::max(last, now);
            }
            else
                dp[i][j] = dp[i-1][j];
        }
        
    }

    std::cout << dp[n][W];
    

    return 0;
}