#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream in("input.txt");
struct Muchie{
    int nod1,nod2,cost;
};
Muchie v[400005],ans[400005];
bool compare(Muchie a, Muchie b){
    if(a.cost<b.cost)
        return true;
    if(a.cost==b.cost && a.nod1<b.nod1)
        return true;
    return false;
}
int parent[200005];
//fct pt gasirea radacinii unui nod
int find_root(int x)
{
    if(parent[x]==x)
        return x;
    return parent[x]=find_root(parent[x]);
}
//fct pt unirea a doua noduri
void unite(int x, int y)
{
    parent[find_root(x)]=find_root(y);
}

int main()
{
    int n,m,rez=0,costmin=0,i;
    in>>n>>m;
    // citim muchiile
    for(i=1;i<=m;++i)
        in>>v[i].nod1>>v[i].nod2>>v[i].cost;
    // inițializăm vectorul de părinți
    for(i=1;i<=n;++i)
        parent[i]=i;

    // sortăm muchiile după cost, crescător
    sort(v+1,v+m+1,compare);

    // parcurgem muchiile sortate
    for(i=1;i<=m && rez<n-1;++i)
        // adăugăm muchia dacă nu formează ciclu (nodurile sunt în mulțimi diferite)
            if(find_root(v[i].nod1)!=find_root(v[i].nod2)){
                ++rez;                      // contor muchii adăugate
                ans[rez]=v[i];              // salvăm muchia în ans
                costmin+=v[i].cost;         // adăugăm costul muchiei la costul minim
                unite(find_root(v[i].nod1),find_root(v[i].nod2)); // unim mulțimile relative nodurilor
            }
    cout<<costmin<<'\n'<<n-1<<'\n';
    for(i=1;i<=n-1;++i)
        cout<<ans[i].nod1<<" "<<ans[i].nod2<<'\n';
    return 0;
}
