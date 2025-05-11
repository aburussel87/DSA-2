#include<bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    int getDistance(vector<int> &p1, vector<int> &p2){
        return abs(p1[0]-p2[0]) + abs(p1[1] - p2[1]);
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> inMST(n);
        vector<int> key(n);
        for(int i = 0; i<n; i++){
            inMST[i] = false, key[i] = INT_MAX;
        }
        priority_queue<pair<int,int>,vector<pair<int,int>> , greater<pair<int,int>>> pq;
        pq.push({0,0});
        key[0] = 0;
        int total = 0;
        while (!pq.empty())
        {
            int u = pq.top().second;
            if(inMST[u]){
                pq.pop();
                continue;
            }
            total += pq.top().first;
            pq.pop();
            inMST[u] = true;
            for(int v = 0; v<n; v++){
                if(!inMST[v]){
                    int newCost = getDistance(points[u],points[v]);
                    if(newCost<key[v]){
                        key[v] = newCost;
                        pq.push({newCost,v});
                    }
                }
            }
        }
        return total;
        
    }
};


