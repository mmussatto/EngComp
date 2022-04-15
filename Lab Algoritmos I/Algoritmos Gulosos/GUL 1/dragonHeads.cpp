#include<iostream>
#include<queue>

/*Function for clearing the pq between test cases*/
void clear_pq (std::priority_queue<int, std::vector<int>, std::greater<int>> *pq)
{
    while (!pq->empty())
    {
        pq->pop();
    }
}


int main ()
{
    int n_heads, n_knights;
    int cost = 0;

    std::priority_queue<int, std::vector<int>, std::greater<int>> heads;
    std::priority_queue<int, std::vector<int>, std::greater<int>> knights;

    std::cin >> n_heads >> n_knights;

    while (n_heads != 0 && n_knights != 0)
    {
        //read heads
        while (n_heads--)
        {
            int temp;
            std::cin >> temp;
            heads.push(temp);
        }

        //read knights
        while (n_knights--)
        {
            int temp;
            std::cin >> temp;
            knights.push(temp);
        }

        //greedy algorithm        
        while (true)
        {
            int top_head = heads.top();
            int top_knight = knights.top();

            if(top_knight >= top_head)
            {
              cost += top_knight; //update cost
              heads.pop();
              knights.pop();
            }
            else    //knight is smaller than head
            {
                knights.pop();
            }

            if(heads.empty()) //all heads were chopped off
            {
                std::cout << cost << "\n";
                break;
            }
            else if(knights.empty())    //no more knights but there are heads remaining
            {
                std::cout << "Loowater is doomed!\n";
                break;
            }
        }

        clear_pq(&heads);
        clear_pq(&knights);

        std::cin >> n_heads >> n_knights;
        cost = 0;
    }
    return 0;
}