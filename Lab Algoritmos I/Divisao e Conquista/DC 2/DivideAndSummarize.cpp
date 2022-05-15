#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

/*Sum of all the elements inside an array*/
int arraySum(std::vector<int> a)
{
    int sum = 0;

    for(auto i : a)
        sum += i;

    return sum;
}

/*Calculate all possible sums of an array. This is a recursive function 
that gets all the sums of the subarrays and store them inside a unordered_set*/
void possibleSums (std::vector<int> a, std::unordered_set<int> &set)
{
    if(a.size() == 1)   //array only has one element
    {
        set.insert(a[0]);
        return;    
    }

    //insert the sum of the curent array to the set
    set.insert(arraySum(a));


    int max = a.back();
    int min = a.front();
    int mid = (max + min)/2;

    //subarrays
    std::vector<int> left;
    std::vector<int> right;

    //divide array into subarrays left and right
    size_t i;
    for (i = 0; i < a.size() && a[i] <= mid; i++)
    {
        left.push_back(a[i]);
    }
    for (; i < a.size(); i++)
    {
        right.push_back(a[i]);
    }

    //if one of the subarrays is empty, terminate recursion (all elements of the array are the same)
    if(right.empty() || left.empty())
        return;
    
    //recursive calls
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

        //sort array
        std::sort(a.begin(), a.end());

        //calculate all possible sums of subarrays
        possibleSums(a, set);

        //prettiness tests 
        while (q--)
        {
            //read sum
            int s;
            std::cin >> s;

            //if sum is inside of set, print "Yes", if not, print "No"
            set.count(s) != 0 ? std::cout <<  "Yes" : std::cout <<  "No";
            std::cout << "\n";
          
        }
    }
    return 0;
}