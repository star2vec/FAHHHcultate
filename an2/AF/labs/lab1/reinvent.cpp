#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 100002

int cul[NMAX];
int timp, n, m, x, mini;
vector<int> graf[NMAX];
int casa[NMAX];
queue<int> q;


void bfs() {
    int i, nod;
  
    for (i=1; i<=n; i++) {
        cul[i] = -1;
    }
    for (i=1; i<=x; i++) {
        q.push(casa[i]);
        cul[casa[i]] = 0;
    }

    mini = -1;
    timp = 0;
    while (timp < n && mini == -1) {
        timp++;
        for (i=1; i<=x; i++) {
            if (!q.empty()) {
                nod = q.front();
                q.pop();
                for (int j=0; j<graf[nod].size(); j++) {
                    if (cul[graf[nod][j]] == -1) {
                        cul[graf[nod][j]] = cul[nod] + 1;
                        q.push(graf[nod][j]);
                    } else {
                        if (mini == -1) {
                            mini = cul[graf[nod][j]] + cul[nod] + 1;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ifstream fin("reinvent.in");
    ofstream fout("reinvent.out");

    int i, a, b, nr;

    fin >> n >> m >> x;
    for (i=1; i<=m; i++) {
        fin >> a >> b;
        graf[b].push_back(a);
        graf[a].push_back(b);
    }

    for (i=1; i<=x; i++) {
        fin >> casa[i];
    }

    timp = 0;
    bfs();

    fout << mini << "\n";

    for (i=1; i<=n; i++) {
        fout << cul[i] << " ";
    }
}