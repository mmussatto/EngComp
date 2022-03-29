#include <iostream>
#include <queue>


struct job
{
    int priority;
    bool myjob = false;
    bool operator<(const job& other)const
    {
        if(priority == other.priority)
            return true;

        return priority < other.priority;
    }
};

void printQueue (std::priority_queue<job> pq)
{
    while (!pq.empty())
    {
        std::cout << pq.top().priority << " " << pq.top().myjob << "\n";
        pq.pop();
    }
    
}


int main ()
{

    int nTestes, n, m;

    std::priority_queue<job> pq;

    std::cin >> nTestes;

    while (nTestes--)
    {
        std::cin >> n >> m;


        int i = 0;
        while (i < n)
        {
            job temp;

            std::cin >> temp.priority;

            if(i == m)
            {
                temp.myjob = true;
            }

            pq.push(temp);

            i++;
        }

        i = 0;
        while (!pq.top().myjob)
        {
            pq.pop();
            i++;
        }
        
        std::cout << i << "\n";

        //printQueue(pq);
        

    }
    





    return 0;
}