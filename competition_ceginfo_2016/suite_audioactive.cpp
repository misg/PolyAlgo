#include <iostream>
#include <string>

using namespace std;

string compute_predecessor(string str)
{
    string res;
    
    for (int i = 0; i < str.size() - 1; i = i + 2)
        for (int j = 0; j < (str[i] - '0'); j++)
            res += str[i + 1];

    return res;
}

string compute_conway(string str)
{
    string res;

    string::iterator i = str.begin();
    string::iterator j = str.begin();

    int k = 0;

    while (i != str.end())
    {
        if (j != str.end() && *i == *j)
        {
            k++;
            j++;
        }
        else
        {
            res += to_string(k) + *i;

            k = 0;
            i = j;
        }
    }

    return res;
}

int main()
{
    string str;
    cin >> str;

    bool zero = false;

    for (char c : str)
        if (c == '0')
            zero = true;

    if (str.size() % 2 != 0 || zero)
        cout << str << endl;
    else
    {
        bool infinite_loop = false;

        string current = str;
        string pred    = compute_predecessor(current);

        int k = 0;

        while (compute_conway(pred) == current)
        {
            current = pred;
            pred    = compute_predecessor(current);

            k++;

            if (k > 1000000)
            {
                cout << ":(" << endl;
                break;
            }
        }

        if (k <= 1000000)
            cout << current << endl;
    }
}
