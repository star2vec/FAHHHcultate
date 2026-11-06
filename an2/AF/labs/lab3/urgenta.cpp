#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMAX 256
#define MMAX 32385

int sef[NMAX];

struct muchie {
    int m1;
    int m2;
    int cost;
    int mark;
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
    ifstream fin("urgenta.in");
    ofstream fout("urgenta.out");
    
    int n, m, k, i, x, y, c, suma, nr, substract, sum;

    fin >> n >> m >> k;
    for (i=1; i<=n; i++) {
        sef[i] = i;
    }
    
    suma = 0;
    for (i=0; i<m; i++) {
        fin >> x >> y >> c;
        much[i].m1 = x;
        much[i].m2 = y;
        much[i].cost = c;
        suma += c;
    }

    sort(much, much+m, cmp);

    substract = 0;
    nr = 0;
    for (i=0; i<m && nr<n-k; i++) {
        x = much[i].m1;
        y = much[i].m2;
        if (find(x)!=find(y)) {
            uneste(x, y);
            nr++;
            substract += much[i].cost;
            much[i].mark = 1; 
        }
    }

    fout << suma-substract << "\n" << m-(n-k) << "\n";
    for (i=0; i<m; i++) {
        if (much[i].mark==0) {
            fout << much[i].m1 << " " << much[i].m2 << "\n";
        }
    }
    
    fin.close();
    fout.close();
    return 0;
}