#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#define INF 9999
using namespace std;

void bfs(vector<vector<int>> graf,int source) {
    int n=graf.size();
    vector<int> res;
    queue<int> q;
    vector<int> distance(n,INF);
    vector<int> parent(n,-1);
    vector<string> color(n,"white");
    color[source]="gray";
    distance[source]=0;
    q.push(source);
    while (!q.empty()) {
        int node=q.front();
        q.pop();
        res.push_back(node);
        for (int i=0;i<n;++i) {
            if (graf[node][i]==1 && color[i]=="white") {
                color[i]="gray";
                distance[i]=distance[node]+1;
                parent[i]=node;
                q.push(i);
            }
        }
        color[node]="black";
    }
    n=res.size();
    for (int i=0;i<n;++i) {
        cout<<res[i]<<" "<<distance[res[i]]<<endl;
    }
}

int main() {
    ifstream fin("graf.txt");
    int n;
    fin >> n;
    vector<vector<int>> graf(n, vector<int>(n));
    int i,j;
    while (fin>>i>>j) {
        graf[i][j]=1;
    }
    bfs(graf,0);
    return 0;
}