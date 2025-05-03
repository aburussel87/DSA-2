#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define INF std::numeric_limits<int>::max()

using namespace std;

int Min_Distance(const vector<int>& dist, const vector<bool>& visited) {
    int min = INF, min_index;
    for (int v = 0; v < dist.size(); ++v) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void Dijkstra_Algorithm(const vector<vector<int>>& graph, const vector<vector<int>>& altered_graph, int source) {
    int V = graph.size();
    vector<int> dist(V, INF);
    vector<bool> visited(V, false);
    dist[source] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = Min_Distance(dist, visited);
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF && dist[u] + altered_graph[u][v] < dist[v]) {
                dist[v] = dist[u] + altered_graph[u][v];
            }
        }
    }

    cout << "Shortest Distance from vertex " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
    }
}

vector<int> BellmanFord_Algorithm(const vector<vector<int>>& edges, int V) {
    vector<int> dist(V + 1, INF);
    dist[V] = 0;
    vector<vector<int>> edges_with_extra(edges);
    for (int i = 0; i < V; ++i) {
        edges_with_extra.push_back({V, i, 0});
    }
    for (int i = 0; i < V; ++i) {
        for (const auto& edge : edges_with_extra) {
            if (dist[edge[0]] != INF && dist[edge[0]] + edge[2] < dist[edge[1]]) {
                dist[edge[1]] = dist[edge[0]] + edge[2];
            }
        }
    }
    return vector<int>(dist.begin(), dist.begin() + V);
}

void JohnsonAlgorithm(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> edges;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] != 0) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }

    vector<int> altered_weights = BellmanFord_Algorithm(edges, V);
    vector<vector<int>> altered_graph(V, vector<int>(V, 0));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] != 0) {
                altered_graph[i][j] = graph[i][j] + altered_weights[i] - altered_weights[j];
            }
        }
    }

    cout << "Modified Graph:\n";
    for (const auto& row : altered_graph) {
        for (int weight : row) {
            cout << weight << ' ';
        }
        cout << endl;
    }

    for (int source = 0; source < V; ++source) {
        cout << "\nShortest Distance with vertex " << source << " as the source:\n";
        Dijkstra_Algorithm(graph, altered_graph, source);
    }
}

int main() {
    vector<vector<int>> graph = {
        {0, -5, 2, 3},
        {0, 0, 4, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };

    JohnsonAlgorithm(graph);
    return 0;
}
