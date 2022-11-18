#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#define INF 1000005
#define dim 100001
using namespace std;

ifstream in("bfs.in");
ofstream out("bfs.out");

vector <int> graf[dim];
queue <int> q;
int d[dim];

int n, m;

void bfs(int s) {
    int x, y;
    for(int i=1; i<=n;i++) {
        d[i]=INF;
    }
    d[s]=0;
    q.push(s); // inseram in coada nodul de start
    
    while(!q.empty()) {
        // extrag nodul de la inceputul cozii
        x = q.front();
        q.pop(); // si elimin nodul

        // ma uit la vecinii lui x
        for (int i = 0; i < graf[x].size(); i++) {
            y = graf[x][i];

            if (d[y] > d[x] + 1) {
                d[y] = d[x] + 1; // fac update in vectorul d
                q.push(y);
            }
        }
    }
}


int main()
{
    int s, x, y;
    in >> n >> m >> s;

    for(int i=0; i < m; i++){
        in >> x >> y;
        //adaug in lista nodlui x pe y nu invesr pt ca e orientat
        graf[x].push_back(y);
    }

    bfs(s);
   
    for (int i = 1; i <= n; i++) {
        if (d[i] == INF) {
            d[i] = -1;
        }
        out << d[i] << " ";
    }
    out << '\n';

    return 0;
}