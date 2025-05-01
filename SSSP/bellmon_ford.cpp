#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 1e9

class edge
{
public:
    int to, weight;
    edge(int x, int y)
    {
        this->to = x;
        this->weight = y;
    }
    bool operator>(const edge &other) const
    {
        return this->weight > other.weight;
    }
};

class Graph
{
    int V;
    vector<vector<edge>> adj;

public:
    Graph(int vertices)
    {
        this->V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w)
    {
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertices";
        }
        adj[u].push_back(edge(v, w));
    }
    void printGraph()
    {
        int i = 0;
        for (auto &rows : adj)
        {
            cout << i++ << "-->";
            for (int i = 0; i < rows.size(); i++)
            {
                cout << rows[i].to << "(" << rows[i].weight << ")" << " ";
            }
            cout << endl;
        }
    }

    void print_shortest_distance(int root)
    {
        priority_queue<edge, vector<edge>, greater<edge>> Q;
        vector<int> distance(V, INF);
        distance[root] = 0;

        Q.push(edge(root, 0));
        while (!Q.empty())
        {
            edge current = Q.top();
            int u = current.to;

            Q.pop();
            if (distance[current.to] < current.weight)
                continue;

            for (edge v : adj[u])
            {
                if (distance[v.to] > distance[u] + v.weight)
                {
                    distance[v.to] = distance[u] + v.weight;
                    Q.push(edge(v.to, distance[v.to]));
                }
            }
        }
        cout << "Shortest Distances from \"" << root << "\" :\n";
        for (int i = 0; i < V; i++)
        {
            if (distance[i] == INF)
            {
                cout << i << " : " << "No path exists!\n";
            }
            else
            {
                cout << i << " : " << distance[i] << endl;
            }
        }
    }

    void dijkstra(int root)
    {
        priority_queue<edge, vector<edge>, greater<edge>> Q;
        vector<int> distance(V, INF);
        distance[root] = 0;
        vector<int> parent(V, -1);

        Q.push(edge(root, 0));
        while (!Q.empty())
        {
            edge current = Q.top();
            int u = current.to;

            Q.pop();
            if (distance[current.to] < current.weight)
                continue;

            for (edge v : adj[u])
            {
                if (distance[v.to] > distance[u] + v.weight)
                {
                    distance[v.to] = distance[u] + v.weight;
                    Q.push(edge(v.to, distance[v.to]));
                    parent[v.to] = u;
                }
            }
        }
        cout << "Shortest Distances from \"" << root << "\" :\n";
        for (int i = 0; i < V; i++)
        {
            if (distance[i] == 0)
            {
                cout << i << "(source)\n";
            }
            else if (distance[i] == INF)
            {
                cout << i << " : " << "No path exists!\n";
            }
            else
            {
                cout << i << " (" << distance[i] << ") : ";
                int p = i;
                vector<int> path;
                while (p != -1)
                {
                    path.push_back(p);
                    p = parent[p];
                }
                reverse(path.begin(), path.end());
                for (int i = 0; i < path.size(); i++)
                {
                    if (i == path.size() - 1)
                    {
                        cout << path[i] << endl;
                        continue;
                    }
                    cout << path[i] << "-->";
                }
            }
        }
    }


    void bellman_ford(int root)
    {
        vector<int> distance(V, INF);
        distance[root] = 0;
        vector<int> parent(V, -1);

        for (int i = 0; i < V - 1; i++)
        {
            for (int u = 0; u < V; u++)
            {
                for (edge v : adj[u])
                {
                    if (distance[v.to] > distance[u] + v.weight)
                    {
                        distance[v.to] = distance[u] + v.weight;
                        parent[v.to] = u;
                    }
                }
            }
        }
        
        for (int u = 0; u < V; u++)
        {
            for (edge v : adj[u])
            {
                if (distance[v.to] > distance[u] + v.weight)
                {
                    cout << "Negative cycle detected!\n";
                    return;
                }
            }
        }


        cout << "Shortest Distances from \"" << root << "\" :\n";
        for (int i = 0; i < V; i++)
        {
            if (distance[i] == INF)
            {
                cout << i << " : " << "No path exists!\n";
            }
            else
            {
                cout << i << " : " << distance[i] << endl;
            }
        }
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    int vertices;
    cin >> vertices;
    Graph graph(vertices);
    int edges;
    cin >> edges;
    for (int i = 0; i < edges; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        graph.addEdge(x, y, z);
    }
    graph.dijkstra(2);
    graph.bellman_ford(2);
}