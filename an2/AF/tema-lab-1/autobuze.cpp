#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 50001
#define AMAX 10000001

vector<int> graf[NMAX];
int v[NMAX];
int f[NMAX];
int viz[NMAX];
unordered_map<int, int> poz;
char prez[AMAX];

void dfs(int nod) {
    int i, nou;

    for (i=0; i<graf[nod].size(); i++) {
        nou = graf[nod][i];
        if (viz[nou]==0) {
            viz[nou] = 1;
            dfs(nou);
        }
    }
}


int main() {
    ifstream fin("autobuze.in");
    ofstream fout("autobuze.out");
    
    int n, i, j, nr, maxi;

    fin >> n;
    maxi = 0;
    for (i=0; i<n; i++) {
        fin >> v[i];
        if (maxi < v[i]) {
            maxi = v[i];
        }
        prez[v[i]] = 1;
    }   

    sort(v, v+n);

    for (i=0; i<n; i++) {
        poz[v[i]] = i;
    }

    for (i=0; i<n; i++) {
        if (f[i]==0) {
            for (j=2*v[i]; j<=maxi; j+=v[i]) {
                if (prez[j]==1) {
                    graf[i].push_back(poz[j]);
                    graf[poz[j]].push_back(i);
                    f[poz[j]] = 1;
                }
            }
        }
    }

    nr = 0;
    for (i=0; i<n; i++) {
        if (viz[i]==0) {
            viz[i] = 1;
            dfs(i);
            nr++;
        }
    }

    fout << nr << "\n";
    
    fin.close();
    fout.close();
    return 0;
} 