#include<bits/stdc++.h>
using namespace std;


struct edge{
    int u,v,w;
    edge(int x, int y, int z){
        u = x,v = y, w = z;
    }
};

bool comparator(const edge& a, const edge& b){
    return a.w < b.w;
}


class kruskal{
    int v;
    vector<int> parent;
    vector<edge> edges;
    public:
    kruskal(int v, vector<edge> &edges){
        this->v = v;
        this->edges = edges;
        parent.assign(v,-1);
        sort(this->edges.begin(),this->edges.end(),comparator);
    }

    void make_set(){
        for(int u = 0; u<v; u++)
            parent[u] = u;
    }

    int find_set(int u){
        if(parent[u] == u){
            return u;
        }
        return parent[u] = find_set(parent[u]);
    }

    bool make_union(int u, int v){
        int p_u = find_set(u);
        int p_v = find_set(v);
        if(p_u == p_v){
            return false;
        }
        parent[p_u] = p_v;
        return true;
    }

    vector<edge> buildMST(){
        vector<edge> inMST;
        make_set();
        for(auto &edge: edges){
            if(make_union(edge.u,edge.v)){
                inMST.push_back(edge);
            }
        }
        return inMST;
    }
};

int main() {
    int v = 6;
    vector<edge> edges = {
        edge(0, 1, 4),
        edge(0, 2, 4),
        edge(1, 2, 2),
        edge(1, 3, 5),
        edge(2, 3, 5),
        edge(2, 4, 11),
        edge(3, 4, 2),
        edge(3, 5, 6),
        edge(4, 5, 1)
    };

    kruskal k(v, edges);
    vector<edge> mst = k.buildMST();

    cout << "Edges in MST:\n";
    int totalWeight = 0;
    for(auto &e : mst){
        cout << e.u << " -- " << e.v << " : " << e.w << "\n";
        totalWeight += e.w;
    }
    cout << "Total weight: " << totalWeight << "\n";

    return 0;
}
