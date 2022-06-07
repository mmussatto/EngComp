#include <iostream>
#include <vector>

void divisors(int n)
{
    std::vector<int> d;

    for (int i = 1; i*i <= n; i++)
    {   if (n % i == 0)
        {        
            d.push_back(i);
            std::cout << i << " ";
        }
    }
    if(n/d.back() == d.back())
        d.pop_back();

    for (int i = d.size() - 1; i >= 0; i--)
    {
        std::cout << n/d[i] << " ";
    }

}

int main ()
{
    int n;
    std::cin >> n;

    divisors(n);

    return 0;
}