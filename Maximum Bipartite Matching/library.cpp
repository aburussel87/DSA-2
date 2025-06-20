/*
Problem Description (Max Flow):

We have a group of students and a collection of books.
- Each student can take multiple books, up to a personal limit (e.g., 3 books total).
- Each book has a limited number of available copies (e.g., 4 copies of Book1).
- A student can take multiple copies of the *same* book if allowed.
- Each student has preferences — they are only willing to take certain books.

Goal:
Maximize the total number of books assigned to students,
while respecting:
  - Each student's total limit on books,
  - The number of available copies per book,
  - Student preferences.

Flow Network Construction:
1. Add a source node 'S' and a sink node 'T'.
2. Create a node for each student and each book.
3. Add an edge from S to each student with capacity = student's book limit.
4. For each student-book preference, add an edge from student to book
   with a large enough capacity (e.g., min(student limit, book copies)).
5. Add an edge from each book to T with capacity = number of available copies.

Run a max flow algorithm (e.g., Edmonds-Karp or Dinic).
The flow from student → book tells how many copies of that book the student gets.
*/
#include "max_flow.h"

int main()
{
    // 3 students (0–2), 3 books (3–5), source=6, sink=7
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

    // Source to students
    add_edge(6, 0, 3); // Student 0 can take up to 3 books
    add_edge(6, 1, 2); // Student 1 can take up to 2 books
    add_edge(6, 2, 2); // Student 2 can take up to 2 books

    // Students to books (based on preferences)
    // Each edge indicates a student's willingness to take multiple copies of a preferred book
    add_edge(0, 3, 3); // Student 0 → Book 0 : can take up to 3 copies of Book 0
    add_edge(0, 4, 3); // Student 0 → Book 1 : can take up to 3 copies of Book 1
    add_edge(1, 3, 2); // Student 1 → Book 0 : can take up to 2 copies of Book 0
    add_edge(1, 5, 2); // Student 1 → Book 2 : can take up to 2 copies of Book 2
    add_edge(2, 4, 2); // Student 2 → Book 1 : can take up to 2 copies of Book 1
    add_edge(2, 5, 2); // Student 2 → Book 2 : can take up to 2 copies of Book 2

    // Books to Sink
    add_edge(3, 7, 4); // Book 0 has 4 copies
    add_edge(4, 7, 2); // Book 1 has 2 copies
    add_edge(5, 7, 3); // Book 2 has 3 copies

    int s = 6, t = 7;
    int maxflow = edmond_karp(adj, capacity, flow, s, t, n);

    cout << "\nMaximum number of books distributed: " << maxflow << "\n\n";
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
