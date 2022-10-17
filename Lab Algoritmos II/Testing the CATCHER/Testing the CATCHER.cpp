#include <bits/stdc++.h>

using namespace std;

int solve (vector<int> &missiles)
{
    vector<int> dp(missiles.size());

    dp[0] = 1;  //first missile

     for (size_t i = 1; i < missiles.size(); i++)
     {  
        dp[i] = 1;  //current missile

        for (size_t j = 0; j < i; j++)  //iterate through previous missiles
            if (missiles[i] < missiles[j] && dp[i] < dp[j] + 1)
                dp[i] = dp[j] + 1; 
    }
     
    return *max_element(dp.begin(), dp.end());

}


int main ()
{
    int height, counter = 1;
    

    while (cin >> height)
    {
        if(height == -1)
            break;
        
        vector<int> missiles;
        missiles.push_back(height);

        while (cin >> height) //read input
        {
            if(height == -1)
                break;

            missiles.push_back(height);
        }

        if(counter != 1) cout << endl;
        //comentario para o vdjuge deixar eu mandar o codigo, odeio presentation error
        cout << "Test #" << counter++ << ":\n  maximum possible interceptions: " << solve(missiles) << endl;
    }
    
    return 0;
}