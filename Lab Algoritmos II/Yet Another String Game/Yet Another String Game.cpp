#include <bits/stdc++.h>

using namespace std;

int main ()
{
    size_t tests;
    cin >> tests;

    while (tests--)
    {
        string word;
        cin >> word;

        bool player = true; //true for Alice, false for Bob

        for (size_t i = 0; i < word.length(); i++)
        {
            if(player)
                word[i] == 'a' ? word[i] = 'b' : word[i] = 'a';
            else
                word[i] == 'z' ? word[i] = 'y' : word[i] = 'z';

            player = !player;
        }

        cout << word << endl;
            
    }
    
    return 0;
}