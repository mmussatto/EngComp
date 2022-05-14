#include <bits/stdc++.h>


bool test(std::vector<int> a, int s)
{
    return true;
}

int main ()
{
    //read number of test cases
    int testCases;
    std::cin >> testCases;

    while (testCases--)
    {
        //read size of array an number of prettiness tests
        int n, q;
        std::cin >> n >> q;

        std::vector<int> a;

        //read array
        int i = n;
        while (i--)
        {
            int temp;
            std::cin >> temp;
            a.push_back(temp);
        }

        std::sort(a.begin(), a.end());

        while (q--)
        {
            int s;
            std::cin >> s;

            std::cout << test(a, s) ? "Yes" : "No";
        }
        
            
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}