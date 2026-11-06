#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 101
#define ALFAMAX 26

vector<int> graf[ALFAMAX];
int grad[ALFAMAX];

string cuv[NMAX];
char rez[ALFAMAX];

int main() {
    ifstream fin("foxandnames.in");
    ofstream fout("foxandnames.out");

    int n, i, j, nod, nr, ok;   
    queue<int> q;

    cin >> n;
    for (i=0; i<n; i++) {
        cin >> cuv[i];
    }

    ok = 0;
    for (i=0; i<n-1 && ok==0; i++) {
        j = 0;
        while (j < cuv[i].size() && j < cuv[i+1].size() && cuv[i][j] == cuv[i+1][j]) {
            j++;
        }
        if (j < cuv[i].size() && j < cuv[i+1].size()) {
            grad[cuv[i+1][j]-'a']++;
            graf[cuv[i][j]-'a'].push_back(cuv[i+1][j]-'a');
        } else if (j < cuv[i].size() && j == cuv[i+1].size()) {
            ok = 1;
        }
    }

    if (ok==1) {
        cout << "Impossible";
        return 0;
    }

    for (i=0; i<ALFAMAX; i++) {
        if (grad[i] == 0) {
            q.push(i);
        }
    }
    nr = 0;
    while (!q.empty()) {
        nod = q.front();
        q.pop();
        rez[nr] = char('a'+nod);
        nr++;
        for (auto vecin : graf[nod]) {
            grad[vecin]--;
            if (grad[vecin] == 0) {
                q.push(vecin);
            }
        }
    }

    if (nr < ALFAMAX) {
        cout << "Impossible";
    } else {
        for (i=0; i<ALFAMAX; i++) {
            cout << rez[i];
        }
    }

    fin.close();
    fout.close();
    return 0;
}