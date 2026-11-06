#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMAX 200002
#define MMAX 400004

int sef[NMAX];
int rez1[MMAX];
int rez2[MMAX];

struct muchie {
    int m1;
    int m2;
    int cost;
} much[MMAX];

bool cmp(const muchie& a, const muchie& b) {
    return a.cost < b.cost;
}

int find(int i) {
    if (sef[i] == i) {
        return i;
    }
    return sef[i] = find(sef[i]);
}
 
void uneste(int i, int j) {
    int sefi, sefj;
    
    sefi = find(i);
    sefj = find(j);
    
    sef[sefj] = sefi;
}



int main() {
    ifstream fin("apm.in");
    ofstream fout("apm.out");
    
    int n, m, i, x, y, c, costmin, nr;

    fin >> n >> m;
    for (i=1; i<=n; i++) {
        sef[i] = i;
    }
    
    for (i=0; i<m; i++) {
        fin >> x >> y >> c;
        much[i].m1 = x;
        much[i].m2 = y;
        much[i].cost = c;
    }

    sort(much, much+m, cmp);

    costmin = 0;
    nr = 0;
    for (i=0; i<m; i++) {
        x = much[i].m1;
        y = much[i].m2;
        if (find(x)!=find(y)) {
            uneste(x, y);
            rez1[nr] = x;
            rez2[nr] = y;
            nr++;
            costmin += much[i].cost;
        }
    }

    fout << costmin << "\n" << nr << "\n";
    for (i=0; i<nr; i++) {
        fout << rez1[i] << " " << rez2[i] << "\n"; 
    }
    
    fin.close();
    fout.close();
    return 0;
}