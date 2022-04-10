#include <bits/stdc++.h>

int main ()
{

    int n_testCases, n_snowflakes, snowflakeID;
    int largestPackage = 0;

    std::vector<int> stream;    //stream of incoming snowflakes
    std::set<int> package;      //package containing unique snowflakes

    std::cin >> n_testCases;

    while (n_testCases--)
    {
        std::cin >> n_snowflakes;

        //Push all snowflakes into stream
        while (n_snowflakes--)  
        {
            std::cin >> snowflakeID;
            stream.push_back(snowflakeID);
        }

        //Nested Loops: O(n^2) solution. Not good but it works.
        for (auto it = stream.begin(); it != stream.end(); it++)
        {
            for(auto it2 = it; it2 != stream.end(); it2++)
            {
                if (package.count(*it2) != 0)   //if snowflake is already in the package, break
                {
                    break;
                }
                else
                {
                    package.insert(*it2);   //insert snowflake into package
                }   
            }
            
            if (largestPackage < (int)package.size())   //verify if current package size is bigger than the largest
            {
                largestPackage = package.size(); 
            }
            
            package.clear();    //clear package for other iterations
        }

        std::cout << largestPackage << "\n";  

        //reset largestPackage and stream of snowflakes
        largestPackage = 0;
        stream.clear();
    }

    return 0;
}