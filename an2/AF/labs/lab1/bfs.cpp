#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 100001

int n, m;
int dist[NMAX];
vector<int> graf[NMAX];

void bfs(int nod) {
    int i;
    queue<int> q;

    for (i=1; i<=n; i++) {
        dist[i] = -1;
    }

    dist[nod] = 0;
    q.push(nod);
    while (!q.empty()) {
        nod = q.front();
        q.pop();
        for (int i=0; i<graf[nod].size(); i++) {
            if (dist[graf[nod][i]] == -1) {
                dist[graf[nod][i]] = dist[nod] + 1;
                q.push(graf[nod][i]);   
            }
        }
    }
}


int main() {
    int i, x, y, nr;

    cin >> n >> m;
    for (i=1; i<=m; i++) {
        cin >> x >> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    bfs(1);
    for (i=1; i<=n; i++) {
        cout << dist[i] << " ";
    }
}