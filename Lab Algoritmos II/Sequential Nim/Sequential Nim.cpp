#include <bits/stdc++.h>

using namespace std;

int main ()
{
    size_t tests;
    cin >> tests;

    while (tests--)
    {
        size_t piles;
        cin >> piles;

        bool player = true; //true - First, false - Second
        bool finished = false; //Winner alerady decided -- still needs to read the rest of the piles

        while (piles--)
        {
            int size;
            cin >> size;

            if(size != 1) finished = true;

            if(piles != 0 && !finished)
                player = !player;
        }

        //Winner
        player ? cout << "First" : cout << "Second";
        
        cout << endl;
        
    }
    
    return 0;
}