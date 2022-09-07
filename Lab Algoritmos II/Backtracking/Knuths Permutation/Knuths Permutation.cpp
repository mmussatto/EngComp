#include <bits/stdc++.h>

using namespace std;

void dfs(string& original, int cur_length, string cur)
{
    if(cur.length() == original.length()) 
    {
        cout << cur << endl;
        return;
    }

    for(size_t i=0; i <= cur.length(); i++) 
        dfs(original, cur_length+1, cur.substr(0, i)+original[cur_length]+cur.substr(i));
}

int main ()
{
    string s;
    bool temp = false;
    
    while (cin >> s)
    {
        if(temp)
            cout << endl;

        temp = true;
        dfs(s, 0, "");    
    }

    return 0;
}