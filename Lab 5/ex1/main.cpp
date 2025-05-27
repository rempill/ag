#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>

using namespace std;
//Ford-Fulkerson algorithm
bool BFS(vector<vector<int>>& Graph, int s, int t, vector<int>& parent) {
    int V = Graph.size();
    vector visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && Graph[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    return visited[t];
}

int Ford_Fulkerson(vector<vector<int>>& G, int s, int t) {
    int V = G.size();
    vector<vector<int>> rG = G;
    vector<vector<int>> f(V, vector<int>(V, 0)); // fluxul inițializat cu 0

    vector<int> parent(V);
    int maxFlow = 0;

    // cat timp exista un drum s->t in Gf
    while (BFS(rG, s, t, parent)) {
        int cf_p = INT_MAX; // capacitatea minima pe drum

        // aflam cf(p)
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            cf_p = std::min(cf_p, rG[u][v]);
        }

        // actualizare fluxuri
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (G[u][v] > 0) {
                f[u][v] += cf_p;
            } else {
                f[v][u] -= cf_p;
            }
            rG[u][v] -= cf_p;
            rG[v][u] += cf_p;
        }
        maxFlow += cf_p;
    }

    return maxFlow;
}


//input:
// 5 6
// 0 1 5
// 0 3 5
// 0 2 10
// 1 4 11
// 2 3 2
// 3 4 8
int main() {
    vector<vector<int>> G;
    ifstream fin("input.txt");
    int n, m;
    fin >> n >> m;
    G.resize(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v, c;
        fin >> u >> v >> c;
        G[u][v] = c; // capacitatea de la u la v
    }
    fin.close();
    int s = 0; // sursa
    int t = n - 1; // destinatia
    int maxFlow = Ford_Fulkerson(G, s, t);
    cout << "Max Flow: " << maxFlow << endl;
    return 0;
}