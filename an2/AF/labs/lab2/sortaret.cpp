#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 50001

vector<int> graf[NMAX];
int grad[NMAX];

int main() {
    ifstream fin("sortaret.in");
    ofstream fout("sortaret.out");

    int n, m, i, x, y, nod;
    queue<int> q;

    fin >> n >> m;
    for (i=1; i<=m; i++) {
        fin >> x >> y;
        grad[y]++;
        graf[x].push_back(y);
    }

    for (i=1; i<=n; i++) {
        if (grad[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        nod = q.front();
        q.pop();
        fout << nod << " ";
        for (auto vecin : graf[nod]) {
            grad[vecin]--;
            if (grad[vecin] == 0) {
                q.push(vecin);
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}