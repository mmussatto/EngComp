#include <bits/stdc++.h>


void subsetUtil(std::vector<int> &A, std::vector<std::vector<int>> &res, std::vector<int> &subset, int index)
{
    res.push_back(subset);

    for(int i = index; i < A.size(); i++)
    {
        subset.push_back(A[i]);

        subsetUtil(A, res, subset, i + 1);

        subset.pop_back();
    }

    return;
}

std::vector<std::vector<int>> subset(std::vector<int> A)
{
    std::vector<int> subset;
    std::vector<std::vector<int>> res;

    int index = 0;
    subsetUtil(A, res, subset, index);

    return res;
}


int main ()
{
    std::vector<int> A = {1 , 2, 3};

    
    std::vector<std::vector<int>> res = subset(A);


    return 0;
}