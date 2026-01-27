#include <iostream>

using namespace std;

float **producto_matriz(float **A, float **B, int n, int m, int p){
    float **C = new float*[n];
    for(int i = 0; i < n; i++){
        C[i] = new float[p];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            C[i][j] = 0;
            for(int k = 0; k < m; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
    
}

bool matriz_positiva(float **matriz,float *vector, int n){
    float *resultado = producto_matriz(matriz,vector,n,n,1);
    float resultado_final = producto_matriz(resultado,vector,n,1,1);
    if(resultado_final > 0){
        return true;
    }
    return false;
}

int main() {

    return 0;
}
