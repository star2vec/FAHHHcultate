#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100001

vector<int> graf[NMAX];
int nivmin[NMAX];
int niv[NMAX];
int viz[NMAX];

int nrcmin;
int cmin[NMAX];

int nrpc;
int pc[NMAX];
int fpc[NMAX];

int dfs(int nod, int mini, int nroot) {
    int i, nou;

    nivmin[nod] = niv[nod];

    for (i=0; i<graf[nod].size(); i++) {
        nou = graf[nod][i];
        if (viz[nou]==0) {
            if (niv[nod] == 1) {
                nroot++;
                if (nroot > 1) {
                    if (fpc[nod]==0) {
                        pc[nrpc] = nod;
                        nrpc++;
                        fpc[nod] = 1;
                    }
                }
            }
            viz[nou] = 1;
            niv[nou] = niv[nod] + 1;
            if (nou < mini) {
                mini = nou;
            }
            mini = dfs(nou, mini, nroot);

            nivmin[nod] = min(nivmin[nod], nivmin[nou]);
            if (nivmin[nou] >= niv[nod] && niv[nod] != 1) {
                if (fpc[nod]==0) {
                    pc[nrpc] = nod;
                    nrpc++;
                    fpc[nod] = 1;
                }
            }
        } else {
            if (niv[nou] < niv[nod]-1) {
                nivmin[nod] = min(nivmin[nod], niv[nou]);
            }
        }
    }
    return mini;
}


int main() {
    ifstream fin("pamant.in");
    ofstream fout("pamant.out");
    
    long long int n, i, a, b, m;

    fin >> n >> m;
    for (i=0; i<m; i++) {
        fin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }   

    nrcmin = 0;
    nrpc = 0;
    for (i=1; i<=n; i++) {
        if (viz[i]==0) {
            viz[i] = 1;
            niv[i] = 1;
            cmin[nrcmin] = dfs(i, i, 0);
            nrcmin++;
        }
    }

    fout << nrcmin << "\n";
    sort(cmin, cmin+nrcmin);
    for (i=0; i<nrcmin; i++) {
        fout << cmin[i] << " ";
    }
    fout << "\n";

    fout << nrpc << "\n";
    sort(pc, pc+nrpc);
    for (i=0; i<nrpc; i++) {
        fout << pc[i] << " ";
    }

    /*
    for (i=1; i<=n; i++) {
        cout << niv[i] << " " << nivmin[i] << "\n";
    }
    */
    
    fin.close();
    fout.close();
    return 0;
}