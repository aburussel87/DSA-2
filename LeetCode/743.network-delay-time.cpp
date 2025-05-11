#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        unordered_map<int, vector<pii>> graph;
        for (auto& time : times) {
            graph[time[0]].push_back({time[1], time[2]});
        }
        
        vector<int> dist(N + 1, INT_MAX);
        dist[K] = 0;
        
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, K});
        
        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            if (currentDist > dist[node]) {
                continue;
            }
            
            for (auto& neighbor : graph[node]) {
                int neighborNode = neighbor.first;
                int weight = neighbor.second;
                int newDist = currentDist + weight;
                
                if (newDist < dist[neighborNode]) {
                    dist[neighborNode] = newDist;
                    pq.push({newDist, neighborNode});
                }
            }
        }
        
        int maxDist = 0;
        for (int i = 1; i <= N; ++i) {
            if (dist[i] == INT_MAX) {
                return -1;
            }
            maxDist = max(maxDist, dist[i]);
        }
        
        return maxDist;
    }
};

