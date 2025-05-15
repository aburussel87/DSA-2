#include<bits/stdc++.h>
using namespace std;

class edge{
    public:
    int u,v,w;
    edge(int x, int y, int z){
        u = x, v = y, w = z;
    }
};

bool comparator(const edge &a,const edge &b){
    return a.w<b.w;
}

void sortEdge(vector<edge> &edges){
    sort(edges.begin(),edges.end(),comparator);
}
void printMST(vector<edge> &inMST){
    for(auto &edge: inMST){
        cout<< edge.u << "--->" <<edge.v <<" with weight: "<<edge.w<<endl;
    }
}

void kruskal(vector<edge> &edges, int v){
    vector<int> key(v);
    vector<edge> inMst;
    for(int i = 0; i<v; i++) key[i] = i;
    for(auto &edge:edges){
        if( key[edge.u] != key[edge.v] ){
            inMst.push_back(edge);
            int y = key[edge.v];
            for(int i = 0; i<v;i++){
                if(key[i] == y) key[i] = key[edge.u];
            }
        }
    }
    printMST(inMst);
}

int main() {
    int v = 6; 
    vector<edge> edges;

    edges.push_back(edge(0, 1, 4));
    edges.push_back(edge(0, 2, 4));
    edges.push_back(edge(1, 2, 2));
    edges.push_back(edge(1, 3, 5));
    edges.push_back(edge(2, 3, 5));
    edges.push_back(edge(2, 4, 11));
    edges.push_back(edge(3, 4, 2));
    edges.push_back(edge(3, 5, 6));
    edges.push_back(edge(4, 5, 1));

    sortEdge(edges);
    kruskal(edges, v);

    return 0;
}
