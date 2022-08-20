#include <bits/stdc++.h>

int main ()
{
    int nfrosh;
    std::cin >> nfrosh;

    while (nfrosh != 0) //test cases
    {
        int most_popular = 0;   //number of students in the most popular
        int students = 0;       //total students taking the most popular courses

        std::map<std::set<int>, int> map;

        for(int i = 0; i < nfrosh; i++) //for each frosh
        {
            std::set<int> set;
            for(int j = 0; j < 5; j++)  //read courses
            {
                int course;
                std::cin >> course;
                set.insert(course);
            }

            map[set]++;
            most_popular = std::max(most_popular, map[set]);
        }

        for(auto i : map)   //iterate through map
        {
            if(i.second == most_popular)
                students += i.second;
        }

        std::cout << students << "\n";

        std::cin >> nfrosh;
    }
    return 0;
}