#include <iostream>
#include <vector>
#include <math.h>
#include <climits>

int main ()
{
    //read number of rocks
    int n;
    std::cin >> n;

    std::vector<int> v_height;

    //read height of each rock
    while (n--)
    {
        int temp;
        std::cin >> temp;
        v_height.push_back(temp);   
    }

    int i = v_height.size();

    std::vector<int> dp (i, INT_MAX);

    dp[i-1] = 0; //final rock
    dp[i-2] = std::abs(v_height[i-1]-v_height[i-2]); //second last rock

    i = i - 3;

    while(i >= 0)
    {
        int cost1 = std::abs(v_height[i]-v_height[i+1]) + dp[i+1];
        int cost2 = std::abs(v_height[i]-v_height[i+2]) + dp[i+2];

        dp[i] = std::min(cost1, cost2);

        i--;
    }

    //print total cost
    std::cout << dp[0];

    return 0;
}