#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

float preserveB = 0.3;
float preserveR = 0.2;
float mutationR = 0.02;
int tests = 200; // entre más tests, mejores resultados
int pbsz = 20;

float f(float x) { return (x) * (x); }

bool random() { return rand() % 2; }

int random(int min, int max) { return min + (rand() % (max - min + 1)); }

vector<bool> generar(int n = 10) {
    vector<bool> cromosoma;
    for (int i = 0; i < 10; ++i) {
        cromosoma.push_back(random());
    }
    return cromosoma;
}

vector<vector<bool>> generarpob(int sz = 20, int n = 10) {
    vector<vector<bool>> pob;
    for (int i = 0; i < sz; i++) {
        pob.push_back(generar(n));
    }
    return pob;
}

float evaluar(vector<bool> individuo) {
    float signo = (individuo[0]) ? -1 : 1;
    float entero = 0;
    float decimal = 0;
    float pot = 1;
    for (int i = 1; i <= 3; i++) {
        entero += individuo[i] * pot;
        pot *= 2;
    }
    pot = 1;
    for (int i = 4; i < individuo.size(); i++) {
        decimal += individuo[i] * pot;
        pot *= 2;
    }
    decimal /= 63;
    // cout << "t: " << (entero + decimal) * signo << endl;
    return (entero + decimal) * signo;
}

void mutar(vector<bool> &individuo) {
    int idx = random(0, individuo.size() - 1);
    individuo[idx] = !individuo[idx];
}

float fitness(vector<bool> individuo) { return abs(f(evaluar(individuo))); }

vector<bool> cruce_(vector<bool> i1, vector<bool> i2) {
    int idx = random(0, i1.size() - 1);
    vector<bool> hijo;
    for (int i = 0; i < idx; i++) {
        hijo.push_back(i1[i]);
    }
    for (int i = idx; i < i2.size(); i++) {
        hijo.push_back(i2[i]);
    }
    return hijo;
}

vector<bool> cruce__(vector<bool> i1, vector<bool> i2) {
    //int idx = random(0, i1.size() - 1);
    vector<bool> hijo;
    for (int i = 0; i < i2.size(); i++) {
        hijo.push_back(i2[i] && i1[i]);
    }
    return hijo;
}

vector<bool> cruce(vector<bool> i1, vector<bool> i2) {
    int idx = random(0, i1.size() - 1);
    vector<bool> hijo;
    for (int i = 0; i < idx; i++) {
        hijo.push_back(i1[i]);
    }
    for (int i = idx; i < i2.size(); i++) {
        hijo.push_back(i2[i] && i1[i]);
    }
    return hijo;
}

struct fitidx {
    fitidx() {}
    int idx;
    float fitness;

    bool operator<(const fitidx &a2) { return fitness < a2.fitness; }
};

vector<vector<bool>> seleccion(vector<vector<bool>> pob) {
    vector<fitidx> fval;
    fitidx a;
    for (int i = 0; i < pob.size(); i++) {
        a.idx = i;
        a.fitness = (float)fitness(pob[i]);
        fval.push_back(a);
    }
    sort(begin(fval), end(fval));
    vector<vector<bool>> res;
    vector<bool> revs(pob.size(), false);

    for (int i = 0; i < pob.size() * preserveB; i++) {
        res.push_back(pob[fval[i].idx]);
        revs[i] = true;
    }
    for (int i = 0; i < pob.size() * preserveR; i++) {
        int idx = random(0, pob.size() - 1);
        revs[idx] = true;
        res.push_back(pob[fval[idx].idx]);
    }
    int i = 0;
    while (res.size() < pob.size()) {
        int idx2 = random(0, (res.size() - 1));
        res.push_back(cruce(res[i], res[idx2]));
        i++;
    }

    for (int i = 0; i < res.size(); i++) {
        int pos = random(1, 100);
        if (pos <= mutationR * 100) {
            mutar(res[i]);
        }
    }
    return res;
}

float pfitness(vector<vector<bool>> pob) {
    float t = 0;
    for (int i = 0; i < pob.size(); ++i) {
        t += fitness(pob[i]);
    }
    return t / pob.size();
}

float mfitness(vector<vector<bool>> pob) {
    float min = numeric_limits<float>::max();
    for (vector<bool> &i : pob) {
        float f = fitness(i);
        if (f < min) {
            min = f;
        }
    }
    return min;
}

int main() {
    vector<bool> min;
    int pmin = 99999999;
    int it = 0;
    srand(time(NULL));
    for (int i = 0; i < tests; i++) {
        vector<vector<bool>> pob = generarpob(pbsz);
        do {
            it++;
            pob = seleccion(pob);
        } while (pfitness(pob) > fitness(pob[0]));  // evaluar convergencia
        if (fitness(pob[0]) < pmin) { // Se toma al mejor individuo de la convergencia (heurística para intentar asegurar mínimo global)
                                      // compensa la baja cantidad de genes
            pmin = fitness(pob[0]);
            min = pob[0];
        }
    }

    cout << "Cromosoma resultante: " << '\n';
    for (int i = 0; i < min.size(); ++i) {
        cout << min[i] << ' ';
    }
    cout << '\n' << "Valor para x: " << evaluar(min);
    cout << '\n' << "Iteraciones: " << it;
    cout << '\n' << "Iteraciones(prom.): " << it / tests;
}
