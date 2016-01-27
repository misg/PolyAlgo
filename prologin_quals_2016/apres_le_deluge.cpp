#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>
#include <tuple>

using namespace std;

class Node
{
    public:
        Node(int id, int x, int y) : _id(id), _x(x), _y(y) {}

        static int _n_nodes;
        
        int getID() {return _id;}
        int getX()  {return _x;}
        int getY()  {return _y;}

        list<Node*> getNeighbors() {return _neighbors;}

        void add_neighbor(Node* n)  {_neighbors.push_back(n);}
        void remove_last_neighbor() {_neighbors.pop_back();}

    private:
        int _id;
        int _x;
        int _y;

        list<Node*> _neighbors;
};

int Node::_n_nodes = 0;

typedef tuple<Node*, Node*, double> edge; 

bool has_cycle_aux(Node* from, Node* parent, vector<bool>& visited_nodes)
{
    visited_nodes[from->getID()] = true;

    for (Node* neighbor : from->getNeighbors())
    {
        if (parent == nullptr || neighbor->getID() != parent->getID()) // Memo: we manipulate undirected (valued) graph
        {
            if (visited_nodes[neighbor->getID()])
                return true;
            else if (has_cycle_aux(neighbor, from, visited_nodes))
                return true;
        }
    }

    return false;
}

bool has_cycle(Node* from)
{
    vector<bool> visited_nodes(Node::_n_nodes, false);
    
    return has_cycle_aux(from, nullptr, visited_nodes);
}

/* DEBUG:
void print_edge(edge& e)
{
    cout << "(" << get<0>(e)->getX() << ", " << get<0>(e)->getY() << ") to "
         << "(" << get<1>(e)->getX() << ", " << get<1>(e)->getY() << ") : "
         << get<2>(e)
         << endl;
}
*/

bool cmp(edge& e1, edge& e2)
{
    return get<2>(e1) < get<2>(e2);
}

int main()
{
    int n;
    cin >> n;

    vector<Node*> graph;
    vector<edge> edges;

    for (int i = 0; i < n; i++)
    {
        int x1, y1;
        cin >> x1 >> y1;

        Node* current = new Node(i, x1, y1);

        Node::_n_nodes++;

        // We compute all possible edges which start from the added node:

        for (Node* n : graph)
        {
            int x2 = n->getX();
            int y2 = n->getY();

            double dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

            edges.push_back(make_tuple(current, n, dist));
        }

        graph.push_back(current);
    }

    // Kruskal's algorithm:

    sort(edges.begin(), edges.end(), cmp);

    int n_edges = 0;
    vector<edge>::const_iterator current_edge = edges.begin();

    double final_cost = 0;

    while (n_edges < graph.size() - 1 && current_edge != edges.end())
    {
        Node* from = get<0>(*current_edge);
        Node* to   = get<1>(*current_edge);

        double cost = get<2>(*current_edge);

        from->add_neighbor(to);
        to->add_neighbor(from);

        if (has_cycle(from))
        {
            from->remove_last_neighbor();
            to->remove_last_neighbor();
        }
        else
        {
            n_edges++;
            final_cost += cost;
        }

        ++current_edge;
    }

    cout << (int) final_cost << endl;

    // Deallocate memory:

    for (Node* n : graph)
        delete n;
}
