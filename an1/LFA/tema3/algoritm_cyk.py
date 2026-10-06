input = open("input.txt").read()

linii = input.split("\n")

N = []
sigma = []

N = linii[0].split()
sigma = linii[1].split()

p2 = {}
prod = {}
m = int(linii[2])
for i in range(3, 3+m):
    lin = linii[i].split()    
    if lin[0] not in prod:
        prod[lin[0]] = []
    prod[lin[0]].append(lin[1])
    if len(lin[1]) == 2:
        if lin[0] not in p2:
            p2[lin[0]] = []
        p2[lin[0]].append(lin[1])

S = linii[m+3]
w = linii[m+4]

n = len(w)

dp = []
for i in range(n+1):
    dp.append([])
    for j in range(n+1):
        dp[i].append(set())
    
for i in range(1, n+1):
    lit = w[i-1]
    for nt in N:
        if lit in prod[nt]:
            dp[i][1].add(nt)
                
for l in range(2, n+1):
    for s in range(1, n-l+2):
        for part in range(1, l):
            for p in p2:
                for prodp in p2[p]:
                    b, c = prodp
                    if b in dp[s][part] and c in dp[s+part][l-part]:
                        dp[s][l].add(p)


with open("output.txt", "w") as fout:
    if S in dp[1][n]:
        fout.write("DA\n")
    else:
        fout.write("NU\n")
    
    for l in range(1, n+1):
        for c in range(1, n+1):
            fout.write(str(dp[c][l]) + " ")
        fout.write("\n")
    