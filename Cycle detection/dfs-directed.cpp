/**
 * Jan25 CSE208
 * Practice Session on BFS/DFS
 *
 *
 * Complete the following code by implementing the functions. Please be mindful of the corner cases.
 * Run the provided input file.
 * Be ready to explain the generated output to the evaluator.
 *
 *
 * The usage of any online tool and/or any GenAI is absolutely forbidden in this course
 * unless otherwise mentioned.
 *
 *
 * You may consider the following:
 *
 * BFS(Graph, start_node):
    # Create a queue to store nodes to be explored
    # Create a set to track visited nodes

    # Start from the initial node and enqueue it

    # While the queue is not empty
        # Dequeue a node from the queue
        # Process the current node (e.g., print it or store it)
        # For each neighbor of the current node
            # If the neighbor has not been visited
                # Mark the neighbor as visited and enqueue it
 *
 *
 * DFS(Graph, current_node, visited):
    # Mark the current node as visited
    # Process the current node (e.g., print it or store it)

    # For each neighbor of the current node
        # If the neighbor has not been visited
            # Recursively call DFS on the neighbor
            DFS(Graph, neighbor, visited)
 *
 *
 *  **-**
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    // You can use the code from previous practice session.
    Graph(int vertices)
    {
        this->V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            cout << "Invalid vertices";
        }
        adj[u].push_back(v);
    }

    void removeEdge(int u, int v)
    {
        if (u < 0 || u > V || v < 0 || v > V)
        {
            cout << "Invalid vertices";
        }
        for (auto &rows : adj)
        {
            if (rows[0] == u)
            {
                auto it = find(rows.begin(), rows.end(), v);
                if (it != rows.end())
                {
                    rows.erase(it);
                }
            }
        }
    }
    void printGraph()
    {
        int i = 0;
        for (auto &rows : adj)
        {
            cout << i++ << "-->";
            for (int i = 0; i < rows.size(); i++)
            {
                cout << rows[i] << " ";
            }
            cout << endl;
        }
    }
    enum Color
    {
        WHITE,
        GRAY,
        BLACK
    };

    bool dfs(int root, vector<Color> &color)
    {
        color[root] = GRAY;
        for (int v : adj[root])
        {
            if (color[v] == WHITE)
            {
                return dfs(v, color);
            }
            else if (color[v] == GRAY)
            {
                return true;
            }
        }
        color[root] = BLACK;
        return false;
    }

    void checkCycle()
    {
        vector<Color> color(V, WHITE);
        for (int i = 0; i < V; i++)
        {
            if (color[i] == WHITE)
            {
                if (dfs(i, color))
                {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
        cout << "YES" << endl;
    }
};

int main()
{
    int initialVertices;
    freopen("input.txt", "r", stdin);
    cin >> initialVertices;
    Graph g(initialVertices);
    int edges;
    cin >> edges;
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    g.checkCycle();
    // Write the necessary code here
}