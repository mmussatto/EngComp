#include <vector>
#include <iostream>
#include <algorithm>

int main ()
{

    int n, W;
    std::cin >> n >> W;

    //wi, vi
    std::vector<std::vector<long long>> items(n+1, std::vector<long long>(2));

    //Read items weight and value
    for (int i = 1; i <= n; i++)
    {
        std::cin >> items[i][0] >> items[i][1];
    }
    
    //[item][max_weight]
    std::vector<std::vector<long long>> dp(n+1, std::vector<long long>(W+1));

    //Iterate through all the items
    for (int i = 0; i <= n; i++)
    {
        //current item
        long long wi = items[i][0]; //weight
        long long vi = items[i][1]; //value

        //iterate through all the max_weights from 0 to W
        for (int j = 0; j <= W; j++)
        {
            if(i == 0 || j == 0)    //no weight or no item selected
                dp[i][j] = 0;
            else if(j >= wi)    //verify valid item
            {
                long long int last = dp[i-1][j];        //current solution until now
                long long int now = vi + dp[i-1][j-wi]; //new item plus last best solution
                dp[i][j] = std::max(last, now);
            }
            else    //invalid item
                dp[i][j] = dp[i-1][j];
        }
        
    }

    //bottom-left corner of the matrix is the best value
    std::cout << dp[n][W];
    
    return 0;
}