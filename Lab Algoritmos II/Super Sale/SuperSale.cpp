#include <bits/stdc++.h>

using namespace std;

void fill_knapsack_table(vector<vector<int>> &knapsack_table, vector<pair<int, int>> &objects, int capacity)
{
    for(auto i = 1; i < (int) knapsack_table.size(); i++)
    {
        for (auto j = 1; j <= capacity; j++)
        {
            if(i == 0 || j == 0)
                knapsack_table[i][j] = 0;
            else if(objects[i-1].second > j)
                knapsack_table[i][j] = knapsack_table[i-1][j];
            else
                knapsack_table[i][j] = max(knapsack_table[i-1][j], objects[i-1].first + knapsack_table[i-1][j-objects[i-1].second]);
        }
    }
}

int main ()
{
    int T;
    cin >> T;

    while (T--) //run test cases
    {
        vector<pair<int, int>> objects;
        vector<int> group;

        int N; //number of objects
        cin >> N;
        
        for(auto i = 0; i < N; i++)
        {
            int P, W;
            cin >> P >> W;
            objects.push_back(make_pair(P, W));
        }

        int G; //number of people in the group
        cin >> G;

        for (auto i = 0; i < G; i++)
        {
            int MW;
            cin >> MW;
            group.push_back(MW);
        }

        // Get max weight
        int max_weight = *max_element(group.begin(), group.end());

        vector<vector<int>> knapsack_table(N+1, vector<int>(max_weight+1));

        fill_knapsack_table(knapsack_table, objects, max_weight);
        
        int result  = 0;

        for(auto g : group)
        {
            result += knapsack_table[N][g];
        }

        cout << result << endl;
    }
    
    return 0;
}