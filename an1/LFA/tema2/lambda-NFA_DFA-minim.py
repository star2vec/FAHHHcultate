inputtxt = open("input.txt").read()

stari = []
muchie = {}
F = []
sigma = []

linii = inputtxt.split("\n")

stari = linii[0].split()
sigma = linii[1].split()

for q in stari:
    muchie[q] = {}
    
m = int(linii[2])
for i in range(3, 3+m):
    lin = linii[i].split()
    if lin[0] not in muchie:
        muchie[lin[0]] = {}
    if lin[2] not in muchie[lin[0]]:
        muchie[lin[0]][lin[2]] = []
    muchie[lin[0]][lin[2]].append(lin[1])
        
q0 = linii[m+3]
F = linii[m+4].split()

inchidere = {}
for q in stari:
    inchidere[q] = []
    inchidere[q].append(q) 

    coada = [q]
    while len(coada) > 0:
        now = coada.pop(0)
        if "λ" in muchie[now].keys():
            for nextq in muchie[now]["λ"]:
                if nextq not in inchidere[q]:
                    inchidere[q].append(nextq)
                    coada.append(nextq)
                    
nfa = {}
for q in stari:
    nfa[q] = {}
    for lit in sigma:
        lista = []
        for qq in inchidere[q]:
            if lit in muchie[qq].keys():
                for nextq in muchie[qq][lit]:
                    if nextq not in lista:
                        lista.append(nextq)
        nfa[q][lit] = []
        for elem in lista:
            for qq in inchidere[elem]:
                if qq not in nfa[q][lit]:
                    nfa[q][lit].append(qq)

q0dfa = tuple(sorted(inchidere[q0]))

Qdfa = [q0dfa]
coada = [q0dfa]
dfa = {}

while len(coada) > 0:
    q = coada.pop(0)
    dfa[q] = {}
    
    for lit in sigma:
        newq = []
    
        for qq in q:
            for nextq in nfa[qq][lit]:
                if nextq not in newq:
                    newq.append(nextq)

        dfa[q][lit] = tuple(sorted(newq))
        if tuple(sorted(newq)) not in Qdfa:
            Qdfa.append(tuple(sorted(newq)))
            coada.append(tuple(sorted(newq)))
            
            
Qdfa = [q for q in Qdfa if q != ()]
for q in Qdfa:
    for lit in sigma:
        if dfa[q][lit] == ():
            del dfa[q][lit]

Fdfa = []
for q in Qdfa:
    for qq in q:
        if qq in F:
            if q not in Fdfa:
                Fdfa.append(q)
                
with open("output.txt", "w") as fout:
     fout.write("stari DFA: " + str(Qdfa) + "\n")
     fout.write("stare initiala DFA: " + str(q0dfa) + "\n")
     fout.write("stari finale DFA: " + str(Fdfa) + "\n")
     for q in Qdfa:
         for lit in sigma:
             if lit in dfa[q]:
                fout.write(str(q) + " --(" + str(lit) + ")-->  " + str(dfa[q][lit]) + "\n")

sgn = {} 
for q in Qdfa:
    if q in Fdfa:
        sgn[q] = 1
    else:
        sgn[q] = 2
    
ok = 0
while ok == 0:
    newsgn = {}
    clase = {} 
    
    for q in Qdfa:
        semn = [sgn[q]]
        for lit in sigma:
            if lit in dfa[q]:
                semn.append(sgn[dfa[q][lit]])
            else:
                semn.append("∅")
                
        semn = tuple(semn)
        if semn not in clase:
            clase[semn] = []
        clase[semn].append(q)
   
    nrcls = 1
    for semn in clase:
        for q in clase[semn]:
            newsgn[q] = nrcls
        nrcls += 1
        
    if sgn == newsgn:
        ok = 1
    else:
        sgn = newsgn
        
Qmin = []
for q in clase.values():
    Qmin.append(tuple(sorted(q)))  
    
q0min = ()
for q in Qmin:
    if q0dfa in q:
        q0min = q     

Fmin = []
for q in Qmin:
    for qq in q:
        if qq in Fdfa:
            if q not in Fmin:
                Fmin.append(q)
                
dfamin = {}
for q in Qmin:
    
    rep = q[0]
    dfamin[q] = {}
    for lit in sigma:
        if lit in dfa[rep]:
            nextdfa = dfa[rep][lit]
            for q2 in Qmin:
                if nextdfa in q2:
                    dfamin[q][lit] = tuple(sorted(q2))

with open("output.txt", "a") as fout:
    fout.write("\n")
    fout.write("stari DFA minim: " + str(Qmin) + "\n")
    fout.write("stare initiala DFA minim: " + str(q0min) + "\n")
    fout.write("stari finale DFA minim: " + str(Fmin) + "\n")
    for q in Qmin:
        for lit in sigma:
            if lit in dfamin[q]:
                fout.write(str(q) + " --(" + str(lit) + ")-->  " + str(dfamin[q][lit]) + "\n")
