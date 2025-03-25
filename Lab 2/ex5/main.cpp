#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
void dfs_visit(vector<vector<int>> graf,int i,vector<int>& parent, vector<string>& color,vector<int>& distance, int& time);
void dfs(vector<vector<int>> graf,int s) {
    int n=graf.size();
    vector<int> parent(graf.size(), -1);
    vector<string> color(graf.size(), "white");
    vector<int> distance(n,-1);
    int time=0;
    dfs_visit(graf,s,parent,color,distance,time);
}

void dfs_visit(vector<vector<int>> graf,int i,vector<int>& parent, vector<string>& color,vector<int>& distance, int& time) {
    cout<<i<<" ";
    time++;
    color[i]="gray";
    distance[i]=time;
    for (int j=0;j<graf.size();++j) {
        if (graf[i][j]==1 && color[j]=="white") {
            parent[j]=i;
            dfs_visit(graf, j, parent, color, distance, time);
        }
    }
    color[i]="black";
    time++;
    distance[i]=time;
}

int main() {
    ifstream fin("graf.txt");
    int n;
    fin>>n;
    vector<vector<int>> graf(n, vector<int>(n));
    int i,j;
    while(fin>>i>>j) {
        graf[i][j]=1;
    }
    fin.close();
    int s;
    cout<<"Enter source: ";
    cin>>s;
    dfs(graf,s);

    return 0;
}