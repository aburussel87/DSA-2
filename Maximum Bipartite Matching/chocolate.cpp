/*
Problem Description (Max Flow):

We have a group of people and a collection of chocolate types.
- Each person has some amount of money that lets them buy multiple chocolates in total (e.g., up to 3 chocolates).
- Each chocolate type has a limited number of chocolates available in the shop (e.g., 4 chocolates of Type1).
- A person can buy multiple chocolates of the *same* type if they want.
- Each person has preferences — they only want certain chocolate types.

Goal:
Maximize the total number of chocolates sold,
while respecting:
  - Each person's total buying limit,
  - The number of available chocolates per type,
  - Person's preferences.

Flow Network Construction:
1. Add a source node 'S' and a sink node 'T'.
2. Create a node for each person and each chocolate type.
3. Add an edge from S to each person with capacity = person's buying limit.
4. For each person-chocolate preference, add an edge from person to chocolate type
   with capacity = how many chocolates the person could buy of that type (e.g., min(buying limit, chocolates available)).
5. Add an edge from each chocolate type to T with capacity = number of available chocolates.

Run max flow algorithm (e.g., Edmonds-Karp).
The flow from person → chocolate type indicates how many chocolates of that type each person buys.
*/
#include"max_flow.h"

int main()
{
    // 3 people (0–2), 3 chocolate types (3–5), source=6, sink=7
    int n = 8;
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<vector<int>> adj(n);

    auto add_edge = [&](int u, int v, int cap)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    };

    // Source to people
    add_edge(6, 0, 3); // Person 0 can buy up to 3 chocolates total
    add_edge(6, 1, 2); // Person 1 can buy up to 2 chocolates total
    add_edge(6, 2, 2); // Person 2 can buy up to 2 chocolates total

    // People to chocolate types (based on preferences)
    // Each edge indicates a person's willingness to buy multiple chocolates of a preferred type
    add_edge(0, 3, 3); // Person 0 → Chocolate Type 0 : can buy up to 3 chocolates of this type
    add_edge(0, 4, 3); // Person 0 → Chocolate Type 1 : can buy up to 3 chocolates of this type
    add_edge(1, 3, 2); // Person 1 → Chocolate Type 0 : can buy up to 2 chocolates of this type
    add_edge(1, 5, 2); // Person 1 → Chocolate Type 2 : can buy up to 2 chocolates of this type
    add_edge(2, 4, 2); // Person 2 → Chocolate Type 1 : can buy up to 2 chocolates of this type
    add_edge(2, 5, 2); // Person 2 → Chocolate Type 2 : can buy up to 2 chocolates of this type

    // Chocolate types to Sink
    add_edge(3, 7, 4); // Chocolate Type 0 has 4 chocolates available
    add_edge(4, 7, 2); // Chocolate Type 1 has 2 chocolates available
    add_edge(5, 7, 3); // Chocolate Type 2 has 3 chocolates available

    int s = 6, t = 7;
    int maxflow = edmond_karp(adj, capacity, flow, s, t, n);

    cout << "\nMaximum number of chocolates sold: " << maxflow << "\n\n";
    printAssignments(adj,flow,n,3,3);
    // Min-cut (Optional)
    vector<int> set_s = find_min_cut(adj, capacity, flow, s, n);
    cout << "Min-Cut (Reachable from Source): ";
    for (int u : set_s)
        cout << u << " ";
    cout << "\nMin-Cut T set (Remaining): ";
    for (int i = 0; i < n; i++)
    {
        if (find(set_s.begin(), set_s.end(), i) == set_s.end())
            cout << i << " ";
    }
    cout << endl;

    return 0;
}
