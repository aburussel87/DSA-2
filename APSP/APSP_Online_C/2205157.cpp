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

void warshall(vector<vector<int>> &graph, vector<vector<int>> &next, int V,vector<int> &maintenance)
{
    // Initialize the next matrix for path reconstruction
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

    // Run Warshall's algorithm for shortest paths
    for (int k = 0; k < V; k++)
    {
        auto it = find(maintenance.begin(),maintenance.end(),k);
        if(it!=maintenance.end()) continue;
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
    int m,n,k,q;
    freopen("test3.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin>>n>>m>>k;
    vector<int> capacity(n);
    vector<vector<int>> adj(n, vector<int>(n, INF));
    vector<vector<int>> next(n, vector<int>(n, -1));
    vector<int> maintenance;
    for(int i = 0; i<n; i++){
        int x;
        cin>>x;
        capacity[i] =x;
        if (x<0){
            maintenance.push_back(i);
        }
    }
    // Reading the graph
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u -= 1;
        v -= 1;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // Initialize the diagonal to 0 (no cost to stay at the same node)
    for (int i = 0; i < n; i++)
    {
        adj[i][i] = 0;
    }

    warshall(adj, next, n,maintenance);
    cin>>q;
    vector<int> queries(q);
    for(int i = 0; i<q; i++){
        int x;
        cin>>x;
        queries[i]  = x-1;
    }

    for(int i = 0; i<queries.size(); i++){
        int start = queries[i];
        vector<int> shortestPath = adj[start];
        vector<pair<int,int>> labs;
        vector<int> cap = capacity;
        for(int i = 0; i<shortestPath.size(); i++){
            labs.push_back({shortestPath[i],i});
        }
        sort(labs.begin(),labs.end());
        vector<int> result(k);
        int idx = 0;
        int filledlab = labs[idx].second;
        for(int i = 0; i<k; i++){
            while(filledlab<n && cap[filledlab] <= 0){
                filledlab = labs[++idx].second;
            }
            if(filledlab>=n){
                result[i] = -1;
                continue;
            }
            result[i] = shortestPath[filledlab];
            cap[filledlab] --;
        }
        for(int i = 0;i<k; i++){
            cout<<result[i]<<" ";
        }
        cout<<endl;
    }


    return 0;
}