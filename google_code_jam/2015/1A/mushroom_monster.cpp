#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n_tc;
    cin >> n_tc;

    for (int tc = 0; tc < n_tc; tc++)
    {
        int n_plates;
        cin >> n_plates;

        vector<int> m(n_plates);

        int delta_max  = 0;

        for (int p = 0; p < n_plates; p++)
        {
            cin >> m[p];
            
            if (p > 0)
            {
                int delta_p = m[p-1] - m[p];

                if (delta_p > delta_max)
                    delta_max = delta_p;
            }
        }
        
        int rate = delta_max;
        
        int ret1 = 0;
        int ret2 = 0;

        for (int p = 1; p < n_plates; p++)
        {
            if (m[p] < m[p-1]) // She ate
                ret1 += m[p-1] - m[p];
            
            ret2 += min(m[p-1], rate);
        }

        cout << "Case #" << tc + 1 << ": " << ret1 << " " << ret2 << endl;
    }
}
