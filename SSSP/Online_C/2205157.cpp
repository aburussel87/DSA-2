#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
 
using namespace std;
 
class Edge {
public:
    int dest, weight;
    Edge(int d, int w) : dest(d), weight(w) {}
};
 
vector<int> dijkstra(int V, vector<vector<Edge>> &adjList, int start) {
    vector<int> cost(V, INT_MAX);
    cost[start] = 0;
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));
 
    while (!pq.empty()) {
        pair<int, int> x = pq.top(); pq.pop();
        int d = x.first;
        int u = x.second;
        if (d > cost[u]) continue;
 
        for (int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i].dest;
            int w = adjList[u][i].weight;
            if (cost[u] + w < cost[v]) {
                cost[v] = cost[u] + w;
                pq.push(make_pair(cost[v], v));
            }
        }
    }
    return cost;
}
 
int main() {
    freopen("4.txt", "r", stdin);
 
    int N, M, F;
    cin >> N >> M >> F;
 
    vector<int> capacity(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        capacity[i] = x;
    }
 
    vector<vector<Edge>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back(Edge(v - 1, w));
        graph[v - 1].push_back(Edge(u - 1, w));
    }
 
    int K;
    cin >> K;
 
    vector<int> distances = dijkstra(N, graph, 0);
 
    vector<pair<int, int>> labs;
    for (int i = 0; i < N; i++) {
        labs.push_back(make_pair(distances[i] + F, i));
    }
 
    sort(labs.begin(), labs.end());
 
    vector<int> result;
    for (int i = 0; i < K; i++) {
        bool assigned = false;
        for (int j = 0; j < labs.size(); j++) {
            int cost = labs[j].first;
            int lab = labs[j].second;
            if (capacity[lab] > 0) {
                result.push_back(cost);
                capacity[lab]--;
                assigned = true;
                break;
            }
        }
        if (!assigned) {
            result.push_back(-1);
        }
    }
 
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
 
    return 0;
}