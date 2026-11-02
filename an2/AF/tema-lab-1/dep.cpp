#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 257
#define MOD 666013

vector<int> graf[NMAX];
vector<int> gt[NMAX];

vector<int> grouped[NMAX];

int grupnod[NMAX];
int weight[NMAX];
int nrch[NMAX];

int viz[NMAX];

int nrfin;
int fini[NMAX];
int nrcomp;
vector<int> rez[NMAX];

int n, k;

int parent[NMAX];
vector<int> tree[NMAX];


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

    rez[nrcomp].push_back(nod);
    grupnod[nod] = nrcomp+1;

    for (i=0; i<gt[nod].size(); i++) {
        nou = gt[nod][i];
        if (viz[nou] == 0) {
            viz[nou] = 1;
            dfst(nou);
        }
    }
} 

void buildgrouped() {
    int i, nou, nod;

    for (nod=1; nod<=n; nod++) {
        for (i=0; i<graf[nod].size(); i++) {
            nou = graf[nod][i];
            if (grupnod[nou]!=grupnod[nod]) {
                grouped[grupnod[nod]].push_back(grupnod[nou]);
            }
        }
    }
}

void countrchcomp(int nod, int origin) {
    int i, nou;

    for (i=0; i<grouped[nod].size(); i++) {
        nou = grouped[nod][i];
        if (viz[nou]==0) {
            viz[nou] = 1;
            nrch[origin]++;
            countrchcomp(nou, origin);
        }
    }
}


void buildtree() {
    int i, nou, nod;

    for (nod=1; nod<=nrcomp; nod++) {
        parent[nod] = 0;
        for (i=0; i<grouped[nod].size(); i++) {
            nou = grouped[nod][i];
            if (nrch[nou] == nrch[nod] - 1) {
                parent[nod] = nou;
            }
        }
        tree[parent[nod]].push_back(nod);
    }
}


long long int dp[NMAX][NMAX]; /// nr de lanturi incepanad de la un nod care au exact un numar de oamaeni inclusi
long long int aux[NMAX];
void rucsac(int nod) {
    int i, son, ii, iii;

    dp[nod][weight[nod]] = 1;

    for (i=0; i<tree[nod].size(); i++) {
        son = tree[nod][i];
        rucsac(son);

        for (ii=0; ii<=k; ii++) {
            aux[ii] = 0;
        }

        for (ii=0; ii<=k; ii++) {
            if (dp[nod][ii] != 0) {
                aux[ii] = (aux[ii] + dp[nod][ii])%MOD;
                for (iii=1; iii+ii<=k; iii++) {
                    aux[ii+iii] = (aux[ii+iii] + dp[nod][ii]*dp[son][iii])%MOD;
                }
            }
        }
        for (ii=0; ii<=k; ii++) {
            dp[nod][ii] = aux[ii];
        }
    }

}


int main() {
    ifstream fin("dep.in");
    ofstream fout("dep.out");

    int m, i, a, b, ii;

    fin >> n >> m >> k;
    for (i=0; i<m; i++) {
        fin >> a >> b;
        graf[a].push_back(b);
        gt[b].push_back(a);
    }   

    /// bagam kosaraju (ctc) + le grupam, acum un nod o sa aiba nr de oameni din componenta
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
    nrcomp = 0;
    for (i=nrfin-1; i>=0; i--) {
        if (viz[fini[i]] == 0) {
            viz[fini[i]] = 1;
            dfst(fini[i]);
            nrcomp++;
        }
    }

    /// construim graful nou
    buildgrouped();
    for (i=1; i<=n; i++) {
        weight[grupnod[i]]++;
    }
    for (i=1; i<=nrcomp; i++) {
        for (ii=1; ii<=nrcomp; ii++) {
            viz[ii] = 0;
        }
        viz[i] = 1;
        countrchcomp(i, i);
    }
    buildtree();
    
    /// incepem de la 0 ca la inceput bagam parent[nod] = 0 pt fiecare, daca isi da overwrite dupa it happens
    rucsac(0);
    fout << dp[0][k];

    fin.close();
    fout.close();
    return 0;
}