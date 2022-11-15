#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

ifstream in("panda.in");
ofstream out("panda.out");

const int dmax = 505; 
const int INF = dmax * dmax;

struct Elem {
    int lin;
    int col;
};

Elem tarcuri[dmax]; // 1MB
//false = 0
//true = 1
int codes[dmax][dmax]; // 1MB
int n, m, k, s, L, C, T;

bool k_bits[20];
int k_idx;

bool code_bits[20];
int code_idx;

int d[dmax][dmax]; // 1 MB

const int d_lin[4] = {-1, 1, 0, 0};
const int d_col[4] = {0, 0, -1, 1};

queue <Elem> q; // 2MB
 
void k_binary_from_int(int x) {
    while(x) {
        k_bits[k_idx++] = x % 2;
        x /= 2;
    }
    for (int i = k_idx; i < s; i++) {
        k_bits[i] = 0;
    }
}
 
void code_binary_from_int(int x) {
    while(x) {
        code_bits[code_idx++] = x % 2;
        x /= 2;
    }
    for (int i = code_idx; i < s; i++) {
        code_bits[i] = 0;
    }
}

bool complementary() {
    for (int i = 0; i < s; i++) {
        if (code_bits[i] == k_bits[i]) {
            return false;
        }
    }
    return true;
}

void task_1() {
    int i, j, nr = 0;

    k_binary_from_int(k);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            code_idx = 0;
            code_binary_from_int(codes[i][j]);
            // verific daca ultimele s cifre din descompunerea binara a lui k sunt complementare 
            // cu ultimele s cifre din descompunera lui codes[i][j]
            if (complementary() && !(i == L && j == C)) {
                nr++;
            }
        }
    }

    out << nr << '\n';
}

bool valid(Elem node) {
    if(node.lin >= 1 && node.lin <= n && node.col >=1 && node.col <= m) {
        return true;
    }
    return false;
}

void task_2() {
    int i, j;
    k_binary_from_int(k);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            code_idx = 0;
            code_binary_from_int(codes[i][j]);
            d[i][j] = INF;

            if (!complementary()) {
                d[i][j] = -1;
            }            
        }  
    }

    d[L][C] = 0;
    q.push({L, C});

    // for (i = 1; i <= n; i++) {
    //     for (j = 1; j <= m; j++) {
    //         out << d[i][j] << " ";
    //     }
    //     out << '\n';
    // }    
    // out << '\n';

    Elem node;
    while(!q.empty()) {
        node = q.front();
        q.pop();

        // parcurgere vecini
        Elem vecin;
        for (k = 0; k < 4; k++) {
            vecin.lin = node.lin + d_lin[k];
            vecin.col = node.col + d_col[k];

            if(valid(vecin) && d[vecin.lin][vecin.col] > d[node.lin][node.col] + 1) {
                d[vecin.lin][vecin.col] = d[node.lin][node.col] + 1;
                q.push(vecin);
            }
        }
    }

    // for (i = 1; i <= n; i++) {
    //     for (j = 1; j <= m; j++) {
    //         out << d[i][j] << " ";
    //     }
    //     out << '\n';
    // }   

    int mini = INF, nr_mini;
    for(i = 0; i < T; i++) {
        if(valid({tarcuri[i].lin, tarcuri[i].col}) && d[tarcuri[i].lin][tarcuri[i].col] != -1 && d[tarcuri[i].lin][tarcuri[i].col] < mini) {
            mini = d[tarcuri[i].lin][tarcuri[i].col];
            nr_mini = 1;
        } else if (valid({tarcuri[i].lin, tarcuri[i].col}) && d[tarcuri[i].lin][tarcuri[i].col] != -1 && d[tarcuri[i].lin][tarcuri[i].col] == mini) {
            nr_mini++;
        }
    }
    out << mini << " " << nr_mini <<'\n';
}

int main()
{
    /*
        1
        5 6 4
        3 5 1 1
        1 2 
        5 1 
        2 1
        4 3
        15 1278 3 1278 1278 1 
        16 17 ..>  ..0

        p
        // dimensiune matrice
        n = 5
        m = 6
        // nr tarcuri
        T = 4
        // coordonate initial ursulet
        L = 3 
        C = 5

        k = 1 - cod microcip ursulet -> 0000001
        s = 1 - nr de cifre (ultimele) -> complementarul ultimelor s cifre ale lui k: 0

        Cerinta 1:
        19      

        Cerinta 2:
        0 1* 0 1 1 0
        1* 0 1 0 1 1
        0 0 1 1 [1] 1
        0 1 0* 0 1 1
        1* 1 1 1 1 1  

        6 1

        12 / 2 = 6 r 0
        6 / 2 =  3 r 0
        3 / 2 =  1 r 1
        1 / 2 = 0  r 1

        12 = 1100
        1100 = 0 * 2^0 + 0 * 2^1 + 1 * 2^2 + 1 * 2^3 = 2^2 + 2^3 = 4 + 8 = 12

    */

    int p, i, j;
    in >> p; // tip cerinta
    in >> n >> m >> T;
    in >> L >> C >> k >> s;
   
    for(i = 0; i < T; i++) {
        in >> tarcuri[i].lin >> tarcuri[i].col;
    }

    for(i = 1; i <= n; i++) {
        for(j = 1;j <= m; j++) {
            in >> codes[i][j];
        }
    }

    if(p == 1) {
        task_1();
    } else {
        task_2();        
    }
    
    return 0;
}
