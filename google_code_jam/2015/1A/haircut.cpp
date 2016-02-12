#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <tuple>

using namespace std;

bool cmp_tuples(tuple<int, int, int>& t1, tuple<int, int, int>& t2)
{
//cout << get<0>(t1) << ", " << get<1>(t1) << ", " << get<2>(t1) << " et "
//     << get<0>(t2) << ", " << get<1>(t1) << ", " << get<2>(t1) << endl;
    return (get<2>(t1) < get<2>(t2));
}

int main()
{
    int n_tc;
    cin >> n_tc;

    for (int tc = 0; tc < n_tc; tc++)
    {
        int n_b, r;
        cin >> n_b >> r;

        vector<tuple<int, int, int>> info(n_b + 1); // <barber_i, M_i, t_i> where t_i is the time after the barber will be free
        list<int> free;

        for (int b_i = 1; b_i <= n_b; b_i++)
        {
            int M_i;
            cin >> M_i;
cout << "(" << b_i << ", " << M_i << ", " << "0)" << endl;
            info[b_i] = make_tuple(b_i, M_i, 0);
            free.push_back(b_i);
        }

        int ret;

        for (int c_i = 1; c_i <= r; c_i++)
        {
        cout << "client: " << c_i << endl;
            if (free.empty())
            {
                int min_time = get<2>(*min_element(info.begin() + 1, info.end(), cmp_tuples));

                while (free.empty())
                { cout << "on enleve " << min_time << " min a tout le monde" << endl;
                    for (auto x : info)
                    {
cout << get<0>(x) << ", " << get<1>(x) << ", " << get<2>(x) << " (avant) et apres : ";
                        get<2>(x) -= min_time;
cout << get<0>(x) << ", " << get<1>(x) << ", " << get<2>(x) << endl;
                        
                        if (get<2>(x) == 0) {cout << "barbier num " << get<0>(x) << " libre" << endl;
                            free.push_back(get<0>(x));}
                    }
cout << "ALLO : " << get<0>(info[1]) << ", " << get<1>(info[1]) << ", " << get<2>(info[1]) << endl;
                }
            }


cout << "ALLO : " << get<0>(info[1]) << ", " << get<1>(info[1]) << ", " << get<2>(info[1]) << endl;

            if (c_i == r)
                ret = free.front();

                // the barber is no more free, it will be in M minutes :
                
                get<2>(info[free.front()]) = get<1>(info[free.front()]);
         cout << "barbier num " << free.front() << " attribue, sera libre dans " << get<2>(info[free.front()]) << endl; 
                free.pop_front();
        }

//cout << "size: " << free.size() << endl;
        cout << "Case #" << tc + 1 << ": " << ret << endl;
    }
}
