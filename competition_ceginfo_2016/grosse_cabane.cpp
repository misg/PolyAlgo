#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<char>> graph_t;

const int n_neighbors = 4;
const int delta[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool is_valid(int x, int y, int width, int height)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return false;

    return true;
}

void dfs(int x, int y, graph_t& graph, int width, int height)
{
    graph[y][x] = 'v';

    for (int dl = 0; dl < n_neighbors; dl++)
    {
        int neighbor_x = x + delta[dl][0];
        int neighbor_y = y + delta[dl][1];

        if (is_valid(neighbor_x, neighbor_y, width, height))
            if (graph[neighbor_y][neighbor_x] == 'o')
                dfs(neighbor_x, neighbor_y, graph, width, height);
    }
}

int main()
{
    int height, width;
    cin >> height >> width;

    graph_t graph(height, vector<char>(width));

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cin >> graph[i][j];

    int n_rooms = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (graph[y][x] == 'o')
            {
                n_rooms++;
                
                dfs(x, y, graph, width, height);
            }
        }
    }

    cout << n_rooms << endl;
}
