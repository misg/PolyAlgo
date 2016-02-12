#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <tuple>

using namespace std;

struct b
{
    b(int i_, int M_i_, int free_) :
        i(i_), M_i(M_i_), free(free_) {};

    int i;
    int M_i;
    int free;
};


bool cmp_b(b* b1, b* b2)
{
    return b1->free < b2->free;
}

int main()
{
    int n_tc;
    cin >> n_tc;

    for (int tc = 0; tc < n_tc; tc++)
    {
        int n_b, r;
        cin >> n_b >> r;

        vector<b*> info(n_b); 
        list<int> free;

        for (int b_i = 0; b_i < n_b; b_i++)
        {
            int M_i;
            cin >> M_i;
            
            info[b_i] = new b(b_i, M_i, 0);
            free.push_back(b_i);
        }

        int ret;

        for (int c_i = 1; c_i <= r; c_i++)
        {
            if (free.empty())
            {
                int min_time = (*min_element(info.begin(), info.end(), cmp_b))->free;

                for (auto x : info)
                {
                    x->free -= min_time;
                        
                    if (x->free == 0)
                        free.push_back(x->i);
                }
            }

            b* free_b = info[free.front()];

            if (c_i == r)
                ret = free_b->i + 1;

            free_b->free = free_b->M_i;

            free.pop_front(); // Barber no more available
        }

        cout << "Case #" << tc + 1 << ": " << ret << endl;
    }
}
