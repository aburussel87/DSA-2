#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define INF 1e9

void print_matrix(vector<vector<int>> &matrix, bool graph, int x)
{
    if (graph)
    {
        cout << "APSP Matrix for ";
    }
    else
    {
        cout << "Parent Matrix for ";
    }
    cout << x << " as intermediate vertex: \n";
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == INF)
                cout << "INF ";
            else
                cout << matrix[i][j] << "   ";
        }
        cout << endl;
    }
}

void warshall(vector<vector<int>> &graph, vector<vector<int>> &next, int V)
{

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (graph[i][j] != INF && i != j)
            {
                next[i][j] = j;
            }
        }
    }

    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (graph[i][k] != INF && graph[k][j] != INF && graph[i][j] > graph[i][k] + graph[k][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

vector<int> print_path(int u, int v, vector<vector<int>> &next)
{
    if (u == v || next[u][v] == -1)
        return {};
    vector<int> path;
    path.push_back(u);
    while (u != v)
    {
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}

int main()
{

    int V;
    int E;
    freopen("warshall.txt", "r", stdin);
    cin >> V >> E;
    vector<vector<int>> adj(V, vector<int>(V, INF));
    vector<vector<int>> next(V, vector<int>(V, -1));
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
    }
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                adj[i][j] = 0;
        }
    }

    warshall(adj, next, V);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                continue;
            vector<int> path = print_path(i, j, next);
            if (path.empty())
            {
                cout << "No path from " << i << " to " << j << ".\n";
                continue;
            }
            cout << "Path from " << i << " to " << j << " : ";
            for (int i = 0; i < path.size(); i++)
            {
                if (i == path.size() - 1)
                {
                    cout << path[i] << " (with cost: " << adj[i][j] << ")\n";
                    continue;
                }
                cout << path[i] << "-->";
            }
        }
        cout << "\n";
    }
}