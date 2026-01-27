#include <iostream>
#include <random> 
using namespace  std;

float **coordenadas_aleatorias(int n){
    // 1. Obtener una semilla del hardware
    std::random_device rd; 
    // 2. Inicializar el generador (Mersenne Twister)
    std::mt19937 gen(rd()); 
    
    // 3. Definir el intervalo [min, max] (ambos inclusive)
    float min = -4.0, max = 4.0;
    std::uniform_real_distribution<float> dis(min, max);
   
    float **array = new float*[n];
    for(int i = 0; i < n; i++){
        array[i] = new float[2];
    }

    for (int i = 0; i < n; i++){
       array[i][0] = 0;
       array[i][1] = 0;   
    }
    for (int i = 0; i < n; i++){
        while (true){
            float x = dis(gen);
            float y = dis(gen);
            if (x*x + y*y >= 4 && array[i][0] == 0 && array[i][1] == 0){
               array[i][0] = x;
               array[i][1] = y;
               break;
           }        
        }
    }
    return array;
}

float aproximacion_pi(long long n){
    // 1. Obtener una semilla del hardware
    std::random_device rd; 
    // 2. Inicializar el generador (Mersenne Twister)
    std::mt19937 gen(rd()); 
    
    // 3. Definir el intervalo [min, max] (ambos inclusive)
    float min = -4.0, max = 4.0;
    std::uniform_real_distribution<float> dis(min, max);
    long long dentro = 0;
    for (long long i = 0; i < n; i++){
        float x = dis(gen);
        float y = dis(gen);
        if (x*x + y*y <= 4){
            dentro++;
        }

    }
    return ((float)dentro/n)*16;
}

int main(){
    //float **array = coordenadas_aleatorias(5);
    //for(int i = 0; i < 5; i++){
    //    cout << array[i][0] << " " << array[i][1] << endl;
    //}
    cout << aproximacion_pi(5000000) << endl;
    return 0;
}