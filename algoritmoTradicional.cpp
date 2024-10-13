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

// Algoritmo tradicional
void multiplicarTradicional(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
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
    
    // Medir el tiempo de ejecución del algoritmo tradicional
    auto start = high_resolution_clock::now();
    multiplicarTradicional(A, B, C, n);
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de ejecucion (Algoritmo Tradicional): " << duration.count() << " ms" << endl;
    
    return 0;
}
