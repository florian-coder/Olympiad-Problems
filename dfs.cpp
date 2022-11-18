#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#define INF 1000005
#define dim 100001
using namespace std;

ifstream in("dfs.in");
ofstream out("dfs.out");

vector <int> graf[dim];

int n, m;
bool visited[dim];
void dfs(int s) {
    visited[s]=true;
    for(int i=0;i<graf[s].size();i++) {
        int y = graf[s][i];
        if(visited[y]==false)
            dfs(y);
    }
}


int main()
{
    int x,y;
    in>>n>>m;
    int nr=0;
    for(int i=1;i<=m;i++){
        in>>x>>y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        if(visited[i]==false){
            dfs(i);
            nr++;
        }
    }
    out<<nr;
    return 0;
}