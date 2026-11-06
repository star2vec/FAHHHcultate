#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define NMAX 100001

int dist[NMAX];
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
    ifstream fin("grarb.in");
    ofstream fout("grarb.out");

    int n, m, i, x, y, nr;

    fin >> n >> m;
    for (i=1; i<=m; i++) {
        fin >> x >> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    nr = 0;
    for (i=1; i<=n; i++) {
        if (!viz[i]) {
            nr++;
            dfs(i);
        }
    }
    fout << (m+nr-1)-(n-1) << "\n" << nr-1 << "\n";
}