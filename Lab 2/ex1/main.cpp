#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define INF 9999
ifstream fin("graf.txt");

struct vectors {
    vector<int> l;
    vector<int> p;
};

vectors moore(int n,int vf[][101],int node) {
    vector<int> l(n+1,0);
    vector<int> p(n+1,0);
    for (int i=1;i<=n;++i) {
        if (i!=node) {
            l[i]=INF;
        }
    }
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int x=q.front();
        q.pop();
        for (int i=1;i<=n;++i) {
            if (i!=node && vf[x][i]==1) {
                if (l[i]>=INF) {
                    l[i]=l[x]+1;
                    p[i]=x;
                    q.push(i);
                }
            }
        }
    }
    vectors rez;
    rez.l=l;
    rez.p=p;
    return rez;
}

vector<int> moore_path(vectors v, int node) {
    int k=v.l[node];
    if (k==INF) {
        cout<<"No path found!";
        return {};
    }
    vector<int> path(k+1,0);
    path[k]=node;
    while (k) {
        path[k-1]=v.p[path[k]];
        k--;
    }
    return path;
}

int main() {
    int n;
    int target;
    int source;
    cout<<"Enter source node: ";
    cin>>source;
    cout<<"Enter target node: ";
    cin>>target;
    fin>>n;
    int a[101][101]={0};
    int i,j;
    while (fin>>i>>j) {
        a[i][j]=1;
    }
    vectors v=moore(n,a,source);
    vector<int> path=moore_path(v,target);
    for (i=0;i<path.size();++i) {
        if (path[i]!=0) {
           cout<<path[i]<<" ";
        }
    }
    return 0;
}