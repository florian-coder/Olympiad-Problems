#include <iostream>
#include <queue>
using namespace std;

const int Nmax = 101;
const int INF = Nmax * Nmax;

bool A[Nmax][Nmax];

struct elem {
    int lin;
    int col;
};

queue <elem> q;
int d[Nmax][Nmax];

int dlin[4] = {-1, 0, 1, 0};
int dcol[4] = {0, 1, 0, -1};

int N;

bool valid(elem node) {
    if (node.lin >= 1 && node.lin <= N && node.col >= 1 && node.col <= N) {
        return true;
    }
    return false;
}

void lee(elem s) {
    int i, j;
    elem x;

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            d[i][j] = INF;
        }
    }

    d[s.lin][s.col] = 0; // marchez nodul de start in d cu distanta 0
    q.push(s);

    while (!q.empty()) {
        x = q.front();
        q.pop();

        elem y;
        // parcurg vecinii y ai lui x
        for (int k = 0; k < 4; k++) {
            y.lin = x.lin + dlin[k];
            y.col = x.col + dcol[k];

            if (valid(y) && A[y.lin][y.col] != 1 && d[y.lin][y.col] > 1 + d[x.lin][x.col]) {
                d[y.lin][y.col] = 1 + d[x.lin][x.col];
                q.push(y);
            }
        }
    }
}

int main()
{  
    int i, j, x1, y1, x2, y2, x3, y3;

    cin >> N; // dimensiune matrice
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            cin >> A[i][j];
        }
    }

    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    elem s;
    s.lin = 1;
    s.col = 1;
    lee(s);

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            if (d[i][j] == INF) {
                d[i][j] = -1;
            }
            cout << d[i][j] << " ";
        }
        cout << '\n';
    }

    cout << d[N][N] << '\n';

    

    return 0;
}