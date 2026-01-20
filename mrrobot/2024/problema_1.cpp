#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

float **CrearMatriz(int rows, int cols) {
  float **matriz = new float *[rows];
  for (int i = 0; i < rows; i++) {
    matriz[i] = new float[cols];
  }
  return matriz;
}

void LlenarMatriz(float **matriz, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matriz[i][j] = static_cast<float>(rand() % 10);
    }
  }
}

void ImprimirMatriz(float **matriz, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

void LiberarMatriz(float **matriz, int rows) {
  for (int i = 0; i < rows; i++) {
    delete[] matriz[i];
  }
  delete[] matriz;
}

float **ProductoKronecker(float **matriz1, float **matriz2, int rows1,
                          int cols1, int rows2, int cols2) {
  float **matriz3 = CrearMatriz(rows1 * rows2, cols1 * cols2);
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      for (int k = 0; k < rows2; k++) {
        for (int l = 0; l < cols2; l++) {
          // PARTE IMPORTANTE!
          matriz3[i * rows2 + k][j * cols2 + l] = matriz1[i][j] * matriz2[k][l];
        }
      }
    }
  }
  return matriz3;
}

float **ProductoKronecker_v2(float **matriz1, float **matriz2, int rows1,
                             int cols1, int rows2, int cols2) {
  float **matriz3 = CrearMatriz(rows1 * rows2, cols1 * cols2);
  for (int i = 0; i < rows1 * rows2; i++) {
    for (int j = 0; j < cols1 * cols2; j++) {
      // PARTE IMPORTANTE!
      matriz3[i][j] =
          matriz1[i / rows1][j / cols1] * matriz2[i % rows2][j % cols2];
    }
  }
  return matriz3;
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  int rows = 2, cols = 2;
  cout << "Matriz 1: " << endl;
  float **matriz = CrearMatriz(rows, cols);
  LlenarMatriz(matriz, rows, cols);
  ImprimirMatriz(matriz, rows, cols);

  cout << "Matriz 2: " << endl;
  float **matriz2 = CrearMatriz(rows, cols);
  LlenarMatriz(matriz2, rows, cols);
  ImprimirMatriz(matriz2, rows, cols);

  float **matriz3 = ProductoKronecker(matriz, matriz2, rows, cols, rows, cols);
  cout << "Matriz 3: " << endl;
  ImprimirMatriz(matriz3, rows * rows, cols * cols);

  LiberarMatriz(matriz, rows);
  LiberarMatriz(matriz2, rows);
  LiberarMatriz(matriz3, rows * rows);

  return 0;
}