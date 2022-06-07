#include <iostream>


bool is_it_prime(int n)
{
    if(n == 1)
        return false;

    for (long long i = 2; i < n/2; i++)
        if (n % i == 0)
            return false;

    return true;
}


int main ()
{
    long long n;
    std::cin >> n;

    is_it_prime(n) ? std::cout << "YES" : std::cout << "NO";

    return 0;
}