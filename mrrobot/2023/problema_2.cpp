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

float producto(float **A, float vector[],int n){
    float vec[n];
    for (int i= 0; i < n; i++){
        vec[i] = 0;
        for(int j= 0; j < n ; j++ ){
            vec[i]+= A[i][j]*vector[j];
        } 
    }
    float res = 0;
    for (int i = 0; i < n; i++ ){
        res+= vec[i]*vector[i];
    }
    return res;
}



int main() {
    int n = 2;
    float **A = new float*[n];
    for(int i = 0; i < n; i++){
        A[i] = new float[n];
    }
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;
    float vector[2] = {-1,1};

    cout << producto(A,vector,n)<< endl;
    return 0;
}
