#include <bits/stdc++.h>

int main ()
{
    int n_numbers, number, sum;
    int cost = 0;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq; //min-heap

    std::cin >> n_numbers;  //read quantity of numbers

    while (n_numbers != 0)
    {
        while (n_numbers--) //push all numbers to min-heap
        {
            std::cin >> number;
            pq.push(number);
        }

        while (true)
        {
            int n1 = pq.top();  //get smallest number
            pq.pop();

            int n2 = pq.top();  //get second smallest number
            pq.pop();

            sum = n1 + n2;  

            cost += sum;    //update cost of sum

            if (pq.empty()) //
            {
                break;
            }
            else    //min-hep not empty
            {
                pq.push(sum);   //push sum to heap
            }

        }
        
        //Print cost
        std::cout << cost << "\n";

        //Reset cost
        cost = 0;

        //Read next quantity of numbers
        std::cin >> n_numbers;
        
    }
    





    return 0;
}