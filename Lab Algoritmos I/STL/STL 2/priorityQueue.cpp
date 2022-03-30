#include <iostream>
#include <queue>
#include <stack>

/*Structed use to remember with job was important*/
struct job
{
    int priority;
    bool myjob = false;
};


/*Function using for printing the queue. It was using during debugging, not necessary to the solution*/
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

    int nTestCases;

    std::cin >> nTestCases;

    while (nTestCases--)    //run through all the test cases
    {
        int n, m;

        std::queue<job> jobQueue;   //queue for simulating the procedure

        std::priority_queue<int> pq;    //queue for checking the highest active priority


        std::cin >> n >> m;     //read number of elements and with one is important

        int i = 0;
        while (i < n)   //iterate through all the elements
        {
            job temp;

            std::cin >> temp.priority;

            if(i == m)  //verify if the job is important
            {
                temp.myjob = true;
            }

            jobQueue.push(temp);
            pq.push(temp.priority);

            i++;
        }

        i = 0; //reset i

        /*This loop will run until the first job of the jobQueue is the important one and its priority is 
        the highest active priority*/
        while (!jobQueue.front().myjob || jobQueue.front().priority != pq.top()) 
        {
            job j = jobQueue.front();

            if(j.priority == pq.top())  //active job has the highest priority -> pop from both queues
            {
                jobQueue.pop();
                pq.pop();
                i++;
            }
            else    //active job does not have the highest priority -> put it in the end of the queue
            {
                jobQueue.pop();
                jobQueue.push(j);
            }
        }
        
        i++;    //accounts for the pop of the important job

        std::cout << i << "\n"; //print the number of jobs completed 
        
    }
    
    return 0;
}