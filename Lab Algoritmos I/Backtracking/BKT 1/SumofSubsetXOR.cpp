#include <iostream>
#include <vector>


void Sum_XOR_Subsets(std::vector<int> &nums, std::vector<int> &subset, int index, int &sum)
{
    if(!subset.empty())
    {
        int XOR = subset[0];
        for (auto i = 1; i < (int)subset.size(); i++)
            XOR = XOR ^ subset[i];
        sum += XOR;
    }
    

    for(auto i = index; i < (int)nums.size(); i++)
    {
        subset.push_back(nums[i]);

        Sum_XOR_Subsets(nums, subset, i + 1, sum);

        subset.pop_back();
    }

    return;
}


int main()
{
    int n; 
    std::cin >> n; //read number of elements

    std::vector<int> nums;

    while(n--) //read elements
    {
        int temp;
        std::cin >> temp;

        nums.push_back(temp);
    }
    
    int index = 0;
    int sum = 0;
    std::vector<int> subset;
    Sum_XOR_Subsets(nums, subset, index, sum);
    
    std::cout << sum;
    
    
    return 0;
}