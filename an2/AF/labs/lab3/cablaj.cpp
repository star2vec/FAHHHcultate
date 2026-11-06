#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

#define NMAX 3003

int x[NMAX];
int y[NMAX];

int luat[NMAX];

double dist[NMAX];
int dela[NMAX];

double calcdist(int x1, int y1, int x2, int y2) {
    int dx, dy;
    dx = x1-x2;
    dy = y1-y2;
    return sqrt(1LL*dx*dx + 1LL*dy*dy);
}

int main() {
    ifstream fin("cablaj.in");
    ofstream fout("cablaj.out");
    
    int n, m, c, i, j, nr, ult;
    double mini, dd, costmin;

    fin >> n;

    for (i=1; i<=n; i++) {
        fin >> x[i] >> y[i];
    }


    nr = 0;
    ult = 1;
    luat[1] = 1;
    costmin = 0;
    while (nr<n-1) {
        for (i=1; i<=n; i++) {
            if (luat[i]==0) {
                dd = calcdist(x[ult], y[ult], x[i], y[i]);
                if (dist[i]==0 || dd < dist[i]) {
                    dist[i] = dd;
                    dela[i] = ult;
                }
            }
        }

        mini = 100000001;
        for (i=1; i<=n; i++) {
            if (luat[i]==0) {
                if (mini > dist[i]) {
                    mini = dist[i];
                    ult = i;
                }
            }
        }
        luat[ult] = 1;
        costmin += dist[ult];
        nr++;
    }

    fout.precision(3);
    fout << fixed << costmin;
    
    fin.close();
    fout.close();
    return 0;
}