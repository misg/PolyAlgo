#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

const unordered_map<string, string> rules = {
    {"11", "1"},   {"1i", "i"},   {"1j", "j"},   {"1k", "k"}, 
    {"i1", "i"},   {"ii", "-1"},  {"ij", "k"},   {"ik", "-j"},
    {"j1", "j"},   {"ji", "-k"},  {"jj", "-1"},  {"jk", "i"},
    {"k1", "k"},   {"ki", "j"},   {"kj", "-i"},  {"kk", "-1"},
};

void find_matching_reduction(
    string::iterator& it, string::iterator end,
    string& reduction, string& signe, string match,
    bool until_end)
{
    while (it != end && (until_end || signe + reduction != match))
    {
        it++;

        if (it != end)
        {
            reduction = rules.at(reduction + *it);

            if (reduction[0] == '-')
            {
                signe = (signe == "-")? "" : "-";
                reduction = reduction[1];
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;

    for (int t = 0; t < n; t++)
    {
        int len, repet;
        cin >> len >> repet;

        string pattern;
        cin >> pattern;

        string input;
        for (int _ = 0; _ < repet; _++)
            input += pattern;
        
        auto i = input.begin();
        
        string reduction = string(1, *i);
        string signe;
        
        find_matching_reduction(i, input.end(), reduction, signe, "i", false);
        
        if (i != input.end() && (i + 1) != input.end())
        {
            auto j = i + 1;
            reduction = *j;

            find_matching_reduction(j, input.end(), reduction, signe, "j", false);

            if (j != input.end() && (j + 1) != input.end())
            {
                auto k = j + 1;
                reduction = *k;

                find_matching_reduction(k, input.end(), reduction, signe, "k", true);
                
                if (signe + reduction == "k")
                    cout << "Case #" << t + 1 << ": YES" << endl;
                else
                    cout << "Case #" << t + 1 << ": NO" << endl;
            }
            else
                cout << "Case #" << t + 1 << ": NO" << endl;
        }
        else
            cout << "Case #" << t + 1 << ": NO" << endl;
    }
}
