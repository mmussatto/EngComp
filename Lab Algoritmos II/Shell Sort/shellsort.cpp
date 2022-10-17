#include <bits/stdc++.h>

bool compare (std::pair<std::string, int> p1, std::pair<std::string, int> p2)
{
    return p1.second > p2.second;
}

int main ()
{
    int k;
    std::cin >> k;  //test cases

    while (k--)
    {
        int n;
        std::cin >> n;
        std::cin.ignore();  //ignore "\n"

        std::vector<std::string> original;
        std::unordered_map<std::string, int> desired;
        std::string name;

        for(int i = 0; i < n; i++)  //read order given
        {
            std::getline(std::cin, name);
            original.push_back(name);
        }

        for(int i = 0; i < n; i++)  //read desired order
        {
            std::getline(std::cin, name);
            desired[name] = i;
        }

        std::vector<std::pair<std::string, int>> order;

        //push to order the elements that need to be moved
        for(int i = n-1, next = n-1; i >= 0; i--)   
        {
            if(desired[original[i]] != next)
                order.push_back(std::make_pair(original[i], desired[original[i]]));
            else
                next--;
        }

        std::sort(order.begin(), order.end(), compare);

        for(auto i : order)
            std::cout << i.first << "\n";

        std::cout << "\n";
    }
    
    return 0; 
}