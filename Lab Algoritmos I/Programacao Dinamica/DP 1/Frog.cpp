#include <bits/stdc++.h>

int main ()
{
    int n;
    std::cin >> n;

    std::vector<int> v_height;

    while (n--)
    {
        int temp;
        std::cin >> temp;
        v_height.push_back(temp);   
    }

    n = v_height.size();

    int totalCost = 0;

    int i = n - 1;

    while (i > 0)
    {
        if (i == 1)
        {
            totalCost += std::abs(v_height[i]-v_height[i-1]);
            break;
        }
        
        int cost1 = std::abs(v_height[i]-v_height[i-1]);
        int cost2 = std::abs(v_height[i]-v_height[i-2]);

        if (cost1 < cost2)
        {
            i = i -1;
            totalCost += cost1;
        }
        else
        {
            i = i- 2;
            totalCost += cost2;
        }
    }
    
    
    std::cout << totalCost;


    return 0;
}