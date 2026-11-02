#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

#define NMAX 100001
#define ALFAMAX 27

vector <int> graf[NMAX];
int viz[NMAX];
int pasi[NMAX];

int last[ALFAMAX];

queue<int> q;

int bfs(int x,  int y) {
    int i, l, ll;

    q.push(x);
    pasi[x] = 0;
    while (!q.empty() && pasi[y]==0) {
        l = q.front();

        for (i=0; i<graf[l].size(); i++) {
            ll = graf[l][i];

            if (pasi[ll]==0 && ll!=x) {
                pasi[ll] = pasi[l] + 1;
                q.push(ll);
            }
        }

        q.pop();
    }

    return pasi[y];
}



int main() {
    ifstream fin("alice2.in");
    ofstream fout("alice2.out");
    
    int i, poz, litera;
    string cuv;
    
    fin >> cuv;

    for (i=0; i<cuv.size()-1; i++) {
        graf[i].push_back(i+1);
        graf[i+1].push_back(i); 
    }

    for (i=0; i<ALFAMAX; i++) {
        last[i] = -1;
    }

    for (i=0; i<cuv.size(); i++) {
        litera = cuv[i] - 'a';
        if (last[litera] != -1) {
            graf[i].push_back(last[litera]);
            graf[last[litera]].push_back(i);
        }

        if (cuv[i-1] == cuv[i]) {
            graf[i].push_back(i+1);
            graf[i+1].push_back(i);
        }
        last[litera] = i;
    }

    fout << bfs(0, cuv.size() - 1);
    
    
    fin.close();
    fout.close();
    return 0;
}