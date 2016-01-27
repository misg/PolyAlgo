#include <cstddef>
#include <algorithm>
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <string>

using namespace std;

struct tree
{
    tree(long val_) : val(val_), n_nodes(1), left(nullptr), right(nullptr) {}

    tree(long val_, tree* left_, tree* right_) : val(val_), left(left_), right(right_)
    {
        n_nodes = 1;

        if (left_ != nullptr)
            n_nodes += left_->n_nodes;

        if (right_ != nullptr)
            n_nodes += right_->n_nodes;
    }

    long val;
    long n_nodes;

    tree* left;
    tree* right;
};



tree* construct_tree(string t)
{
    if (t.empty())
        return nullptr;

    string left, right;

    int p = 0;

    string::const_iterator i = t.begin() + 1; // ignore the '('

    while (i != t.end())
    {
        if (*i == '(')
            p++;

        if (*i == ')')
            p--;

        if (*i == '.' && p == 0) // found the root
            break;
        else // still in the left subtree
        {
            left += *i;
            i++;
        }
    }

    i++; // ignore the '.'

    string val;

    while (*i != '.')
    {
        val += *i;
        i++;
    }

    i++; // ignore the '.'

    while (i != t.end())
    {
        right += *i;
        i++;
    }

    right.pop_back(); // ignore the last ')'

    return new tree(stol(val), construct_tree(left), construct_tree(right));
}



long max_cost(tree* t)
{
    if (t == nullptr)
        return 0;

    if (t->left == nullptr && t->right == nullptr) // leaf
        return 0;

    return (t->val + max(max_cost(t->left), max_cost(t->right)));
}



mpz_class n_binary_trees(int k)
{
    vector<mpz_class> res(k+1);

    res[0] = 1;
    res[1] = 1;

    for (int i = 2; i <= k; i++)
    {
        mpz_class n = 0;

        for (int j = 1; j <= i; j++)
            n += res[j-1] * res[i-j];

        res[i] = n;
    }

    return res[k];
}



int main()
{
   /* 
    string tree_s;
    cin >> tree_s;

    tree* t = construct_tree(tree_s);

    cout << max_cost(t) << endl;
    cout << n_binary_trees(t->n_nodes) << endl;
    */

    int i;
    cin >> i;

    cout << n_binary_trees(i) << endl;
}
