#include <bits/stdc++.h>

int main ()
{

    int n_testCases, n_snowflakes, snowflakeID;
    int largestPackage = 0;

    std::vector<int> stream;
    std::set<int> package;

    std::cin >> n_testCases;

    while (n_testCases--)
    {
        std::cin >> n_snowflakes;

        while (n_snowflakes--)  
        {
            std::cin >> snowflakeID;
            stream.push_back(snowflakeID);
        }

        for (auto it = stream.begin(); it != stream.end(); it++)
        {
            for(auto it2 = it; it2 != stream.end(); it2++)
            {
                if (package.count(*it2) != 0)
                {
                    break;
                }
                else
                {
                    package.insert(*it2);
                }   
            }
            
            if (largestPackage < (int)package.size())
            {
                largestPackage = package.size(); 
            }
            
            package.clear();
        }

        std::cout << largestPackage << "\n";

        largestPackage = 0;
        stream.clear();
    }

    return 0;
}