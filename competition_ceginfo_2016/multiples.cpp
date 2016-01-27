#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

long b_to_dec(string str, int base)
{
    string::reverse_iterator i = str.rbegin();

    long result  = 0;
    long r       = 1;

    while (i != str.rend())
    {
        if (*i == ')')
        {
            string nbr;

            while (*i != '(')
            {
                nbr = *i + nbr;
                i++;
            }

            i++; // ignore '('

            nbr.pop_back(); // remove the ')'

            result += r * stoi(nbr);
        }
        else
        {
            result += r * (*i - '0');
            i++;
        }

        r *= base; 
    }

    return result;
}

vector<string>* dec_to_b(long x, int base)
{
    vector<string>* result = new vector<string>();

    long m = x / base;
    long r = x % base;

    while (m != 0 || r != 0)
    {

        if (r >= 10)
            result->push_back("(" + to_string(r) + ")");
        else
            result->push_back(to_string(r));

        r = m % base;
        m /= base;
    }

    return result;
}

using namespace std;

int main()
{
   /* 
    //cout << b_to_dec("159", 16) << endl;

    cout << b_to_dec("(14)3424(10)(12)0", 16) << endl;

    vector<string>* x = dec_to_b(b_to_dec("(14)3424(10)(12)0", 16), 16);

    for (int i = 7; i >= 0; i--)
        cout << x->at(i);
    cout << endl;
    */
    
    string p;
    cin >> p;

    int b, n, l;
    cin >> b >> n >> l;

    for (int _ = 0; _ < l; _++)
    {
        string m;
        cin >> m;

        vector<string>* x = dec_to_b(b_to_dec(m, b) / b_to_dec(p, b), b);

        if (n > x->size())
        {
            for (int i = 0; i < n - x->size(); i++)
                cout << "0";
        }

    
        int limit = min((int) x->size(), n);

        for (int i = limit - 1; i >= 0; i--)
            cout << x->at(i);

        cout << endl;
    } 
}
