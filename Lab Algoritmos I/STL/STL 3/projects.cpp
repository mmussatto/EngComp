#include <bits/stdc++.h>


/*Function to order the vector containing the project name and number of students*/
bool cmp(std::pair<std::string, int>& a, 
         std::pair<std::string, int>& b)
{
    if (a.second == b.second) //same number of students
    {
        return a.first < b.first; //alfabetical order
    }
    return a.second > b.second; //highest
}

void print_projects(std::map<std::string, int> &map)
{
    std::vector<std::pair<std::string, int>> V;

    for (auto& it : map) {
        V.push_back(it);
    }

    std::sort(V.begin(), V.end(), cmp);
    
    for (auto& it : V) {
        std::cout << it.first << ' ' << it.second << "\n";
    }
}


int main ()
{
    std::map<std::string, int> map_projects;
    std::map<std::string, std::string> map_students;

    std::string s;

    //std::cin >> s; 
    std::getline(std::cin, s);
    

    while (s != "0")
    {
        std::string project_name;

        while (s != "1")
        {
            if(isupper(s[0])) //project
            {
                project_name = s;
                map_projects[s] = 0;
            }
            else //student id
            {
                
                if (map_students.find(s) != map_students.end()) //student already signed
                {
                    if(map_students[s] != project_name) //student signed to more than one project
                    {
                        map_students[s] = "INVALID";
                    }
                }
                else
                {   
                    map_students[s] = project_name;
                }
            }
            //std::cin >> s; 
            std::getline(std::cin, s);
        }

        for (auto it = map_students.begin(); it != map_students.end(); it++)
        {
            if (it->second != "INVALID")
            {
                map_projects[it->second]++;
            }
        }

        print_projects(map_projects);
        map_students.clear();
        map_projects.clear();
        

        //std::cin >> s; 
        std::getline(std::cin, s);
        
    }
    
}