#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Encuentra el tamaño del menor subarreglo cuya suma es > S.
 * Complejidad temporal: O(N)
 * Complejidad espacial: O(1)
 */
int menorSubarreglo(const std::vector<int>& arreglo, long long S) {
    int n = arreglo.size();
    int min_len = n + 1; // Inicializamos con un valor imposible
    long long suma_actual = 0;
    int inicio = 0;

    for (int fin = 0; fin < n;++fin) {
        std::cout << fin << std::endl; 
        suma_actual += arreglo[fin];

        // Mientras la condición se cumpla, intentamos reducir la ventana
        while (suma_actual > S) {
            // Actualizamos el tamaño mínimo encontrado
            min_len = std::min(min_len, fin - inicio + 1);
            
            // Restamos el valor en 'inicio' y movemos el puntero
            suma_actual -= arreglo[inicio];
            inicio++;
        }
    }

    // Si min_len nunca cambió, no se encontró ningún subarreglo válido
    return (min_len == n + 1) ? -1 : min_len;
}

int main() {
    // Ejemplo de uso
    //std::vector<int> nums = {2, 3, 1, 2, 4, 3};
    //long long S = 7;

    std::vector<int> nums = { 8, 20, 15, 17, 12 };
    long long S = 34;
    

    int resultado = menorSubarreglo(nums, S);

    if (resultado != -1) {
        std::cout << "El tamaño del menor subarreglo es: " << resultado << std::endl;
    } else {
        std::cout << "No existe un subarreglo que sume más de " << S << std::endl;
    }

    return 0;
}