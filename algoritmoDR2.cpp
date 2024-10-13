#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Generar matrices aleatorias
void generarMatriz(vector<vector<int>>& matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % 100;
        }
    }
}

// Algoritmo DR2
void multiplicarDR2(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    int mitad = n / 2;

    vector<vector<int>> M(mitad, vector<int>(mitad));
    vector<vector<int>> N(mitad, vector<int>(mitad));
    vector<vector<int>> O(mitad, vector<int>(mitad));
    vector<vector<int>> P(mitad, vector<int>(mitad));
    vector<vector<int>> Q(mitad, vector<int>(mitad));
    vector<vector<int>> R(mitad, vector<int>(mitad));
    vector<vector<int>> S(mitad, vector<int>(mitad));
    
    // Calcular M, N, O, P, Q, R, S
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            M[i][j] = (A[i][j] + A[i + mitad][j + mitad]) * (B[i][j] + B[i + mitad][j + mitad]);
            N[i][j] = (A[i + mitad][j] + A[i + mitad][j + mitad]) * B[i][j];
            O[i][j] = A[i][j] * (B[i][j + mitad] - B[i + mitad][j + mitad]);
            P[i][j] = A[i + mitad][j + mitad] * (B[i + mitad][j] - B[i][j]);
            Q[i][j] = (A[i][j] + A[i][j + mitad]) * B[i + mitad][j + mitad];
            R[i][j] = (A[i + mitad][j] - A[i][j]) * (B[i][j] + B[i][j + mitad]);
            S[i][j] = (A[i][j + mitad] - A[i + mitad][j + mitad]) * (B[i + mitad][j] + B[i + mitad][j + mitad]);
        }
    }

    // Calcular las submatrices Cij
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i][j] = M[i][j] + P[i][j] - Q[i][j] + S[i][j];
            C[i][j + mitad] = O[i][j] + Q[i][j];
            C[i + mitad][j] = N[i][j] + P[i][j];
            C[i + mitad][j + mitad] = M[i][j] + O[i][j] - N[i][j] + R[i][j];
        }
    }
}

int main() {
    int n = 512;  // Puedes cambiar este valor
    
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> C(n, vector<int>(n));
    
    generarMatriz(A, n);
    generarMatriz(B, n);
    
    // Medir el tiempo de ejecución del algoritmo DR2
    auto start = high_resolution_clock::now();
    multiplicarDR2(A, B, C, n);
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de ejecucion (Algoritmo DR2): " << duration.count() << " ms" << endl;
    
    return 0;
}
