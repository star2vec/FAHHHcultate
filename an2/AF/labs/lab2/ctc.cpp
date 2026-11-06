#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define NMAX 100001

int n, m;

vector <int> graf[NMAX];
int viz[NMAX];
int nivmin[NMAX];

int nrez;
vector <int> rez[NMAX];

int nr;
int st[NMAX];
int f[NMAX]; /// daca se afla in stiva

int niv;
void dfs(int nod) {
    int nivpoz;
    
    nivmin[nod] = niv;
    nivpoz = niv;
    niv++;
    st[nr] = nod;
    nr++;
    f[nod] = 1;
    viz[nod] = 1;
    for (int i:graf[nod]) {
        if (nivmin[i]==-1) {
            dfs(i);
            nivmin[nod] = min(nivmin[nod], nivmin[i]);
        }
        if (f[i]==1) {
            nivmin[nod] = min(nivmin[nod], nivmin[i]);
        }
    }
    if (nivmin[nod] == nivpoz) {
        do {
            nr--;
            rez[nrez].push_back(st[nr]);
            f[st[nr]]=0;
            nivmin[st[nr]] = niv;
        } while (st[nr]!=nod);
        nrez++;
    }
}

int main() {
    ifstream fin("ctc.in");
    ofstream fout("ctc.out");
    
    int i, j, x, y;
    
    fin >> n >> m;
    
    for (i=0; i<m; i++) {
        fin >> x >> y;
        graf[x].push_back(y);
    }
    
    for (i=1; i<=n; i++) {
        nivmin[i] = -1;
    }
    
    nr = 0;
    nrez = 0;
    for (i=1; i<=n; i++) {
        if (viz[i]==0) {
            niv = 0;
            dfs(i);
        }
    }
    
    fout << nrez-1 << "\n";
    /*
    for (i=0; i<nrez; i++) {
        for (j=0; j<rez[i].size(); j++) {
            fout << rez[i][j] << " ";
        }
        fout << "\n";
    }
    */
    
    fin.close();
    fout.close();
    return 0;
}
