#include <iostream>
#include <vector>


void Sum_XOR_Subsets(std::vector<int> &nums, std::vector<int> &subset, int index, int &sum)
{
    //calculate XOR for the current subset
    if(!subset.empty())
    {
        int XOR = subset[0];    //starts with first element

        for (auto i = 1; i < (int)subset.size(); i++)   //iterate through the vector
            XOR = XOR ^ subset[i];
        
        sum += XOR; //update sum 
    }
    
    //backtraking of subsets
    for(auto i = index; i < (int)nums.size(); i++)
    {
        subset.push_back(nums[i]);  //push next element into subset

        Sum_XOR_Subsets(nums, subset, i + 1, sum);  //recursion

        subset.pop_back();  //remove element from subset
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
    
    std::cout << sum;   //print sum
    
    return 0;
}