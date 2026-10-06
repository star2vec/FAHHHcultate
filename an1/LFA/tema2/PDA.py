inputtxt = open("input.txt").read()


stari = []
muchie = {}
F = []
sigma = []
gamma = []
stiva = ""

linii = inputtxt.split("\n")

stari = linii[0].split()
sigma = linii[1].split()
gamma = linii[2].split()

for s in stari:
    muchie[s] = {}

m = int(linii[3])

for i in range(4, 4+m):
    lin = linii[i].split()
    if (lin[1], lin[2]) not in muchie[lin[0]]:
        muchie[lin[0]][(lin[1], lin[2])] = []
    muchie[lin[0]][(lin[1], lin[2])].append((lin[3], lin[4]))

q0 = linii[m+4]
Z = linii[m+5]
F = linii[m+6].split()
mod = linii[m+7]
cuv = linii[m+8]

q = q0
stiva = Z
idx = 0
config = (q, idx, stiva)
coada = []
coada.append(config)
acceptat = False

viz = []
viz.append(config)

while (len(coada) > 0 and acceptat == False):
    q, idx, stiva = coada.pop(0)
    
    ok1 = 0
    ok2 = 0
    if idx == len(cuv):
        if stiva == "":
            ok1 = 1
        if q in F:
            ok2 = 1
    
    if (mod == "stiva goala" and ok1==1):
        acceptat = True
    if (mod == "stare finala" and ok2==1):
        acceptat = True
    if (mod == "ambele" and ok1==1 and ok2==1):
        acceptat = True

    if acceptat == True:
        break
    
    if stiva == "":
        continue
    
    if idx < len(cuv):
        for move in muchie[q].keys():
            if move[0] == cuv[idx] and move[1] == stiva[0]:
                for m in muchie[q][move]:
                    add = m[1]
                    if (m[1]=="λ"):
                        add = ""
                    config = (m[0], idx+1, add+stiva[1:])
                    if config not in viz:
                        viz.append(config)
                        coada.append(config)
                        
    for move in muchie[q].keys():
        if move[0] == "λ" and move[1] == stiva[0]:
            for m in muchie[q][move]:
                add = m[1]
                if (m[1]=="λ"):
                    add = ""
                config = (m[0], idx, add+stiva[1:])
                if config not in viz:
                    viz.append(config)
                    coada.append(config)
                    
                
if acceptat == False:
    rez = "RESPINS"
else:
    rez = "ACCEPTAT"

with open("output.txt", "w") as fout:
    fout.write(rez)