#include <iostream>
#include <fstream>
#include <queue>
#define dim 176
#define INF 175*175+1
using namespace std;
ifstream in("alee.in");
ofstream out("alee.out");
struct elem {
    int lin;
    int col;
};
elem camere[INF];
int d[dim][dim];
int u[dim][dim];
int n,ops;

queue <elem> q;

const int d_lin[4] = {-1, 1, 0, 0};
const int d_col[4] = {0, 0, -1, 1};

bool valid(elem node) {
    if(node.lin >= 1 && node.lin <=n && node.col >= 1 && node.col <= ops) {
        return true;
    }
    return false;
}

int main()
{


    int m,x,y,i,j;
    elem start, finish;

    in >> n >>ops>> m;
    // initializare matrice cu INF
     for(i = 1; i <= n; i++) {
        for(j = 1; j <= ops; j++) {
            d[i][j] = INF;
        }
    }
     for(i = 1; i <= n; i++) {
        for(j = 1; j <= ops; j++) {
            u[i][j] = 0;
        }
    }
    for(i = 0; i < m; i++) {
        in >> camere[i].lin>>camere[i].col;
        u[camere[i].lin][camere[i].col]++;
    } 

    start.lin=1;
    start.col=1;
    d[start.lin][start.col] = 0;
    
    q.push(start);
    int save;
    while(!q.empty()) {
        
        elem node = q.front(); 
        q.pop(); 

        elem neighbour;
        for (int k = 0; k < 4; k++) {
            neighbour.lin = node.lin + d_lin[k];
            neighbour.col = node.col + d_col[k];

            // !!!!
            // valid(neighbour) == true daca 
            // neighbour.lin >= 1 && neighbour.lin <= n && neighbour.col >= 1 && neighbour.col <= n
            if (valid(neighbour) && d[neighbour.lin][neighbour.col] > d[node.lin][node.col] + 1) {
                // fac update in matricea d
                d[neighbour.lin][neighbour.col] = d[node.lin][node.col] + 1;
                // adaug nodul in coada q

                for(j=0;j<m;j++)
            {
                if(camere[j].lin==node.lin&&camere[j].col==node.col)
                {
                    save=u[node.lin][node.col];
                    
                    j=m;
                }
            }

                q.push(neighbour);
            }
            
        }
    }
    out<<save<<"\n";
    /*for(i = 1; i <= n; i++) {
         for (j = 1; j <= ops; j++) {
             out << d[i][j] << " ";
         }
         out << '\n';
     }
    for(i = 1; i <= n; i++) {
         for (j = 1; j <= ops; j++) {
             out << u[i][j] << " ";
         }
         out << '\n';
     }*/
    

    return 0;
}
