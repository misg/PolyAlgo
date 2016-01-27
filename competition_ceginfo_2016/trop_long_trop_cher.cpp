#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <vector>
#include <utility>

using namespace std;

const int inf = -1;

struct node
{
    node(int id_) : id(id_) {};

    int id;

    bool visited = false;

    list<pair<node*, int>> edges;

    list<int> children;
};

typedef vector<node*> graph_t;

bool compare_edges(tuple<node*, node*, int>& e1, tuple<node*, node*, int>& e2)
{
    return (get<2>(e1) > get<2>(e2));
}

void construct_span_tree(node* start)
{
    vector<tuple<node*, node*, int>> not_visited;

    not_visited.push_back(make_tuple(start, nullptr, 0));
    
    make_heap(not_visited.begin(), not_visited.end(), compare_edges);
   
    while (not not_visited.empty())
    {
        pop_heap(not_visited.begin(), not_visited.end(), compare_edges);
        
        node* current = get<0>(not_visited.back());
        node* parent  = get<1>(not_visited.back());

        not_visited.pop_back();

        if (not current->visited)
        {
            for (pair<node*, int> edge : current->edges)
            {
                node* neighbor = edge.first;
                int cost       = edge.second;

                not_visited.push_back(make_tuple(neighbor, current, cost));
                push_heap(not_visited.begin(), not_visited.end(), compare_edges);
            }

            current->visited = true;
            if (parent != nullptr)
                parent->children.push_back(current->id);
        }
    }
}

int main()
{
    int n;
    cin >> n;

    graph_t graph(n + 1);

    for (int i = 1; i <= n; i++)
        graph[i] = new node(i);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            string cost_s;
            cin >> cost_s;

            if (j > i) // superior triangular matrix
            {
                if (cost_s != "-")
                {
                    int cost = stoi(cost_s);

                    graph[i]->edges.push_back(make_pair(graph[j], cost));
                    graph[j]->edges.push_back(make_pair(graph[i], cost));
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (not graph[i]->visited)
            construct_span_tree(graph[i]);
    }

    list<pair<int, int>> result;

    for (int i = 1; i <= n; i++)
    {
        // segfault?
       
        for (int c : graph[i]->children)
        {
            if (graph[i]->id <= c)
                result.push_back(make_pair(graph[i]->id, c));
            else
                result.push_back(make_pair(c, graph[i]->id));
        }
    }

    result.sort();

    for (pair<int, int> p : result)
        cout << p.first << " " << p.second << endl;

    for (int i = 1; i <= n; i++)
        delete graph[i];
}
