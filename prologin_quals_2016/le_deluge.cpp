#include <iostream>

using namespace std;

int main()
{
    int h;
    cin >> h;

    int n;
    cin >> n;

    int res = 0;

    for (int i = 0; i < n && res == 0; i++)
    {
        int tmp;
        cin >> tmp;

        if (tmp < h)
            res = 1;
    }

    cout << res << endl;
}
