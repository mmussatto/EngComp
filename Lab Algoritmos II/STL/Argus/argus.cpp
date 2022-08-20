#include <bits/stdc++.h>

class querie {
    public:
        int id;
        int period;
        int time;

        querie(int id, int period, int time);
};

querie::querie(int id, int period, int time)
{
    this->id = id;
    this->period = period;
    this->time = time;
}

bool operator<(const querie& q1, const querie& q2)
{
    if(q1.time == q2.time)
        return q1.id > q2.id;
    else
        return q1.time > q2.time;
}

int main ()
{
    std::string str;
    int k;

    std::priority_queue<querie> pq;

    std::cin >> str;
    while (str != "#")
    {
        int id, period;
        std::cin >> id >> period;
        querie q(id, period, period);
        pq.push(q);
        std::cin >> str;
    }

    std::cin >> k;

    while (k--)
    {
        querie q = pq.top();
        pq.pop();
        std::cout << q.id << "\n";
        q.time = q.time + q.period;
        pq.push(q);
    }
    
    return 0;
}