input = open("input.txt").read()

stari = []
muchie = {}
F = []
sigma = []

linii = input.split("\n")

n = int(linii[0])
stari = linii[1].split()
    
m = int(linii[2])
for i in range(3, 3+m):
    lin = linii[i].split()
    if lin[0] not in muchie:
        muchie[lin[0]] = {}
    muchie[lin[0]][lin[2]] = lin[1]
    
    if lin[2] not in sigma:
        sigma.append(lin[2])
        
q0 = linii[m+3]
    
nrF = int(linii[m+4])
for i in range(m+5, m+5+nrF):
    F.append(linii[i])

nrcuv = int(linii[m+5+nrF])

for i in range(m+5+nrF+1, m+5+nrF+1+nrcuv):
    cuv = linii[i]
    cuv = cuv.strip()
    
    q = q0
    drum = str(q0)
    for lit in cuv:
        if q in muchie and lit in muchie[q]:
            q = muchie[q][lit]
            drum = drum + " -(" + lit + ")-> " + q
        else:
            q = None
            break

    if q in F:
        print("DA: " + drum)
    else:
        print("NU")
        
print(f"alfabet ({len(sigma)} litere): {' '.join(sigma)}")