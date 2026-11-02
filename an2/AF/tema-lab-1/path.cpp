#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define ALFAMAX 53
#define KMAX 2000000002

string rez;
int n, k;
int nr;

int fullmaxi;
int graf[ALFAMAX][ALFAMAX];
int in[ALFAMAX];
int out[ALFAMAX];
int viz[ALFAMAX];
int lm[ALFAMAX];
long long int cnt[ALFAMAX];

void dfslmcnt(int nod) {
    int i, nou, lmaxi;

    if (nr >= k) {
        return;
    }

    if (out[nod]==0) {
        lm[nod] = 1;
        cnt[nod] = 1;
        return;
    }

    lmaxi = 0;
    for (i=1; i<ALFAMAX; i++) {
        if (graf[nod][i] == 1) {
            if (viz[i]==0) {
                viz[i] = 1;
                dfslmcnt(i);
            }
            if (lm[i] > lmaxi) {
                lmaxi = lm[i];
            }
        }
    }
    lm[nod] = lmaxi + 1;
    if (lm[nod] > fullmaxi) {
        fullmaxi = lm[nod];
    }
    for (i=1; i<ALFAMAX; i++) {
        if (graf[nod][i] == 1) {
            if (lm[i] == lmaxi) {
                cnt[nod] += cnt[i];
                if (cnt[nod] > KMAX) {
                    cnt[nod] = KMAX;
                }
            }
        }
    }
}

void dfs(int nod, string cuv) {
    int i, nou, ok;

    if (nod <= 26) {
        cuv += (char)(nod + 'a' - 1);
    } else {
        cuv += (char)(nod + 'A' - 27);
    }

    if (lm[nod]==1) {
        rez = cuv;
        return;
    }

    ok = 0;
    for (i=1; i<ALFAMAX && ok==0; i++) {
        if (graf[nod][i] == 1 && lm[nod] - 1 == lm[i]) {
            if (k > cnt[i]) {
                k -= cnt[i];
            } else {
                ok = 1;
                dfs(i, cuv);
            }
        }
    }
}

int main() {
    ifstream fin("path.in");
    ofstream fout("path.out");
    
    long long int i, a, b, m;
    char c1, c2;
    string lit;

    fin >> n >> m >> k;
    for (i=0; i<m; i++) {
        fin >> c1 >> c2;
        if ('a' <= c1 && c1 <= 'z') {
            a = c1 - 'a' + 1;
        } else {
            a = c1 - 'A' + 27;
        }
        if ('a' <= c2 && c2 <= 'z') {
            b = c2 - 'a' + 1;
        } else {
            b = c2 - 'A' + 27;
        }

        graf[a][b] = 1;
        in[b]++;
        out[a]++;
    }   


    for (i=1; i<ALFAMAX; i++) {
        if (in[i]==0) {
            dfslmcnt(i);
        }
    }

    for (i=1; i<ALFAMAX; i++) {
        if (lm[i]==fullmaxi) {
            if (cnt[i] < k) {
                k -= cnt[i];
            } else {
                dfs(i, "");
                break;
            }
        }
    }

    fout << rez;
    
    fin.close();
    fout.close();
    return 0;
}