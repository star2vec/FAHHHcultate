inputtxt = open("input.txt").read()

expr = inputtxt.strip()

op = {'|': 1, '*': 3, '(': 0, ')': 0, '.': 2}
stiva = []
output = ""

ant = "★"  
for lit in expr:
    if ant.isalnum() or ant==")" or ant=="*":
        if lit.isalnum() or lit=="(":
            while (len(stiva)>0 and op[stiva[-1]]>=op['.']):
                output+=stiva.pop()
            stiva.append('.')

    if lit.isalnum():
        output+=lit
    else:
        if lit == '(':
            stiva.append(lit)
        elif lit == ')':
            while stiva[-1] != '(':
                output+=stiva.pop()
            stiva.pop()
        else:
            while (len(stiva)>0 and op[stiva[-1]]>=op[lit]):
                output+=stiva.pop()
            stiva.append(lit)

    ant = lit

while len(stiva) > 0:
    output+=stiva.pop()


stnfa = []
nq = 0
for lit in output:
    if lit.isalnum():
        nfa = {}

        q0 = 'q'+str(nq)
        F = 'q'+str(nq+1)
        nq += 2

        nfa[q0] = {lit: [F]}
        nfa[F] = {}
        stnfa.append((nfa, q0, F))
        
    elif lit == '.':
        nfa2, q02, F2 = stnfa.pop()
        nfa1, q01, F1 = stnfa.pop()
        
        newnfa  = nfa1.copy()
        newnfa.update(nfa2)

        if 'λ' not in newnfa[F1]:
            newnfa[F1]['λ'] = []
        newnfa[F1]['λ'].append(q02)

        stnfa.append((newnfa, q01, F2))

    elif lit == '|':
        nfa2, q02, F2 = stnfa.pop()
        nfa1, q01, F1 = stnfa.pop()

        newq0 = 'q'+str(nq)
        newF = 'q'+str(nq+1)
        nq += 2

        newnfa = nfa1.copy()
        newnfa.update(nfa2)
        newnfa[newq0] = {'λ': [q01, q02]}
        if 'λ' not in newnfa[F1]:
             newnfa[F1]['λ'] = []
        if 'λ' not in newnfa[F2]:
             newnfa[F2]['λ'] = []
        newnfa[F1]['λ'].append(newF)
        newnfa[F2]['λ'].append(newF)
        newnfa[newF] = {}

        stnfa.append((newnfa, newq0, newF))

    elif lit == '*':
        nfa, q0, F = stnfa.pop()

        newq0 = 'q'+str(nq)
        newF = 'q'+str(nq+1)
        nq += 2

        newnfa = nfa.copy()
        newnfa[newq0] = {'λ': [q0, newF]}
        if 'λ' not in newnfa[F]:
             newnfa[F]['λ'] = []
        newnfa[F]['λ'].append(q0)
        newnfa[F]['λ'].append(newF)
        newnfa[newF] = {}

        stnfa.append((newnfa, newq0, newF))

nfa, q0, F = stnfa.pop()
with open("output.txt", "w") as fout:
    fout.write("stari: " + str(list(nfa.keys())) + "\n")
    fout.write("stare initiala: " + q0 + "\n")
    fout.write("stare finala: " + F + "\n")

    for q in nfa:
        for lit in nfa[q]:
            for qq in nfa[q][lit]:
                fout.write(q + " --(" + lit + ")--> " + qq + "\n")