#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define INF 9999
ifstream fin("graf.txt");

vector<int> moore(int n,int vf[][101],int node) {
    vector<int> l(n+1,0);
    for (int i=0;i<n;++i) {
        if (i!=node) {
            l[i]=INF;
        }
    }
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int x=q.front();
        q.pop();
        for (int i=0;i<n;++i) {
            if (i!=node && vf[x][i]==1) {
                if (l[i]>=INF) {
                    l[i]=l[x]+1;
                    q.push(i);
                }
            }
        }
    }
    return l;
}

int main() {
    int n;
    fin>>n;
    int a[101][101]={0};
    int i,j;
    while (fin>>i>>j) {
        a[i][j]=1;
    }
    for (i=0;i<n;++i) {
        a[i][i]=1;
        for (j=0;j<n;++j) {
            vector<int> l=moore(n,a,i);
            if (l[j]!=INF) {
                a[i][j]=1;
            }
        }
    }
    for (i=0;i<n;++i) {
        for (j=0;j<n;++j) {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}