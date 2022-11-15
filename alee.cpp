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

int d[dim][dim];
int n;

queue <elem> q;

const int d_lin[4] = {-1, 1, 0, 0};
const int d_col[4] = {0, 0, -1, 1};

bool valid(elem node) {
    if(node.lin >= 1 && node.lin <=n && node.col >= 1 && node.col <= n) {
        return true;
    }
    return false;
}

int main()
{
    /*
        q: 1 2 3 
        insert(4) - inserare la finalul cozii
        q: 1 2 3 4

        q.pop() - eliminare element de la inceputul cozii
        q: 2 3 4
    */

   /*
        Algoritmul lui Lee - BFS

        Se da:
        - o pozitie de start de unde vreau sa plec
        - o pozitie de finish unde vreau sa ajung
        - pozitii (x, y), reprezentand obstacole (unde nu am voie sa merg)

        Se cere:
        - distanta minima de la pozitia de start la pozitia de finish
        - drumu de la pozitia de start la pozitia de finish
        
        input

        8 6
        2 7
        3 3
        4 6
        5 4
        7 3
        7 5
        1 1 8 8

        N = 8 - dimensiune matrice
        x_start = 1
        y_start = 1

        x_finish = 8
        y_finish = 8
        
        d
        0  1 2 3 4 5 6 7 
        1 2  3 4 5 6 -1 8
        2 3 -1 5 6 7  8  9
        3  4 5 6 7 -1 9 10
        4 5  6 -1 8 9 10 11
        5 6  7 8  9 10 11 12
        6 7 -1 9 -1 11 12 13
        7 8 9  10 11 12 13 14

        Eu sunt in celula (i, j) si ma uit la veinul (x, y)
            - daca d[x][y] > d[i][j] + 1
                - fac update (d[x][y] = 1 + d[i][j])

        d[i][j] = distanta minima de la punctul de start la celula (i, j)
        d[1][1] = 0 (pozitie de start)
        d[i][j] = -1, unde (i, j) sunt celule in care nu putem ajunge
        raspunsul: d[x_finish][y_finish] + 1
        
        - ne folosim de o coada in care punem celulele pe care o sa le vizitam

        q: (1, 1)
        - extrag primul element din coada (q.pop())
            x = (3, 1)
        - parcurg veinii elementului extras din coada (x)
        - adaug in coada veinii a caror distanta a devenit mai mica
            -> q: (3, 1); (1, 4); (2, 3); (3, 2)
        - se repeta pana cand coada devine nula
   */
    
    /*
        n = 4
        0 INF INF INF
        INF INF INF INF
        INF INF INF INF
        INF INF INF INF
        INF = n * n + 1
    */

    int m,x,y,i,j;
    elem start, finish;

    in >> n >> m;
    // initializare matrice cu INF
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            d[i][j] = INF;
        }
    }
    
    for(i = 0; i < m; i++) {
        in >> x >> y;
        d[x][y] = -1; // obstacol
    } 
    in >> start.lin >> start.col >> finish.lin >> finish.col;
    
    // update la pozitia de start (start.lin, start.col)
    cout << start.lin << " " << start.col << '\n';
    d[start.lin][start.col] = 0;
    // inserare in coada primul element
    q.push(start);
    
    while(!q.empty()) {
        // extrag primul element din coada
        elem node = q.front(); // ia primul element
        q.pop(); // scoate primul element

        // parcurg veinii elementului extras din coada (node)
        // care este linia elementului extras? node.lin
        // care este coloana elementului extras? node.col

        // N (node.lin-1 , node.col)
        // S (node.lin+1 , node.col)
        // V (node.lin , node.col-1)
        // E (node.lin , node.col+1)

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
                q.push(neighbour);
            }
        }
    }
     for(i = 1; i <= n; i++) {
         for (j = 1; j <= n; j++) {
             out << d[i][j] << " ";
         }
         out << '\n';
     }

    out << d[finish.lin][finish.col] + 1 << '\n';

    return 0;
}
