#include <iostream>
#include <vector>
#include <algorithm>

int main ()
{

    int size;
    std::cin >> size;

    std::vector<int> array;
    std::vector<int> vLIS(size, 1);
    
    while (size--)
    {
        int value;
        std::cin >> value;
        array.push_back(value);
    }


    int n = array.size();

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if(array[i] < array[j])
                vLIS[i] = std::max(vLIS[i], 1 + vLIS[j]);
        }

    }

    int max = *max_element(vLIS.begin(), vLIS.end());

    std::cout << max;
    

    return 0;    
}