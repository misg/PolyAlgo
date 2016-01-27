#include <algorithm>
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

const int inf = -1;

struct node
{
    node(string name_) : name(name_) {};

    string name;
    bool visited = false;
    int distance = inf;
    node* predecessor_on_the_path = nullptr;
    list<node*> neighbors;
};

typedef vector<node*> graph_t;

bool is_neighbor(node* n1, node* n2)
{
    int delta = 0;

    string::const_iterator i = n1->name.begin();
    string::const_iterator j = n2->name.begin();

    while (i != n1->name.end() && j != n2->name.end())
    {
        if (*i != *j)
            delta++;

        i++;
        j++;
    }

    return (delta <= 1);
}

bool compare_nodes(node* n1, node* n2)
{
    if (n1->distance == inf)
        return true;

    if (n2->distance == inf)
        return false;

    return (n1->distance > n2->distance);
}

bool find_path(node* start, node* end)
{
    vector<node*> not_visited;

    start->distance = 0;
    not_visited.push_back(start);
    
    make_heap(not_visited.begin(), not_visited.end(), compare_nodes);
   
    while (not not_visited.empty() && not end->visited)
    {
        pop_heap(not_visited.begin(), not_visited.end(), compare_nodes);
        node* current = not_visited.back();
        not_visited.pop_back();

        if (not current-> visited)
        {
            for (node* neighbor : current->neighbors)
            {
                if (not neighbor->visited &&
                    (neighbor->distance == inf ||
                    (neighbor->distance > (current->distance + 1)) ||
                    (neighbor->distance == (current->distance + 1) && (current->name > neighbor->predecessor_on_the_path->name))))
                {
                    neighbor->distance = current->distance + 1;
                    neighbor->predecessor_on_the_path = current;

                    not_visited.push_back(neighbor);
                    push_heap(not_visited.begin(), not_visited.end(), compare_nodes);
                }
            }

            current->visited = true;
        }
    }

    return end->visited;
}

int main()
{
    string start_s, end_s;
    cin >> start_s >> end_s;

    node* start = new node(start_s);
    node* end   = new node(end_s);

    if (is_neighbor(start, end))
        cout << start->name << " " << end->name << endl;
    else
    {
        graph_t graph;

        graph.push_back(start);
        graph.push_back(end);

        string word;

        while (cin >> word)
        {
            if (word != start_s && word != end_s)
            {
                node* current = new node(word);

                for (node* n : graph)
                {
                    if (is_neighbor(n, current))
                    {
                        n->neighbors.push_back(current);
                        current->neighbors.push_back(n);
                    }
                }

                graph.push_back(current);
            }
        }

        if (find_path(start, end))
        {
            string path;

            node* current = end;

            while (current->name != start->name)
            {
                path = " " + current->name + path;

                current = current->predecessor_on_the_path;
            }

            cout << start->name << path << endl;
        }
        else
            cout << ":(" << endl;
    }
}
