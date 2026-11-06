#include <iostream>
#include <fstream>

using namespace std;

#define NMAX 100001
 
int sef[NMAX];
 
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
    ifstream fin("disjoint.in");
    ofstream fout("disjoint.out");
    
    int n, m, i, x, y, op;

    fin >> n >> m;
    for (i=1; i<=n; i++) {
        sef[i] = i;
    }
    
    for (i=0; i<m; i++) {
        fin >> op >> x >> y;
        if (op==1) {
            uneste(x, y);
        } else {
            if (find(x) == find(y)) {
                fout << "DA" << "\n";
            } else {
                fout << "NU" << "\n";
            }
        }
    }
    
    fin.close();
    fout.close();
    return 0;
}