#include <bits/stdc++.h>

using namespace std;

vector<double> probabilities = {
    12.53, 1.42, 4.68, 5.86, 13.68, 0.69, 1.01, 0.70, 6.25, 0.44, 0.00, 4.97, 3.15, 
    6.71, 8.68, 2.51, 0.88, 6.87, 7.98, 4.63, 3.93, 0.90, 0.02, 0.22, 0.90, 0.52};

vector<char> odd = {'a', 'e', 'i', 'o', 'u'};
vector<char> even = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

float total = 0, cnt = 0;     //used for calculating the average SBC


float SBC (const string& w)
{
    float sum = 0;

    for (size_t i = 0; i < w.length(); i++)
        sum += (i+1) * probabilities[w[i] - 'a'];      

    return sum;
}


void dfs(string& cur, int length, vector<int>& ccount)
{
    int cur_length = cur.length();

    if(cur_length == length)    //word with same length as original, calulate SBC
    {
        total += SBC(cur);
        cnt++;
        return;
    }

    //Iterate through all letters in the correct pattern
    for(auto& c : (cur_length%2 ? odd : even))
    {
        if(ccount[c - 'a'] < 2) //verifies if character has appeared at most two times
        {
            cur += c;           //add char to string
            ccount[c-'a']++;    //increase counter for that char

            dfs(cur, length, ccount);   //continue to generate the word

            cur.pop_back();     //remove char from string
            ccount[c-'a']--;    //decrease counter
        }
    }
}


int main ()
{
    //Read number of words
    int N;
    cin >> N;

    //Map to store the average of words already tested
    unordered_map<string, double> cache;

    while (N--)
    {   
        //Read word
        string w;
        cin >> w;

        int length = w.length();
        float avg;

        //Create a key to store the average of words of same length and starting with w[0]
        string key = to_string(length) + ":" + w[0];

        //Check if the average has already been calculated
        if(cache.count(key))
            avg = cache[key];   
        else
        {
            //initialize string to generate all possibilities with the same pattern
            string cur(1, w[0]);    

            vector<int> ccount(26); //count how many times a char appears
            ccount[w[0]-'a']++;
            
            
            total = cnt = 0;    //Reset variables
            dfs(cur, length, ccount);   //Generate all possible words with the same pattern and their SBC

            avg = total/cnt;    //calculate avg
            cache[key] = avg;   //store avg in cache
        }


        if(SBC(w) < avg)
            cout << "below\n";
        else
            cout << "above or equal\n";
    }

    return 0;
}