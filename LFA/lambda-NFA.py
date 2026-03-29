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
    if lin[2] not in muchie[lin[0]]:
        muchie[lin[0]][lin[2]] = []
    muchie[lin[0]][lin[2]].append(lin[1])

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
    
    qpos = [q0] # de la q posibil
    stack = [q0]
    drum = {q0: str(q0)}
    while len(stack) > 0:
        q = stack.pop()
        if q in muchie and 'lambda' in muchie[q]:
            for dest in muchie[q]['lambda']:
                if dest not in qpos:
                    qpos.append(dest)
                    stack.append(dest)
                    drum[dest] = drum[q] + " --> " + dest
    
    for lit in cuv:
        newqpos = []
        newdrum = {}
        for q in qpos:
            if q in muchie and lit in muchie[q]:
                for dest in muchie[q][lit]:
                    if dest not in newqpos:
                        newqpos.append(dest)
                        if lit != 'lambda':
                            newdrum[dest] = drum[q] + " -(" + lit + ")-> " + dest
                        else: 
                            newdrum[dest] = drum[q] + " --> " + dest
                        
        qpos = list(newqpos)
        drum = newdrum
        
        stack = list(qpos) 
        while len(stack) > 0:
            q = stack.pop()
            if q in muchie and 'lambda' in muchie[q]:
                for dest in muchie[q]['lambda']:
                    if dest not in qpos:
                        qpos.append(dest)
                        stack.append(dest)
                        drum[dest] = drum[q] + " --> " + dest
    

    nr = len([q for q in qpos if q in F])
    if nr > 0:
        print("DA, drumuri posibile: ")
        for q in qpos:
            if q in F:
                print(drum[q])
    else:
        print("NU")
        
if 'lambda' in sigma:
    sigma.remove('lambda')
print(f"alfabet ({len(sigma)} litere): {' '.join(sigma)}")