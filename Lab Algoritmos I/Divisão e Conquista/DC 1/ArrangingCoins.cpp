#include <iostream>

int binarySearch(int n)
{
    long int left = 0;
    long int right = n;
    long int mid;

    while (left <= right)
    {
        mid = left + (right - left)/2;

        long int sum = (1 + mid)*mid/2;

        if(sum == n)
            return mid;

        if(sum > n)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return right;
}

int main ()
{
    int n;

    std::cin >> n;

    std::cout << binarySearch(n);
    
    return 0;
}