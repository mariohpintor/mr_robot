#include <iostream>

using namespace std;

// Estructura para el Nodo de la lista
struct Nodo {
  int dato;
  Nodo *siguiente;

  // Constructor simple para inicializar el nodo
  Nodo(int valor) {
    dato = valor;
    siguiente = nullptr;
  }
};

// Clase para la Lista Ligada
class ListaLigada {
private:
  Nodo *cabeza; // Puntero al primer elemento

public:
  // Constructor: al inicio la lista está vacía
  ListaLigada() { cabeza = nullptr; }

  // Método para insertar al final
  void insertar(int valor) {
    Nodo *nuevo = new Nodo(valor);

    // Si la lista está vacía, el nuevo nodo es la cabeza
    if (cabeza == nullptr) {
      cabeza = nuevo;
    } else {
      // Recorrer hasta el final
      Nodo *temp = cabeza;
      while (temp->siguiente != nullptr) {
        temp = temp->siguiente;
      }
      // Conectar el último nodo al nuevo
      temp->siguiente = nuevo;
    }
  }

  // Método para mostrar la lista
  void mostrar() {
    Nodo *temp = cabeza;
    while (temp != nullptr) {
      cout << temp->dato << " -> ";
      temp = temp->siguiente;
    }
    cout << "NULL" << endl;
  }
  // ###########################
  //  Método para invertir la lista
  void invertir() {
    Nodo *anterior = nullptr;
    Nodo *actual = cabeza;
    while (actual != nullptr) {
      Nodo *siguiente = actual->siguiente;
      actual->siguiente = anterior;
      anterior = actual;
      actual = siguiente;
    }
    cabeza = anterior;
  }
  // ###########################

  // Destructor: IMPORTANTE para liberar la memoria
  ~ListaLigada() {
    Nodo *actual = cabeza;
    while (actual != nullptr) {
      Nodo *siguiente = actual->siguiente;
      delete actual;
      actual = siguiente;
    }
  }
};

int main() {
  ListaLigada lista;

  // Insertar algunos datos
  lista.insertar(10);
  lista.insertar(75);
  lista.insertar(50);
  lista.insertar(40);

  // Mostrar la lista
  cout << "Contenido de la lista: " << endl;
  lista.mostrar();

  // Invertir la lista
  lista.invertir();

  // Mostrar la lista invertida
  cout << "Contenido de la lista invertida: " << endl;
  lista.mostrar();

  return 0;
}
