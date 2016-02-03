#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

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
        int cost_special_minute = 1 + ((n_pancakes.back() % 2 == 0)? (n_pancakes.back() / 2) : (1 + n_pancakes.back() / 2));

        while (cost_special_minute < n_pancakes.back())
        {
            int max_plate = n_pancakes.back();
            n_pancakes.pop_back();
            
            int part = max_plate / 2;

            if (max_plate % 2 == 0)
            {
                n_pancakes.push_back(part);
                n_pancakes.push_back(part);
            }
            else
            {
                n_pancakes.push_back(part);
                n_pancakes.push_back(part + 1);
            }

            sort(n_pancakes.begin(), n_pancakes.end());

            time++;

            cost_special_minute = 1 + ((n_pancakes.back() % 2 == 0)? (n_pancakes.back() / 2) : (1 + n_pancakes.back() / 2));
        }

        time += n_pancakes.back();

        cout << "Case #" << i + 1 << ": " << time << endl;
    }
}
