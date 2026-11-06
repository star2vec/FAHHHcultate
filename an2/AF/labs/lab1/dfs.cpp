#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define NMAX 10001

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
    int n, m, i, x, y, nr;

    cin >> n >> m;
    for (i=1; i<=m; i++) {
        cin >> x >> y;
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
    cout << nr << "\n";
}