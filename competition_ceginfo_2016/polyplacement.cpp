#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <utility>

using namespace std;

struct investment
{
    investment(int buy_, int sell_, float profit_) : buy(buy_), sell(sell_), profit(profit_) {}

    int buy;
    int sell;
    float profit;

    list<investment> next_investments;
};

investment* investment_profil0(string str)
{
    stringstream investment_s(str);

    int buy, sell;
    investment_s >> buy >> sell;

    float profit = 0;
    float c, d;

    while (investment_s >> c >> d)
        profit += c * d;

    if (profit <= 0)
        return nullptr;
    else
        return new investment(buy, sell, profit);
}

investment* investment_profil1(string str)
{
    stringstream investment_s(str);

    int buy, sell;
    investment_s >> buy >> sell;

    float profit = 0;
    float _, d;

    while (investment_s >> _ >> d)
        if (d > profit)
            profit = d;

    if (profit == 0)
        return nullptr;
    else
        return new investment(buy, sell, profit);
}

void add_investment(list<investment>& investments, investment x)
{
    bool result = false;
    //cout << "investment to add: " << x.buy << ", " << x.sell << ": " << x.profit << endl;

    for (investment& i : investments)
    {
    //cout << "current investment: " << i.buy << ", " << i.sell << ": " << i.profit << endl;
        if (x.buy >= i.sell) // not simultaneous
        {
            //cout << "on l'ajoute" << endl;
            add_investment(i.next_investments, x);

            result = true;
        }
    }

    if (not result) // x is not a part of a sequence -> x is the root of a new sequence
    { investments.push_back(x); //cout << "ajoute a la fin" << endl;
    }
}

float max_profit(list<investment>& investments)
{
    if (investments.empty())
        return 0;
   
    float max = 0;

    for (investment& i : investments)
    {
        //cout << i.profit << endl;
        float current_profit = i.profit + max_profit(i.next_investments);

        if (current_profit > max)
            max = current_profit;
    }

    return max;
}

bool compare_investments(investment& i1, investment& i2)
{
    return make_pair(i1.buy, i1.sell) < make_pair(i2.buy, i2.sell);
}

int main()
{
    string n_simulations_s;
    getline(cin, n_simulations_s);
    int n_simulations = stoi(n_simulations_s);

    for (int i = 0; i < n_simulations; i++)
    {
       string n_investments_s;
       getline(cin, n_investments_s);
       int n_investments = stoi(n_investments_s);

       string type_s;
       getline(cin, type_s);
       int type = stoi(type_s);

       string n_days_s;
       getline(cin, n_days_s);
       int n_days = stoi(n_days_s);

       list<investment> investments;

       for (int j = 0; j < n_investments; j++)
       {
           string investment_str;
           getline(cin, investment_str);

            investment* current = (type == 0)? investment_profil0(investment_str) : investment_profil1(investment_str);
            
            if (current != nullptr) // positive investment
            {
                //cout << current->profit << endl;
                investments.push_back(*current);
            }
       }

       investments.sort(compare_investments);

       list<investment> graph;
       for (investment& i : investments)
       {
           add_investment(graph, i);
 //          cout << endl;
           //cout << i.profit << endl;
       }

       cout.setf( std::ios::fixed, std:: ios::floatfield );
       cout.precision(2);
       cout << max_profit(graph) << endl;
    }
}
