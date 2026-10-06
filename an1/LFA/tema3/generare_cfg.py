from transformare_fnc import getfnc

input = open("input.txt").read()

linii = input.split("\n")

N = []
sigma = []

N = linii[0].split()
sigma = linii[1].split()

prod = {}
m = int(linii[2])
for i in range(3, 3+m):
    lin = linii[i].split()    
    if lin[0] not in prod:
        prod[lin[0]] = []
    prod[lin[0]].append(lin[1])

S = linii[m+3]

N, sigma, prod, S = getfnc(N, sigma, prod, S)

k = int(linii[m+4])

rez = []
def gen(cuv):
    if len(cuv)>k:
        return
    
    idxnt = -1
    for i in range(len(cuv)):
        if cuv[i] in N:
            idxnt = i
            break
        
    if idxnt == -1:
        if len(cuv)==k:
            if cuv not in rez:
                rez.append(cuv)
        return
    else:
        nt = cuv[idxnt]
        for p in prod[nt]:
            if (p=="λ"):
                gen(cuv[:idxnt] + cuv[(idxnt+1):])
            else:
                gen(cuv[:idxnt] + p + cuv[(idxnt+1):])
        return

gen(S)

    
with open("output.txt", "w") as fout:
    for cuv in rez:
        fout.write(cuv + "\n")