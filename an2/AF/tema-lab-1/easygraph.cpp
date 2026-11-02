#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100001

vector<long long int> graf[NMAX];
long long int val[NMAX];
long long int d[NMAX];
long long int in[NMAX];
long long int viz[NMAX];

queue<long long int> q;


int main() {
    ifstream fin("easygraph.in");
    ofstream fout("easygraph.out");
    
    long long int t, tt, n, m, k, i, a, b, nod, nou, nr, maxi;
    string cuv;

    fin >> t;
    for (tt=0; tt<t; tt++) {
        fin >> n >> m;
        for (i=1; i<=n; i++) {
            fin >> val[i];
            graf[i].clear();
            d[i] = val[i];
            in[i] = 0;
            viz[i] = 0;
            if (i==1) {
                maxi = val[i];
            } 
            if (maxi < val[i]) {
                maxi = val[i];
            }
        }
        for (i=0; i<m; i++) {
            fin >> a >> b;
            graf[a].push_back(b);
            in[b]++;
        }

        for (i=1; i<=n; i++) {
            if (in[i]==0) {
                q.push(i);
                viz[i] = 1; 
            }
        }

        while(!q.empty()) {
            nod = q.front();
            q.pop();

            for (i=0; i<graf[nod].size(); i++) {
                nou = graf[nod][i];
                if (viz[nou]==0) {
                    viz[nou] = 1;
                    q.push(nou);
                    d[nou] = max(d[nou], d[nod]+val[nou]);
                } else {
                    if (d[nou] < d[nod]+val[nou]) {
                        d[nou] = d[nod]+val[nou];
                        q.push(nou);
                    }
                }
                if (maxi < d[nou]) {
                    maxi = d[nou];
                }
            }
        }

        fout << maxi << "\n";
    }
    
    fin.close();
    fout.close();
    return 0;
}
