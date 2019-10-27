#include <math.h>
#include <iostream>

using namespace std;

int main() {
    ////2,4,6,8 en las esquinas
    ///7,9,3,1 en las aristas
    /// 5 en el centro
    
    // 2 - 8 esquinas opuestas
    // 4 - 6 esquinas opuestas
    // 5 en el centro
    int tablero[3][3];
    int cost = 0;
    int posibles [8][3][3] = {
        {[8,1,6],[3,5,7],[4,9,2]}
        {[4,3,8],[9,5,1],[2,7,6]}
        {}
        {}
        {}
        {}
        {}
        {}
    }
    
    vector<vector>int 
    /* como no es cuestion de tiempo podirmaos definir todos los cuadros validos
        sacar el valor absoluto de las diferencias con cada uno
        y el devolver el que se menor
        */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int k;
            cin >> k;
            tablero[i][j] = k;
        }
    }

    cost += abs(tablero[1][1] - 5);
    
}