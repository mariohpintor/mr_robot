#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

float *MinSubarray(float array[], int n) {
  float *subarray = new float[n];
  for (int i = 0; i < n; i++)
    subarray[i] = 0;

  vector<float> negativos;
  vector<float> positivos;

  // 1. Omitir ceros y separar positivos/negativos
  for (int i = 0; i < n; i++) {
    if (array[i] < 0) {
      negativos.push_back(array[i]);
    } else if (array[i] > 0) {
      positivos.push_back(array[i]);
    }
  }

  // 2. Ordenar los negativos para identificar el más grande (más cercano a
  // cero)
  sort(negativos.begin(), negativos.end());

  // 3. Tomar el máximo número impar de negativos
  // Si hay un número par de negativos, quitamos el que es mayor (ej. -1 es
  // mayor que -10)
  if (!negativos.empty() && negativos.size() % 2 == 0) {
    negativos.pop_back();
  }

  // 4. Llenar el subarray final con todos los positivos y los negativos
  // seleccionados
  int index = 0;
  for (float p : positivos) {
    subarray[index++] = p;
  }
  for (float neg : negativos) {
    subarray[index++] = neg;
  }

  return subarray;
}

int main() {
  // Arreglo estático de prueba
  float array[7] = {-1, 9, -8, -2, 0, 5, -10};
  int n = 7;

  cout << "Arreglo original: " << endl;
  for (int i = 0; i < n; i++) {
    cout << array[i] << " ";
  }
  cout << endl;

  float *subarray = MinSubarray(array, n);

  cout << "Subarray procesado (minimo producto posible): " << endl;
  for (int i = 0; i < n; i++) {
    // Solo imprimimos los que no son cero (según la lógica de "omitir ceros")
    if (subarray[i] != 0) {
      cout << subarray[i] << " ";
    }
  }
  cout << endl;

  // Liberar memoria
  delete[] subarray;

  return 0;
}
