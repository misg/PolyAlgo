#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int h;
    cin >> h;

    int n;
    cin >> n;

    int vol = 0;

    for (int i = 0; i < n; i++)
    {
        int tmp_h;
        cin >> tmp_h;

        if (tmp_h < h)
            vol += abs(h - tmp_h);
    }

    cout << vol << endl;
}
