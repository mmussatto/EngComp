#include <bits/stdc++.h>

using namespace std;

int calculate_song(vector<pair<size_t, size_t>>& playlist, size_t& moment, size_t& minutes, size_t& song)
{
    if(minutes >= moment)
        return song;

    for(size_t i = song; i < playlist.size(); i++)
    {
        minutes += playlist[i].second * playlist[i].first;
        playlist[i].first = 0;

        if(minutes >= moment)
            return i;
    }

    return -1;
}

int main ()
{
    size_t n, m;
    cin >> n >> m;
    vector<pair<size_t, size_t>> playlist;

    while (n--)
    {
        size_t c, t;
        cin >> c >> t;
        playlist.push_back(make_pair(c, t));
    }

    size_t minutes = 0, song = 0;

    while (m--)
    {
        size_t moment;
        cin >> moment;
        song = calculate_song(playlist, moment, minutes, song);
        cout << song + 1 << endl;
    }
    
    return 0;
}