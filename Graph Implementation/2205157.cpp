/**
 * Jan25 CSE208
 * Practice Session on Graphs
 *
 *
 * Complete the following code by implementing the functions. Please be mindful of the corner cases.
 * Run the provided input file.
 * Be ready to explain the generated output to the evaluator.
 *
 *
 * The usage of any online tool and/or any GenAI is absolutely forbidden in this course
 * unless otherwise mentioned.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices)
    {
        this->V = vertices;
        adj.resize(V);
        for (int i = 0; i < V; i++)
        {
            adj[i].push_back(i);
        }
    }

    void addEdge(int u, int v)
    {
        if (u < 0 || u > V || v < 0 || v > V)
        {
            cout << "Invalid vertices";
        }
        for (auto &rows : adj)
        {
            if (rows[0] == u)
            {
                rows.push_back(v);
                return;
            }
        }
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

    int inDegree(int u)
    {
        int total = 0;
        for (auto rows : adj)
        {
            if (rows[0] == u)
                continue;
            for (int v : rows)
            {
                if (v == u)
                    total++;
            }
        }
        return total;
    }

    int outDegree(int u)
    {
        if (u >= 0 && u <= V)
        {
            for (auto &rows : adj)
            {
                if (rows[0] == u)
                {
                    return rows.size() - 1;
                }
            }
        }
        return 0;
    }

    bool removeVertex(int u)
{
    if (u < 0 || u >= V) return false;

    bool status = false;
    
    for (auto &rows : adj)
    {
        if (!rows.empty())
        {
            auto it = find(rows.begin() + 1, rows.end(), u);
            if (it != rows.end())
            {
                rows.erase(it);
                status = true;
            }
        }
    }

    for (auto it = adj.begin(); it != adj.end(); ++it)
    {
        if (!it->empty() && (*it)[0] == u)
        {
            adj.erase(it);
            status = true;
            break;
        }
    }

    return status;
}


    void printGraph()
    {
        for (auto &rows : adj)
        {
            cout<<rows[0]<<"-->";
            for (int i = 1; i<rows.size(); i++)
            {
                cout <<rows[i]<<" ";
            }
            cout << endl;
        }
    }
    void printInNeighbors(int u){
        cout<<"In Neighbors of "<<u<<" :";
        for(auto &rows: adj){
            if(rows[0] == u) continue;
            auto it = find(rows.begin(),rows.end(),u);
            if(it!=rows.end()){
                cout<<rows[0]<<" ";
            }
        }
        cout<<endl;
    }
    void printOutNeighbors(int u){
        for(auto &rows: adj){
            if(rows[0] == u){
                cout<<"Out Neighbors: ";
                for(int i = 1; i<rows.size(); i++){
                    cout<<rows[i]<<" ";
                }
                cout<<endl;
                return;
            }
        }
        cout<<"Vertex is absent";
    }

    // please note that once a vertex is removed, it will not be printed in the printGraph function
};
int main()
{
    int initialVertices;
    cout << "Enter number of initial vertices: ";
    freopen("input.txt","r",stdin);
    cin >> initialVertices;
    Graph g(initialVertices);

    while (true)
    {
        cout << "\n========== MENU ==========\n";
        cout << "1. Add Edge\n";
        cout << "2. Remove Edge\n";
        cout << "3. Remove Vertex\n";
        cout << "4. Print Graph\n";
        cout << "5. Find In-Degree of a Vertex\n";
        cout << "6. Find Out-Degree of a Vertex\n";
        cout << "7. Print In-Neighbors of a Vertex\n";
        cout << "8. Print Out-Neighbors of a Vertex\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        

        int choice, u, v;
        cin >> choice;

        if (choice == 9)
            break;

        switch (choice)
        {
        case 1:
            cout << "Enter source and destination vertex: ";
            cin >> u >> v;
            g.addEdge(u, v);
            break;
        case 2:
            cout << "Enter source and destination vertex to remove edge: ";
            cin >> u >> v;
            g.removeEdge(u, v);
            break;
        case 3:
            cout << "Enter vertex to remove: ";
            cin >> u;
            if (g.removeVertex(u))
            {
                cout << "Vertex " << u << " removed successfully.\n";
            }
            else
            {
                cout << "Failed to remove vertex " << u << ".\n";
            }
            break;
        case 4:
            cout<<endl;
            g.printGraph();
            break;
        case 5:
            cout << "Enter vertex to find in-degree: ";
            cin >> v;
            cout << "In-degree of " << v << " is: " << g.inDegree(v) << "\n";
            break;
        case 6:
            cout << "Enter vertex to find out-degree: ";
            cin >> v;
            cout << "Out-degree of " << v << " is: " << g.outDegree(v) << "\n";
            break;
        case 7:
            cout << "Enter vertex to find in-neighbors: ";
            cin >> u;
            g.printInNeighbors(u);
            break;
        case 8:
            cout << "Enter vertex to find out-neighbors: ";
            cin >> u;
            g.printOutNeighbors(u);
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    cout << "Program exited.\n";
    return 0;
}