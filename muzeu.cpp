#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
 
#define dmax 251
 
ifstream in("muzeu.in");
ofstream out("muzeu.out");
 
// vectori de deplasare (pentru vecini)
const int d_lin[4] = {-1, 0, 1, 0};
const int d_col[4] = {0, 1, 0, -1};
 
int A[dmax][dmax];
int N;
 
struct Elem {
    int x;
    int y;
};
 
queue <Elem> q;
 
bool valid(Elem node) {
    if(node.x >= 0 && node.x < N && node.y >= 0 && node.y < N) {
        return true;
    }
 
    return false;
}
 
int main()
{
    /*
        8
        ...#....
        #..#..#.
        .##.P..#
        ..#.#.#.
        ........
        ........
        ###...##
        ..P.....

        -1 -1 -1 -2  2  3  4  5
        -2 -1 -1 -2  1  2 -2  6
        8 -2 -2  1  0  1  2 -2
        7  6 -2  2 -2  2 -2  6
        6  5  4  3  4  3  4  5
        6  5  4  3  4  4  5  6
        -2 -2 -2  2  3 4 -2 -2
        2  1  0  1  2  3  4  5

        codificare:
        . - loc liber
        # - loc innacesibil
        P - loc paznic (loc de start)
    */
 
    char c;
    int i, j, k;
    Elem start;
 
    in >> N;
 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            in >> c;
            if (c == '#') {
                A[i][j] = -2;
            }
            else if (c == 'P') {
                A[i][j] = 0;
                start.x = i;
                start.y = j;
                q.push(start);
            }
            else if (c == '.') {
                A[i][j] = N * N + 1;
            }
        }
    }
 
    Elem node, vecin;
 
    while(!q.empty()) {
        node = q.front();
 
        
        for (k = 0; k < 4; k++) {
            vecin.x = node.x + d_lin[k];
            vecin.y = node.y + d_col[k];
 
            if (valid(vecin) && A[vecin.x][vecin.y] > 1 + A[node.x][node.y]) {
                A[vecin.x][vecin.y] = 1 + A[node.x][node.y];
                q.push(vecin);
            }
        }
 
        q.pop();
    }
 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (A[i][j] == N * N + 1) {
                A[i][j] = -1;
            }
        }
    }
 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            out << A[i][j] << " ";
        }
        out << '\n';
    }
 
    return 0;
}