#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100001

vector<int> graf[NMAX];
vector<int> gt[NMAX];


int viz[NMAX];

int nrfin;
int fini[NMAX];

int nr;
vector<int> rez[NMAX];

int st[NMAX];
int kst;

void dfs(int nod) {
    int i, nou;

    for (i=0; i<graf[nod].size(); i++) {
        nou = graf[nod][i];
        if (viz[nou]==0) {
            viz[nou] = 1;
            dfs(nou);
        }
    }

    fini[nrfin] = nod;
    nrfin++;
}

void dfst(int nod) {
    int i, nou;

    rez[nr].push_back(nod);

    for (i=0; i<gt[nod].size(); i++) {
        nou = gt[nod][i];
        if (viz[nou] == 0) {
            viz[nou] = 1;
            dfst(nou);
        }
    }
} 


int main() {
    ifstream fin("ctc.in");
    ofstream fout("ctc.out");
    
    int n, i, a, b, m, j;

    fin >> n >> m;
    for (i=0; i<m; i++) {
        fin >> a >> b;
        graf[a].push_back(b);
        gt[b].push_back(a);
    }   

    nrfin = 0;
    for (i=1; i<=n; i++) {
        if (viz[i]==0) {
            viz[i] = 1;
            dfs(i);
        }
    }

    for (i=1; i<=n; i++) {
        viz[i] = 0;
    }

    nr = 0;
    for (i=nrfin-1; i>=0; i--) {
        if (viz[fini[i]] == 0) {
            viz[fini[i]] = 1;
            dfst(fini[i]);
            nr++;
        }
    }
    

    fout << nr << "\n";
    for (i=0; i<nr; i++) {
        for (j=0; j<rez[i].size(); j++) {
            fout << rez[i][j] << ' ';
        }
        fout << "\n";
    }
    
    fin.close();
    fout.close();
    return 0;
}