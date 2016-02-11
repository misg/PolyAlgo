#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main()
{

    /* Parsing the input */

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int n_diners;
        cin >> n_diners;

        vector<int> n_pancakes(n_diners);
        int max_pancakes = 0;

        for (int j = 0; j < n_diners; j++)
        {
            cin >> n_pancakes[j];

            if (n_pancakes[j] > max_pancakes)
                max_pancakes = n_pancakes[j];
        }

    /* End of parsing */

    /* Solution of the contest analysis: */

        int min_minutes = max_pancakes + 1;

        for (int x = 1; x <= max_pancakes; x++)
        {
            int cost_special_minutes = 0; // = sum M(P_i) = sum ceil(P_i / x) - 1 where P_i is a plate with a number of pancakes > x

            for (int p : n_pancakes)
                if (p > x)
                    cost_special_minutes += ceil((float) p / (float) x) - 1;
            
            int minutes = cost_special_minutes + x;

            if (minutes < min_minutes)
                min_minutes = minutes;
       }

    /* End of the algorithm */

    cout << "Case #" << i + 1 << ": " << min_minutes << endl;

    }
}
