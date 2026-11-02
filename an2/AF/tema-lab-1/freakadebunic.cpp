#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100001

int parent[NMAX];
int rez[NMAX];
int culoare[NMAX];
int trupe[NMAX];
int counted[NMAX];

queue<int> q;


int main() {
    ifstream fin("freakadebunic.in");
    ofstream fout("freakadebunic.out");
    
    int n, k, i, a, b, nod, nou, nr;
    string cuv;
    
    fin >> n >> k;
    for (i=0; i<k; i++) {
        fin >> trupe[i];
    }

    parent[1] = 1;
    for (i=0; i<n-1; i++) {
        fin >> a >> b;
        if (parent[a]==0) {
            parent[a] = b;
        } else {
            parent[b] = a;
        }
    }
    
    for (i=0; i<k; i++) {
        q.push(trupe[i]);
        culoare[trupe[i]] = trupe[i];
    }   

    nr = 0;
    while (!q.empty()) {
        nod = q.front();

        nou = parent[nod];
        if (culoare[nou]==0) {
            culoare[nou] = culoare[nod];
            if (nou!=1) {
                q.push(nou);        
            }
        } else if (culoare[nou]!=culoare[nod] && counted[nou]==0) {
            rez[nr] = nou;
            counted[nou] = 1;
            nr++;
        }

        q.pop();
    }
    
    sort(rez, rez+nr);
    fout << nr << "\n";
    for (i=0; i<nr; i++) {
        fout << rez[i] << " ";
    }
    
    fin.close();
    fout.close();
    return 0;
}
