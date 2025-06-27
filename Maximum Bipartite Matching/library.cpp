#include"max_flow.h"
int main()
{
    freopen("input.txt","r",stdin);
    int n, m;
    cin >> n >> m; // n = number of students, m = number of books

    int total_nodes = n + m + 2;
    int s = n + m;   
    int t = n + m + 1; 

    vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));
    vector<vector<int>> flow(total_nodes, vector<int>(total_nodes, 0));
    vector<vector<int>> adj(total_nodes);

    auto add_edge = [&](int u, int v, int cap)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    };

    // Max books each student can take
    for (int i = 0; i < n; i++)
    {
        int books;
        cin >> books;
        add_edge(s, i, books); // Source to student i
    }

    // Available copies for each book
    for (int j = 0; j < m; j++)
    {
        int copies;
        cin >> copies;
        add_edge(n + j, t, copies); // Book node to sink
    }

    // Read preferences: student → book with max desired copies
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int student, book, amount;
        cin >> student >> book >> amount;
        add_edge(student, n + book, amount); // Student node to book node
    }

    int maxflow = edmond_karp(adj, capacity, flow, s, t, total_nodes);
    cout << "\nMaximum number of books distributed: " << maxflow << "\n\n";


    // m+n+2 = total nodes, n = number of student, m = number of books
    printAssignments(adj, flow, m+n+2, n,m); 

 
    vector<int> set_s = find_min_cut(adj, capacity, flow, s, total_nodes);
    cout << "Min-Cut (Reachable from Source): ";
    for (int u : set_s)
        cout << u << " ";
    cout << "\nMin-Cut T set (Remaining): ";
    for (int i = 0; i < total_nodes; i++)
    {
        if (find(set_s.begin(), set_s.end(), i) == set_s.end())
            cout << i << " ";
    }
    cout << endl;

    return 0;
}

