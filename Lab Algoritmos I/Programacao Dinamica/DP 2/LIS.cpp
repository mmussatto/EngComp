#include <iostream>
#include <vector>
#include <algorithm>

int main ()
{
    //read size of vector
    int size;
    std::cin >> size;

    std::vector<int> array;
    std::vector<int> vLIS(size, 1);
    
    //read vector
    while (size--)
    {
        int value;
        std::cin >> value;
        array.push_back(value);
    }

    //convert the size of the array from size_t to int. It helps with the for statments below
    int n = array.size();

    //iterate through the array starting at the end
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++) //iterate starting at position i, and going foward
        {
            if(array[i] < array[j]) //element to the left is bigger then element were looking
                vLIS[i] = std::max(vLIS[i], 1 + vLIS[j]);
        }

    }

    //get teh max element of vector vLIS
    int max = *max_element(vLIS.begin(), vLIS.end());

    //print max
    std::cout << max;
    
    return 0;    
}