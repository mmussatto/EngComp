#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>


int arraySum(std::vector<int> a)
{
    int sum = 0;

    for(auto i : a)
        sum += i;

    return sum;
}

void possibleSums (std::vector<int> a, std::unordered_set<int> &set)
{
    if(a.size() == 1)
    {
        set.insert(a[0]);
        return;    
    }

    set.insert(arraySum(a));

    int max = a.back();
    int min = a.front();

    int mid = (max + min)/2;


    std::vector<int> left;
    std::vector<int> right;

    size_t i;
    for (i = 0; i < a.size() && a[i] <= mid; i++)
    {
        left.push_back(a[i]);
    }
    for (; i < a.size(); i++)
    {
        right.push_back(a[i]);
    }

    if(right.empty() || left.empty())
        return;
    

    possibleSums(left, set);
    possibleSums(right, set);

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
        std::unordered_set<int> set;

        //read array
        int i = n;
        while (i--)
        {
            int temp;
            std::cin >> temp;
            a.push_back(temp);
        }

        std::sort(a.begin(), a.end());

        possibleSums(a, set);

        while (q--)
        {
            int s;
            std::cin >> s;

            set.count(s) != 0 ? std::cout <<  "Yes" : std::cout <<  "No";
            std::cout << "\n";
          
        }
    }

    return 0;
}