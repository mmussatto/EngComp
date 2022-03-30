#include <iostream>
#include <queue>
#include <stack>


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

    int nTestes;

    std::cin >> nTestes;

    while (nTestes--)
    {

        int n, m;

        std::queue<job> jobQueue;
        std::priority_queue<int> pq;


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

            jobQueue.push(temp);
            pq.push(temp.priority);

            i++;
        }

        i = 0;
        while (!jobQueue.front().myjob || jobQueue.front().priority != pq.top())
        {
            job j = jobQueue.front();

            if(j.priority == pq.top())
            {
                jobQueue.pop();
                pq.pop();
                i++;
            }
            else
            {
                jobQueue.pop();
                jobQueue.push(j);
            }
        }
        
        i++;
        std::cout << i << "\n";

        //printQueue(pq);
        

    }
    

    return 0;
}