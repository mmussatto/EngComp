#include <iostream>

int binarySearch(int n)
{
    long int left = 0;
    long int right = n;
    long int mid;

    while (left <= right)
    {
        mid = left + (right - left)/2;

        long int sum = (1 + mid)*mid/2;  //sum of all coins used until the mid_th row

        if(sum == n)    //sum of mid row is exactly the number of coins (n)
            return mid;

        if(sum > n) //sum is bigger than number of coins available, get smaller rows
        {
            right = mid - 1;
        }
        else    //sum is smaller than number of coins available, get greater rows
        {
            left = mid + 1;
        }
    }

    //if gets here, there is no complete row with the exact number of coins
    //right variable has the last complete row 
    return right;   
}

int main ()
{
    int n;

    std::cin >> n;

    std::cout << binarySearch(n);
    
    return 0;
}