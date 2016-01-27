#include <iostream>
#include <cmath>

int tbl_h[10000] = {0};

using namespace std;

int main()
{
    int vol0;
    cin >> vol0;

    int n;
    cin >> n;

    int min = 100000;

    for (int i = 0; i < n; i++)
    {
        cin >> tbl_h[i];

        if (tbl_h[i] < min)
            min = tbl_h[i];
    }

    int vol = 0;
    int h = min;

    while (vol < vol0)
    {
        vol = 0;
        h++;

        for (int i = 0; i < n; i++)
        {
            if (tbl_h[i] < h)
                vol += abs(h - tbl_h[i]);
        }
    }

    if (vol > vol0)
        h--;

    cout << h << endl;
}
