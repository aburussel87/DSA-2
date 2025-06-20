#include <bits/stdc++.h>
using namespace std;

int bfs(vector<vector<int>> &adj, vector<vector<int>> &capacity, vector<vector<int>> &flow, vector<int> &parent, int s, int t)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});
    while (!q.empty())
    {
        int u = q.front().first;
        int curr_flow = q.front().second;
        q.pop();
        for (int v : adj[u])
        {
            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0)
            {
                parent[v] = u;
                int newflow = min(curr_flow, capacity[u][v] - flow[u][v]);
                if (v == t)
                    return newflow;
                q.push({v, newflow});
            }
        }
    }
    return 0;
}

int edmond_karp(vector<vector<int>> &adj, vector<vector<int>> &capacity, vector<vector<int>> &flow, int s, int t, int n)
{
    int maxflow = 0;
    vector<int> parent(n);
    int newflow;
    while ((newflow = bfs(adj, capacity, flow, parent, s, t)))
    {
        maxflow += newflow;
        int v = t;
        while (v != s)
        {
            int u = parent[v];
            flow[u][v] += newflow;
            flow[v][u] -= newflow;
            v = u;
        }
    }
    return maxflow;
}


void printAssignments(const vector<vector<int>> &adj, const vector<vector<int>> &flow, int n, int person, int type)
{
    int person_start = 0;
    int person_end = person-1;
    int type_start = person;
    int type_end = n-3;
    cout << "Assignments (Person → Type -> amount):\n";
    for (int i = person_start; i <= person_end; i++)
    {
        for (int j : adj[i])
        {
            if (j >= type_start && j <= type_end && flow[i][j] > 0)
            {
                cout << "  Person " << i - person_start << " → Type " << j - type_start << " -> amount: " << flow[i][j] << "\n";
            }
        }
    }
}


vector<int> find_min_cut(vector<vector<int>> &adj, vector<vector<int>> &capacity, vector<vector<int>> &flow, int s, int n)
{
    vector<int> set_s;
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    set_s.push_back(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        visited[u] = true;
        for (int v : adj[u])
        {
            if (!visited[v] && capacity[u][v] - flow[u][v] > 0)
            {
                visited[v] = true;
                set_s.push_back(v);
                q.push(v);
            }
        }
    }
    return set_s;
}