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

// Algoritmo DR1
void multiplicarDR1(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    int mitad = n / 2;
    vector<vector<int>> C11(mitad, vector<int>(mitad));
    vector<vector<int>> C12(mitad, vector<int>(mitad));
    vector<vector<int>> C21(mitad, vector<int>(mitad));
    vector<vector<int>> C22(mitad, vector<int>(mitad));
    
    // Calcular las submatrices Cij
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C11[i][j] = A[i][j] * B[i][j] + A[i][j + mitad] * B[i + mitad][j];
            C12[i][j] = A[i][j] * B[i][j + mitad] + A[i][j + mitad] * B[i + mitad][j + mitad];
            C21[i][j] = A[i + mitad][j] * B[i][j] + A[i + mitad][j + mitad] * B[i + mitad][j];
            C22[i][j] = A[i + mitad][j] * B[i][j + mitad] + A[i + mitad][j + mitad] * B[i + mitad][j + mitad];
        }
    }
    
    // Combinar los resultados en la matriz C
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
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
    
    // Medir el tiempo de ejecución del algoritmo DR1
    auto start = high_resolution_clock::now();
    multiplicarDR1(A, B, C, n);
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de ejecucion (Algoritmo DR1): " << duration.count() << " ms" << endl;
    
    return 0;
}
