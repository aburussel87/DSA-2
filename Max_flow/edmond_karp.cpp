#include<bits/stdc++.h>

int bfs(vector<vector<int>> &adj, vector<vector<int>> &capacity, vector<vector<int>> &flow, vector<int> &parent,int s, int t){
    fill(parent.begin(),parent.end(),-1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s,INT_MAX});
    while(!q.empty()){
        int u = q.front().first;
        int curr_flow = q.front().second;
        q.pop();
        for(int v : adj[u]){
            if(parent[v] == -1 && capacity[u][v]-flow[u][v] > 0){
                parent[v] = u;
                int newflow = min(curr_flow,capacity[u][v] - flow[u][v]);
                if(v == t) return newflow;
                q.push({v,newflow});
            }
        }
    }
    return 0;
}

int edmond_karp(vector<vector<int>> &adj, vector<vector<int>> &capacity, vector<vector<int>> &flow,int s, int t, int n){
    int maxflow = 0;
    int newflow;
    vector<int> parent(n);
    while((newflow = bfs(adj,capacity,flow,parent,s,t))){
        maxflow += newflow;
        int v = t;
        while ( v != s ){
            int u  = parent[v];
            flow[u][v] += newflow;
            flow[v][u] -= newflow;
            v = u;
        }
    }

    for(int i=0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(flow[i][j] <= 0) continue;
            cout<<i<<"-->"<<j<<": "<<flow[i][j]<<endl;
        }
    }

    return maxflow;
}

vector<int> find_min_cut(vector<vector<int>> &adj, vector<vector<int>> &capacity, vector<vector<int>> &flow,int s,int n){
    vector<int> set_s;
    vector<bool> visited(n,false);

    queue<int> q;
    q.push(s);
    set_s.push_back(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        visited[u] = true;
        for(int v : adj[u]){
            if(!visited[v] && (capacity[u][v]-flow[u][v] > 0)){
                visited[v] = true;
                set_s.push_back(v);
            }
        }
    }
    return set_s;
}


int main(){
    freopen("edmond.txt","r",stdin);
    int m,n;
    cin>>n>>m;
    vector<vector<int>> capacity(n,vector<int> (n,0));
    vector<vector<int>> flow(n,vector<int> (n,0));
    vector<vector<int>> adj(n);
    for(int i = 0;i<m; i++){
        int u,v,cap;
        cin>>u>>v>>cap;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    }

    int s,t;
    cin>>s>>t;
    
    int maxflow = edmond_karp(adj,capacity,flow,s,t,n);
    cout<<"maxflow of the network is : "<<maxflow<<endl;
    vector<int> set_s = find_min_cut(adj,capacity,flow,s,n);
    cout<<"Set S contains: ";
    for(int i= 0; i<set_s.size(); i++){
        cout<<set_s[i]<<"  ";
    }
    cout<<endl<<"set T contains: ";
    for(int i = 0; i<n; i++){
        auto it = find(set_s.begin(),set_s.end(),i);
        if(it != set_s.end()) continue;
        cout<<i<<"  ";
    }
    cout<<endl;
    return 0;
}