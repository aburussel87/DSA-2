#include <bits/stdc++.h>
using namespace std;

void prim(vector<vector<pair<int,int>>> &graph, int v, int start){
    vector<bool> inMST(v,false);
    vector<int> parent(v,-1);
    vector<int> key(v,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    key[start] = 0;
    pq.push({0,start});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(inMST[u]) continue;
        inMST[u] = true;
        for(pair<int,int> &neighbor : graph[u]){
            if(!inMST[neighbor.first] && neighbor.second < key[neighbor.first]){
                key[neighbor.first] = neighbor.second;
                pq.push({neighbor.second,neighbor.first});
                parent[neighbor.first] = u;
            }
        }
    }

    int totalWeight = 0;

    for(int i = 0; i<parent.size(); i++){
        if(parent[i] != -1){
            cout<<"parent of "<<i<<" is: "<<parent[i]<<endl;
            totalWeight += key[i];
        }
    }
    cout<<"Total weight: "<<totalWeight<<endl;
    
}

int main(){
    freopen("prims.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> graph(n);
    for(int i = 0; i<m; i++){
        int x,y,z;
        cin>>x>>y>>z;
        graph[x].push_back({y,z});
        graph[y].push_back({x,z});
    }

    prim(graph,n,0);
    return 0;
}