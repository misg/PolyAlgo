#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void divide(int a, int& p1, int& p2)
{
    if (a % 2 == 0)
    {
        p1 = a / 2;
        p2 = a / 2;
    }
    else
    {
        p1 = a / 2;
        p2 = a / 2 + 1;
    }
}

int repetitions_max(vector<int>& v)
{
    int repetitions = 1;

    auto plate = v.rbegin() + 1;
    while (plate != v.rend() && *plate == v.back())
    {
        repetitions++;
        plate++;
    }

    return repetitions;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int n_diners;
        cin >> n_diners;

        vector<int> n_pancakes(n);

        for (int j = 0; j < n_diners; j++)
            cin >> n_pancakes[j];

        sort(n_pancakes.begin(), n_pancakes.end());

        int time = 0;

        int fst_max = n_pancakes.back();
        int repetitions = repetitions_max(n_pancakes);
        int snd_max = ((n_pancakes.size() - repetitions - 1) < 0)? -1 : n_pancakes[n_pancakes.size() - repetitions - 1];
        
        int p1, p2;
        divide(n_pancakes.back(), p1, p2);

        int cost_special_minute = repetitions + max(snd_max, max(p1, p2));

        while (cost_special_minute < n_pancakes.back())
        {
            time += repetitions;

            // remove all the max:

            for (int j = 0; j < repetitions; j++)
                n_pancakes.pop_back();

            // add all the two parts of the max divided:
            for (int j = 0; j < repetitions; j++)
            {
                n_pancakes.push_back(p1);
                n_pancakes.push_back(p2);
            }
                
            sort(n_pancakes.begin(), n_pancakes.end());

            fst_max = n_pancakes.back();
            repetitions = repetitions_max(n_pancakes);
            snd_max = ((n_pancakes.size() - repetitions - 1) < 0)? -1 : n_pancakes[n_pancakes.size() - repetitions - 1];
        
            divide(n_pancakes.back(), p1, p2);
            cost_special_minute = repetitions + max(snd_max, max(p1, p2));
        }

        time += n_pancakes.back();

        cout << "Case #" << i + 1 << ": " << time << endl;
    }
}
