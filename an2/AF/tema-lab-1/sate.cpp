#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 30003

int n, m;

vector <int> graf[NMAX];
vector <int> d[NMAX];
int viz[NMAX];
int dist[NMAX];

queue<int> q;

int bfs(int x,  int y) {
    int i, sat, satnou;

    q.push(x);
    dist[x] = 0;
    while (!q.empty() && dist[y]==0) {
        sat = q.front();

        for (i=0; i<graf[sat].size(); i++) {
            satnou = graf[sat][i];

            if (dist[satnou]==0 && satnou!=x) {
                if (satnou > sat) {
                    dist[satnou] = dist[sat] + d[sat][i];
                } else {
                    dist[satnou] = dist[sat] - d[sat][i];
                }
                q.push(satnou);
            }
        }

        q.pop();
    }

    return dist[y];
}

int main() {
    ifstream fin("sate.in");
    ofstream fout("sate.out");
    
    int n, m, x, y, a, b, i, dab;
    
    fin >> n >> m >> x >> y;
    
    for (i=0; i<m; i++) {
        fin >> a >> b >> dab;
        graf[a].push_back(b);
        graf[b].push_back(a);
        d[a].push_back(dab);
        d[b].push_back(dab);
    }

    fout << abs(bfs(x, y));

    /*
    for (i=1; i<=n; i++) {
        cout << dist[i] << " ";
    }
    */
    
    
    fin.close();
    fout.close();
    return 0;
}