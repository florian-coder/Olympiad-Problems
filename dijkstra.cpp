#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#define Nmax 50005
#define INF INT_MAX - 1
using namespace std;
ifstream in("dijkstra.in");
ofstream out("dijkstra.out");

vector <pair<int, int>> graf[Nmax];
/*
    Liste de vecini 
    
    nod x: (vecin y1, cost arc x-y1), (vecin y2 cost arc x-y2)

    1: (2, 1), (4, 2)
    2: (3, 2)
    3: (5, 6)
    4: (3, 4), (5,3)
    5: 
*/

int n, m;

int d[Nmax];
bool visited[Nmax];
priority_queue <pair<int, int>> H;

void dj(int s) {
    // inserez in heap perechea (0- dist, nodul_sursa)
    H.push({0, s});
    d[s] = 0;
    int x,y,c;
    while(!H.empty()) {

        while (!H.empty() && visited[H.top().second] == true) {
            H.pop();
        }
        if(H.empty()){
            break;
        }
        x = H.top().second;
        visited[x] = true;
        // parcurgem vecinii y ai lui x
        for (int i = 0; i < graf[x].size();i++){
            y = graf[x][i].first;
            c = graf[x][i].second;
            if(d[y] > d[x] + c){
                d[y] = d[x] + c;
                H.push({-d[y], y });
            }
        }
    }
}

int main()
{
    int x, y, c;
    
    in>>n>>m;
    for(int i=1; i<=m; i++){
        in >> x >> y >> c;
        graf[x].push_back({y, c});
    }

    // afisare lista de vecini
    /*
    for (int i = 1; i <= n; i++) {
        out << i << ": ";

        for (int j = 0; j < graf[i].size(); j++) {
            y = graf[i][j].first;
            c = graf[i][j].second;

            out << "(" << y << ", " << c << ") ";
        }
        out << '\n';
    }
    */
    
    for (int i = 1; i <= n; i++) {
        d[i] = INF;
    }

    dj(1);

    for (int i = 2; i <= n; i++) {
        if(d[i] == INF) {
            d[i] = 0;
        }
        out << d[i] << " ";
    }
    

    return 0;

}