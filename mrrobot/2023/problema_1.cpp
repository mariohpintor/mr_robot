#include <iostream>
#include <vector>

using namespace std;

float sin(float x){
    float y = 0;
    x*= 3.14159/180;
    float a = x;
    for (int i = 0; i < 10; i++){
        y += a;
        a *= -x*x/((2*i+2)*(2*i+3));
    }
    return y;
}

float f(float x){
    float y = 0,factor = 2;
    y = sin(x);
    for (int i = 1; i < 10; i++){
        y += (sin(factor*x))/(factor);
        factor*=2;
    }
    return y;
}

vector<float> MiFuncion(float xi, float delta, int n) {
    vector<float> res(n);
    
    for (int i = 0; i < n; i++) {
        res[i] = f(xi + delta * i);
    }
    return res;
}

int main() {
    int n = 10;
    float x = 0;
    float delta = 10;
    cin >> n >> x >> delta;
    vector<float> v = MiFuncion(x,delta, n);
    for (int i = 0; i < n; i++) {
        cout << v[i] << endl;
    }
    //cout << f(0) << endl;
    return 0;
}