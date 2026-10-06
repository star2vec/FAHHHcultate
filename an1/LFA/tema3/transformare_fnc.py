def getfnc(N, sigma, prod, S):
    # scoatem neterminalele neutilizabile
    utile = set()

    for nt in N:
        for p in prod[nt]:
            netermgasit = 0
            for lit in p:
                if lit in N:
                    netermgasit = 1
                    break
            if netermgasit==0:
                utile.add(nt)
                break
            

    change = 1
    while change != 0:
        change = 0
        for nt in N:
            if nt not in utile:
                for p in prod[nt]:
                    utilgasit = 0
                    for lit in p:
                        if lit in N and lit not in utile:
                            utilgasit = 1
                            break
                    if utilgasit==0:
                        utile.add(nt)
                        change = 1
                        break
                    
    newN = []
    newprod = {}
    for nt in N:
        if nt in utile:
            newN.append(nt)
            
            newprodnt = []
            for p in prod[nt]:
                descos = 0
                for lit in p:
                    if lit in N and lit not in utile:
                        descos = 1
                        break
                if descos == 0:
                    newprodnt.append(p)
            newprod[nt] = newprodnt

    N = newN
    prod = newprod



    # scoatem neterminalele inaccesibile
    viz = set()
    def dfs(nt):
        viz.add(nt)
        for p in prod[nt]:
            for lit in p:
                if lit in N and lit not in viz:
                    dfs(lit)

    dfs(S)

    newN = []
    newprod = {}
    for nt in N:
        if nt in viz:
            newN.append(nt)
            
            newprodnt = []
            for p in prod[nt]:
                descos = 0
                for lit in p:
                    if lit in N and lit not in viz:
                        descos = 1
                        break
                if descos == 0:
                    newprodnt.append(p)
            newprod[nt] = newprodnt
                    
    N = newN
    prod = newprod

    # scoatem lambda productiile
    descos = []
    for nt in N:
        if "λ" in prod[nt]:
            if len(prod[nt])==1:
                descos.append(nt) 

    while len(descos)>0:
        lambdant = descos.pop(0)
        N.remove(lambdant)
        del prod[lambdant]
        
        for nt in N:
            newprodnt = []
            for p in prod[nt]:
                pnoua = p.replace(lambdant, "")
                if pnoua == "":
                    pnoua = "λ"
                    if nt not in descos and len(prod[nt])==1:
                        descos.append(nt)
                        
                if pnoua not in newprodnt:
                    newprodnt.append(pnoua)
            prod[nt] = newprodnt
            
    ntwlambda = []
    for nt in N:
        if "λ" in prod[nt]:
            ntwlambda.append(nt)
            prod[nt].remove("λ")          

    change = 1
    while change != 0:
        change = 0
        for nt in N:
            newprodnt = []
            for p in prod[nt]:
                if p not in newprodnt:
                    newprodnt.append(p)
                
                for i in range(len(p)):
                    if p[i] in ntwlambda:
                        semicuv = p[:i] + p[(i+1):]
                        if semicuv == "":
                            if nt not in ntwlambda:
                                ntwlambda.append(nt) 
                                change = 1
                        else:
                            if semicuv not in newprodnt and semicuv not in prod[nt]:
                                newprodnt.append(semicuv)
                                change = 1
                            
            prod[nt] = newprodnt   
            
    for nt in N:
        if "λ" in prod[nt]:
            prod[nt].remove("λ")         
                        
    if S in ntwlambda or "λ" in prod[S]:
        N.append("Z")
        prod["Z"] = [S, "λ"]
        if "λ" in prod[S]: 
            prod[S].remove("λ")
        S = "Z"
        
        
    # eliminare productiilor unitare
    change = 1
    while change != 0:
        change = 0
        
        for nt in N:
            for p in list(prod[nt]): 
                if len(p) == 1 and p in N:
                    prod[nt].remove(p)
                    change = 1
                    
                    if p != nt: 
                        for p2 in prod[p]:
                            if p2!='λ' and p2 not in prod[nt]:
                                prod[nt].append(p2)
                                
    # scoatem neterminalele neutilizabile
    utile = set()

    for nt in N:
        for p in prod[nt]:
            netermgasit = 0
            for lit in p:
                if lit in N:
                    netermgasit = 1
                    break
            if netermgasit==0:
                utile.add(nt)
                break
            

    change = 1
    while change != 0:
        change = 0
        for nt in N:
            if nt not in utile:
                for p in prod[nt]:
                    utilgasit = 0
                    for lit in p:
                        if lit in N and lit not in utile:
                            utilgasit = 1
                            break
                    if utilgasit==0:
                        utile.add(nt)
                        change = 1
                        break
                    
    newN = []
    newprod = {}
    for nt in N:
        if nt in utile:
            newN.append(nt)
            
            newprodnt = []
            for p in prod[nt]:
                descos = 0
                for lit in p:
                    if lit in N and lit not in utile:
                        descos = 1
                        break
                if descos == 0:
                    newprodnt.append(p)
            newprod[nt] = newprodnt

    N = newN
    prod = newprod

    # scoatem neterminalele inaccesibile
    viz = set()
    def dfs2(nt):
        viz.add(nt)
        for p in prod[nt]:
            for lit in p:
                if lit in N and lit not in viz:
                    dfs2(lit)
    if S in prod:
        dfs2(S)

    newN = []
    newprod = {}
    for nt in N:
        if nt in viz:
            newN.append(nt)
            
            newprodnt = []
            for p in prod[nt]:
                descos = 0
                for lit in p:
                    if lit in N and lit not in viz:
                        descos = 1
                        break
                if descos == 0:
                    newprodnt.append(p)
            newprod[nt] = newprodnt
                    
    N = newN
    prod = newprod

    # transformare finala

    alfanefol = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for nt in N:
        if nt in alfanefol:
            alfanefol = alfanefol.replace(nt, "")
    changed = {}

    for nt in list(N):
        newprodnt = []
        for p in prod[nt]:
            if len(p)>1:
                pnoua = p
                for lit in p:
                    if lit in sigma:
                        if lit not in changed:
                            newnt = alfanefol[0]
                            alfanefol = alfanefol[1:]
                            N.append(newnt)
                            prod[newnt] = [lit]
                            changed[lit] = newnt
                        pnoua = pnoua.replace(lit, changed[lit])
                newprodnt.append(pnoua)
            else:
                newprodnt.append(p)
        prod[nt] = newprodnt
        

    change = 1
    Y = {}
    while change != 0:
        change = 0
        for nt in list(N):
            newprodnt = []
            for p in prod[nt]:
                if len(p)>2:
                    if p[1:] not in Y:
                        Y[p[1:]] = alfanefol[0]
                        alfanefol = alfanefol[1:]
                        N.append(Y[p[1:]])
                        prod[Y[p[1:]]] = [p[1:]]
                    pnoua = p[0] + Y[p[1:]]
                    newprodnt.append(pnoua)
                    change = 1
                else:
                    newprodnt.append(p)
            prod[nt] = newprodnt
    
    return N, sigma, prod, S

if __name__ == "__main__":
    inputtxt = open("input.txt").read()

    linii = inputtxt.split("\n")

    N = linii[0].split()
    sigma = linii[1].split()

    prod = {}
    for nt in N:
        prod[nt] = []
        
        
    m = int(linii[2])
    for i in range(3, 3+m):
        lin = linii[i].split()    
        if lin[0] not in prod:
            prod[lin[0]] = []
        prod[lin[0]].append(lin[1])

    S = linii[m+3]

    N, sigma, prod, S = getfnc(N, sigma, prod, S)        

    with open("output.txt", "w") as fout:
        for nt in prod:
            for p in prod[nt]:
                fout.write(nt + " -> " + p + "\n")