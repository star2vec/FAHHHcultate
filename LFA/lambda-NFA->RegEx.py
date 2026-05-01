inputtxt = open("input.txt").read()

stari = []
muchie = {}
F = []
sigma = []

linii = inputtxt.split("\n")

stari = linii[0].split()
sigma = linii[1].split()

rin = {}
for s in stari:
    rin[s] = []
    muchie[s] = {}
    
m = int(linii[2])
for i in range(3, 3+m):
    lin = linii[i].split()
    if lin[1] not in muchie[lin[0]]:
        muchie[lin[0]][lin[1]] = lin[2]
    else:
        muchie[lin[0]][lin[1]] += "+" + lin[2]
    if (lin[0] not in rin[lin[1]]) and (lin[0] != lin[1]):
        rin[lin[1]].append(lin[0])
        
q0 = linii[m+3]
q0 = q0.strip()
rin[q0].append("qstart")
muchie["qstart"] = {q0: "λ"}

starifin = linii[m+4].split()
rin["qfin"] = []
for sf in starifin:
    rin["qfin"].append(sf)
    muchie[sf]["qfin"] = "λ"
    
for q in stari:
    for r1 in rin[q]:
        if r1 != q:
            for r2 in muchie[q]:
                if r2 != q:
                    road = ""
                    if muchie[r1][q] != "λ":
                        if "+" in muchie[r1][q]:
                            road = "(" + muchie[r1][q] + ")"
                        else:
                            road = muchie[r1][q]
                    if q in muchie[q] and muchie[q][q] != "λ":
                        road += "(" + muchie[q][q] + ")*"
                    if muchie[q][r2] != "λ":
                        if "+" in muchie[q][r2]:
                            road += "(" + muchie[q][r2] + ")"
                        else:
                            road += muchie[q][r2]
                        
                    if road == "":
                        road = "λ"
                    
                    
                    if r2 in muchie[r1]:
                        muchie[r1][r2] = "(" + muchie[r1][r2] + ")+(" +  road + ")"
                    else:
                        muchie[r1][r2] = road
                    
                    if r1 not in rin[r2]:
                        rin[r2].append(r1)
                
    for r1 in rin[q]:
        if q in muchie[r1]:
            del muchie[r1][q]
            
    for r2 in muchie[q]:
        if q in rin[r2]:
            rin[r2].remove(q)
    
    del muchie[q]
    del rin[q]
    
with open("output.txt", "w") as fout:
    fout.write(muchie["qstart"]["qfin"])