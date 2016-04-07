#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum letter_t {
    begin,
    mid,
    end,
    all
};

typedef vector<letter_t> states;
typedef vector<states> alphabet_t;

bool check_letter(char letter, letter_t type, alphabet_t& alphabet)
{
    int i = letter - 'a';

    for (auto state : alphabet[i])
    {
        switch (state)
        {
            case letter_t::begin:
                if (type == letter_t::begin || type == letter_t::mid)
                    return false;
                break;

            case letter_t::mid:
                return false;
                break;

            case letter_t::end:
                if (type == letter_t::mid || type == letter_t::end)
                    return false;
                break;

            case letter_t::all:
                if (type == letter_t::mid)
                    return false;
                break;
        }
    }

    return true;
}

bool check_word(string word, alphabet_t& alphabet)
{
    if (word.size() == 1)
    {
        if (check_letter(word[0], letter_t::all, alphabet))
        {
            int i = word[0] - 'a';
            alphabet[i].push_back(letter_t::all);

            return true;
        }
        else
            return false;
    }

    bool several_letters = false;

    char prec = word[0];

    for (int i = 1; i < word.size(); i++)
    {
        char current = word[i];

        if (current != prec)
        {
            if (several_letters)
            {
                if (check_letter(prec, letter_t::mid, alphabet))
                {
                    int j = prec - 'a';
                    alphabet[j].push_back(letter_t::mid);
                }
                else
                    return false;
            }
            else
            {
                if (check_letter(prec, letter_t::begin, alphabet))
                {
                    int j = prec - 'a';
                    alphabet[j].push_back(letter_t::begin);
                }
                else
                    return false;

                several_letters = true;
            }
        }

        prec = current;
    }

    if (several_letters)
    {
        if (check_letter(prec, letter_t::end, alphabet) && prec != word[0])
        {
            int j = prec - 'a';
            alphabet[j].push_back(letter_t::end);
        }
        else
            return false;
    }
    else
    {
        if (check_letter(prec, letter_t::all, alphabet))
        {
            int j = prec - 'a';
            alphabet[j].push_back(letter_t::all);
        }
        else
            return false;
    }

    return true;
}


bool check_input(vector<string>& input)
{
    alphabet_t alphabet(26);

    for (string word : input)
    {
        if (not check_word(word, alphabet))
            return false;
    }

    return true;
}

struct one_letter_word
{
    char letter;
    int  n_rep;
};

struct disjoint_set
{
    vector<one_letter_word> one_letter_words;
    vector<string> other_words;
};

bool is_one_letter_word(string word)
{
    char first = word[0];

    for (char c : word)
        if (c != first)
            return false;

    return true;
}

typedef vector<disjoint_set*> disjoint_sets_t;

bool belong_to_disjoint_set(string word, disjoint_set* set)
{
    for (auto w : set->one_letter_words)
        if (w.letter == word[0] || w.letter == word[word.size()-1])
            return true;

    for (auto w : set->other_words)
        if (w[0] == word[word.size()-1] || w[w.size()-1] == word[0])
            return true;

    return false;
}

void construct_disjoint_sets(vector<string>& input, disjoint_sets_t& disjoint_sets)
{
    disjoint_set* first = new disjoint_set();

    if (is_one_letter_word(input[0]))
        first->one_letter_words.push_back({input[0][0], 1});
    else
        first->other_words.push_back(input[0]);

    disjoint_sets.push_back(first);
    input.erase(input.begin());

    int i_set = 0;
    
    while (input.size() > 0)
    {
        bool more_members = true;

        while (more_members)
        {
            more_members = false;

            auto word = input.begin();

            while (word != input.end())
            {
                if (belong_to_disjoint_set(*word, disjoint_sets[i_set]))
                {
                    more_members = true;

                    if (is_one_letter_word(*word))
                    {
                        bool found = false;

                        for (int j = 0; j < (disjoint_sets[i_set])->one_letter_words.size(); j++)
                        {
                            if (disjoint_sets[i_set]->one_letter_words[j].letter == (*word)[0])
                            {
                                (disjoint_sets[i_set])->one_letter_words[j].n_rep++;
                                found = true;
                            }
                        }

                        if (not found)
                            (disjoint_sets[i_set])->one_letter_words.push_back({(*word)[0], 1});
                    }
                    else
                        (disjoint_sets[i_set])->other_words.push_back(*word);

                    word = input.erase(word);
                }
                else
                    word++;
            }
        }
   
        if (input.size() > 0)
        {
            disjoint_set* new_set = new disjoint_set();

            if (is_one_letter_word(input[0]))
                new_set->one_letter_words.push_back({input[0][0], 1});
            else
                new_set->other_words.push_back(input[0]);

            disjoint_sets.push_back(new_set);
            input.erase(input.begin());
        
            i_set++;
        }
    }
}


/*
 * For some debug:
 *
void print_disjoint_sets(disjoint_sets_t& sets)
{
    for (auto s : sets)
    {
        cout << "disjoint set:" << endl;

        cout << "one-letter words:" << endl;
        
        for (auto olw : s->one_letter_words)
            cout << olw.letter << ": " << olw.n_rep << endl;

        cout << "other words:" << endl;

        for (auto ow : s->other_words)
            cout << ow << endl;

        cout << endl;
    }
}
*/

unsigned long factorial(unsigned int n)
{
    if (n == 1)
        return 1;
    else
        return (((unsigned long) n) * factorial(n-1)) % 1000000007;
}

unsigned long n_combinations(disjoint_sets_t& sets)
{
    unsigned long res = factorial(sets.size());

    for (auto s : sets)
    {
        unsigned long x = 1;

        for (auto one_letter_word : s->one_letter_words)
            x = (x * factorial(one_letter_word.n_rep)) % 1000000007;

        res = (res * x) % 1000000007;
    }

    return (res % 1000000007);
}

int main()
{
    int t;
    cin >> t;

    for (int t_i = 0; t_i < t; t_i++)
    {
        int n;
        cin >> n;

        vector<string> cars(n);

        for (int car_i = 0; car_i < n; car_i++)
            cin >> cars[car_i];
        
        if (check_input(cars))
        {
            disjoint_sets_t sets;
            construct_disjoint_sets(cars, sets);

            // Debug:
            //print_disjoint_sets(sets);

            cout << "Case #" << t_i + 1 << ": " << n_combinations(sets) << endl;
        }
        else
            cout << "Case #" << t_i + 1 << ": 0" << endl;
    }
}
