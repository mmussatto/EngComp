#include <iostream>
#include <vector>
#include <algorithm>

int main ()
{
    //Read number of days
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(3));

    //Read matrix
    for (int i = 0; i < n; i++)
    {
        std::cin >> matrix[i][0] >> matrix[i][1] >>matrix[i][2];
    }

    std::vector<std::vector<int>> dp(n, std::vector<int>(3));

    dp[0] = matrix[0];

    //Iterate through matrix
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = matrix[i][0] + std::max(dp[i-1][1], dp[i-1][2]); 
        dp[i][1] = matrix[i][1] + std::max(dp[i-1][0], dp[i-1][2]);        
        dp[i][2] = matrix[i][2] + std::max(dp[i-1][0], dp[i-1][1]);        
    }
    
    //Get max happines
    std::cout << std::max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
    

    return 0;
}