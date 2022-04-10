#include <bits/stdc++.h>


/*Function to order the vector containing the project name and number of students*/
bool cmp(std::pair<std::string, int>& a, 
         std::pair<std::string, int>& b)
{
    if (a.second == b.second) //same number of students
    {
        return a.first < b.first; //alfabetical order
    }
    return a.second > b.second; //highest number of students first
}

/*Funcion to order and print the project names and number of students*/
void print_projects(std::map<std::string, int> &map)
{
    std::vector<std::pair<std::string, int>> V; //vector used to sort the projects

    //Pushing all projects to vector
    for (auto& it : map) {
        V.push_back(it);
    }

    //Sorting
    std::sort(V.begin(), V.end(), cmp);
    
    //Printing project names and student count
    for (auto& it : V) {
        std::cout << it.first << ' ' << it.second << "\n";
    }
}


int main ()
{
    std::map<std::string, int> map_projects;            //stores project name and number of students
    std::map<std::string, std::string> map_students;    //stores name of the sutdent and with project he is assinged to 

    std::string s; 

    std::getline(std::cin, s);  //read cin
    

    while (s != "0")    //all tests cases have ended
    {
        std::string project_name;

        while (s != "1")    //current test case has endend
        {
            if(isupper(s[0])) //project
            {
                project_name = s;       //stores the name of the project
                map_projects[s] = 0;    //add to map
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
                    map_students[s] = project_name; //store student in map
                }
            }

            std::getline(std::cin, s);
        }

        //Count number of students in each project
        for (auto it : map_students)
        {
            if (it.second != "INVALID") //count only VALID students
            {
                map_projects[it.second]++;
            }
        }

        print_projects(map_projects);

        //Clears the maps for other test cases
        map_students.clear();
        map_projects.clear();
        
        std::getline(std::cin, s);
    }

    return 0;
    
}