#include <iostream>
#include <vector>
#include <math.h>

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

    int totalCost = 0;

    int i = v_height.size() - 1;

    //iterate through rocks starting at the end
    while (i > 0)
    {
        if (i == 1) //only one movement possible
        {
            totalCost += std::abs(v_height[i]-v_height[i-1]);
            break;
        }
        
        //calculate cost of jumping one or two rocks
        int cost1 = std::abs(v_height[i]-v_height[i-1]);
        int cost2 = std::abs(v_height[i]-v_height[i-2]);

        //choose the smaller cost
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
    
    //print total cost
    std::cout << totalCost;


    return 0;
}