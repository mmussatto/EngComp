#include <bits/stdc++.h>

int main ()
{
    int n_numbers, number;
    int sum = 0,  cost = 0;

    std::multiset<int , std::less<int>> mset;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    std::cin >> n_numbers;

    while (n_numbers != 0)
    {
        while (n_numbers--)
        {
            std::cin >> number;
            pq.push(number);
        }

        while (true)
        {
            int n1 = pq.top();
            pq.pop();

            int n2 = pq.top();
            pq.pop();

            sum = n1 + n2;

            cost += sum;

            if (pq.empty())
            {
                break;
            }
            else
            {
                pq.push(sum);
            }

        }
        

        std::cout << cost << "\n";

        sum = 0;
        cost = 0;
        mset.clear();

        std::cin >> n_numbers;
        
    }
    





    return 0;
}