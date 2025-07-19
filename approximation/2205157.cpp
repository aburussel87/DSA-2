#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<pair<int,int>> edges;

bool is_vertex_cover(const vector<int>& subset) {
    set<int> cover(subset.begin(), subset.end());
    for (const auto& e : edges) {
        if (cover.count(e.first) == 0 && cover.count(e.second) == 0) {
            return false;
        }
    }
    return true;
}

vector<int> exact_vertex_cover() {
    vector<int> best_cover;
    for (int k = 1; k <= n; ++k) {
        vector<int> vertices(n);
        iota(vertices.begin(), vertices.end(), 0);
        vector<bool> mask(n, false);
        fill(mask.begin(), mask.begin() + k, true);

        do {
            vector<int> subset;
            for (int i = 0; i < n; ++i) {
                if (mask[i]) subset.push_back(i);
            }
            if (is_vertex_cover(subset)) {
                best_cover = subset;
                return best_cover;
            }
        } while (prev_permutation(mask.begin(), mask.end()));
    }
    return best_cover;
}

vector<int> approx_vertex_cover() {
    vector<int> cover;
    vector<pair<int,int>> remaining_edges = edges;

    while (!remaining_edges.empty()) {
        auto e = remaining_edges.back(); remaining_edges.pop_back();
        int u = e.first, v = e.second;

        cover.push_back(u);
        cover.push_back(v);

        auto it = remaining_edges.begin();
        while (it != remaining_edges.end()) {
            if (it->first == u || it->second == u || it->first == v || it->second == v) {
                it = remaining_edges.erase(it);
            } else {
                ++it;
            }
        }
    }
    sort(cover.begin(), cover.end());
    cover.erase(unique(cover.begin(), cover.end()), cover.end());
    return cover;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }

    vector<int> exact = exact_vertex_cover();
    cout << "Exact Minimum Vertex Cover Size: " << exact.size() << endl;
    cout << "Vertices:";
    for (int v : exact) cout << " " << v;
    cout << endl;

    vector<int> approx = approx_vertex_cover();
    cout << "Approximate Vertex Cover Size: " << approx.size() << endl;
    cout << "Vertices:";
    for (int v : approx) cout << " " << v;
    cout << endl << "Approximation Ratio: "<< approx.size()/exact.size()<<endl;

    return 0;
}