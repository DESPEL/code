from math import sqrt

int pasos[100000] = {-2}

def cantAlgoritmo(int &s, int &query, map<int, int> &index):
    int indice = index[query]
    int pasos = 0

    if (indice == 0):
        return -1

    if (indice % s == 0):
        return indice // s

    pasos += (indice // s) + 2
    pasos += indice % s

    return pasos
    
n=input()
q=input()
map<int, int> index

for i in range (0,n):
    temp = input()
    index[temp] = i + 1

n = sqrt(n)

for  i in range (0,q): 
    temp=input()
    if (pasos[temp] == -2)
        pasos[temp] = cantAlgoritmo(n, temp, index)
        print(pasos[temp])
        print()
    