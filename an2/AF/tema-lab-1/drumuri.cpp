#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");

#define NMAX 100001

vector<int> graf[NMAX];
unordered_map<long long int, int> used;

int viz[NMAX];


void dfs(int nod, int parent) {
    int nou, i, nr, uval;
    vector<int> lun;

    for (i=0; i<graf[nod].size(); i++) {
        nou = graf[nod][i];
        if (viz[nou]==0) {
            viz[nou] = 1;
            dfs(nou, nod);
        }
    }

    nr = 0;
    for (i=0; i<graf[nod].size(); i++) {
        nou = graf[nod][i];
        uval = nod*NMAX+nou;
        if (used.find(uval)==used.end() && nou!=parent) {
            nr++;
            lun.push_back(graf[nod][i]);
        }
    }

    if (nr%2==1) {
        fout << parent << " " << nod << " " << lun[lun.size()-1] << "\n"; 
        uval = parent*NMAX + nod;
        used[uval] = 1;
        uval = nod*NMAX + parent;
        used[uval] = 1;
        uval = lun[lun.size()-1]*NMAX + nod;
        used[uval] = 1;
        uval = nod*NMAX + lun[lun.size()-1];
        used[uval] = 1;
        lun.pop_back();
    } 
    for (i=0; i<lun.size(); i+=2) {
        fout << lun[i] << " " << nod << " " << lun[i+1] << "\n"; 
        uval = lun[i]*NMAX + nod;
        used[uval] = 1;
        uval = nod*NMAX + lun[i];
        used[uval] = 1;
        uval = lun[i+1]*NMAX + nod;
        used[uval] = 1;
        uval = nod*NMAX + lun[i+1];
        used[uval] = 1;
    }

}


int main() {
    int n, i, a, b, m, j;

    fin >> n >> m;
    for (i=0; i<m; i++) {
        fin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }   

    if (m%2==1) {
        fout << 0 << "\n";
    } else {
        fout << 1 << "\n";
        viz[1] = 1;
        dfs(1, 0);
    }

    fin.close();
    fout.close();
    return 0;
}