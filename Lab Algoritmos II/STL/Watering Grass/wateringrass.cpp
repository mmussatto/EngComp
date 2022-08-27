#include <bits/stdc++.h>

int wateringGrass(int n, int l, int w)
{
    std::vector<std::pair<double, double>> ranges;

    while (n--) //read sprinklers
    {
        double pos, rad;
        std::cin >> pos >> rad;

        if(rad < w/2)
            continue;

        double range = std::sqrt((rad*rad) - (w*w/4.0));
        ranges.push_back(std::make_pair(pos-range, pos+range));
    }

    std::sort(ranges.begin(), ranges.end());

    double curr = 0;
    double most_right = 0;
    int sprinklers = 0;
    int i = 0;

    while (most_right < l)
    {
        bool flag = false;

        for(; i < (int) ranges.size(); i++)
        {
            if(ranges[i].first > curr)
                break;

            if(ranges[i].second >= most_right)
            {
                most_right = ranges[i].second;
                flag = true;
            }            
        }

        if(!flag)
            break;

        curr = most_right;
        sprinklers++;
    }
    

    if(most_right < l)
        return  -1;
    else
        return sprinklers;
    
}

int main ()
{
    int n, l, w;

    while (std::cin >> n >> l >> w)
    {
        int res = wateringGrass(n, l, w);
        std::cout << res << "\n";
    }
    
    return 0;
}