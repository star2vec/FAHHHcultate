#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define NMAX 1000001

int viz[NMAX];
vector<int> graf[NMAX];

void dfs(int nod) {
    int i;

    viz[nod] = 1;
    for (i=0; i<graf[nod].size(); i++) {
        if (!viz[graf[nod][i]]) {
            dfs(graf[nod][i]);
        }
    }
}

int main() {
    ifstream fin("berarii2.in");
    ofstream fout("berarii2.out");

    int n, m, i, x, y, nr, p, b;

    fin >> n >> m >> p;
    for (i=1; i<=m; i++) {
        fin >> x >> y;
        graf[y].push_back(x);
    }

    for (i=1; i<=p; i++) {
        fin >> b;
        dfs(b);
    }

    nr=0;
    for (i=1; i<=n; i++) {
        if (!viz[i]) {
            nr++;
        }
    }

    fout << nr << "\n";
    for (i=1; i<=n; i++) {
        if (!viz[i]) {
            fout << i << "\n";
        }
    }
}