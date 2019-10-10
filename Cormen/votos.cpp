#include <iostream>

#define ELECTORES 160

using namespace std;

struct voto {
    int candidato = 0;
};

int main() {
    int candidatos[3] = {0};
    voto votos[ELECTORES] = {
        // aqui van los votos
    };

    for (int i = 0; i < ELECTORES; i++) {
        candidatos[votos[i].candidato]++;
    }
    int max = 1;
    if (candidatos[0] > candidatos[1]) {
        candidatos[1] = candidatos[0];
        max = 0;
    }
    if (candidatos[2] > candidatos[1]) {
        candidatos[1] = candidatos[2];
        max = 2;
    }
    cout << "El candidato ganador es " << max << endl;

    return 0;
}