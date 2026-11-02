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
int f[NMAX];

int nr;
vector<int> rez[NMAX];

int st[NMAX];
int kst;

void dfs(int nod) {
    int i, nou;

    nivmin[nod] = niv[nod];
    st[kst] = nod;
    f[nod] = 1;
    kst++;

    for (i=0; i<graf[nod].size(); i++) {
        nou = graf[nod][i];
        if (viz[nou]==0) {
            viz[nou] = 1;
            niv[nou] = niv[nod] + 1;
            
            dfs(nou);

            nivmin[nod] = min(nivmin[nod], nivmin[nou]);
            if (nivmin[nou] >= niv[nod]) {
                while (kst>0 && st[kst-1] != nou) {
                    rez[nr].push_back(st[kst-1]);
                    f[st[kst-1]] = 0;
                    kst--;
                }
                if (st[kst-1]==nou) {
                    rez[nr].push_back(st[kst-1]);
                    f[st[kst-1]] = 0;
                    kst--;
                } 
                rez[nr].push_back(nod);
                if (f[nod]==0) {
                    st[kst] = nod;
                    kst++;
                }
                nr++;
            }
        } else {
            if (niv[nou] < niv[nod]-1) {
                nivmin[nod] = min(nivmin[nod], niv[nou]);
            }
        }
    }
}


int main() {
    ifstream fin("biconex.in");
    ofstream fout("biconex.out");
    
    int n, i, a, b, m, j;

    fin >> n >> m;
    for (i=0; i<m; i++) {
        fin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }   

    for (i=1; i<=n; i++) {
        if (viz[i]==0) {
            viz[i] = 1;
            niv[i] = 1;
            dfs(i);
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