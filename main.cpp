/*
Programa que realiza operaciones simples de Hashing en tabla de dispersión y tabla Hash,
cumpliendo con las condiciones especiales de la estructura de datos.
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 22 de noviembre de 2022
*/

#include <iostream>
#include <list>

/* 
  Clase de entradas de tabla de dispersión.
*/
class Entry {
public:
  int key;
  std::string value;

  Entry(int key, std::string value) {
    this->key = key;
    this->value = value;
  }
};

/* 
  Clase de tabla de dispersión, junto con el método de manejo de desbordamiento chain.
*/
class dispersionTable {
  int bucket;
  std::list<Entry> *hashList;
  public:

    /* 
    Constructor de la tabla de dispersión.
    */
    dispersionTable(int bucket){
      if(bucket > 0){
        this->bucket = bucket;
        hashList = new std::list<Entry>[bucket];
      }

      else{
        std::cout << "Valor inválido de bucket" << std::endl << std::endl;
      }
      
    }

    /*
    Función Hash para manejar el desbordamiento por encadenamiento.
    Param: (Entry entries[]) Entradas de la función Hash a insertar. (int n) número de entradas.
    Return: Nada.
    Complejidad de tiempo: O(n), n siendo el número de entradas.
    Complejidad de espacio: O(n).
    */
    void chain(Entry entries[], int n) {
      for(int i = 0; i < n; i++){
        int index = hashFunction(entries[i].key);
        hashList[index].push_back(entries[i]);
      }
    }

    /*
    Función para imprimir la tabla de dispersión.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(B + n), B siendo el bucket y n siendo el número de entradas.
    Complejidad de espacio: O(1).
    */
    void displayDispersionList(){
      std::cout << "Tabla de dispersión:" << std::endl;

      for (int i = 0; i < bucket; i++) {
        std::cout << i << " -> ";
        for (auto x : hashList[i]) {
          std::cout << "(" << x.key << ", " << x.value << ") ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

    /*
    Función para aplicar Hashing a un valor.
    Param: (int key) Valor a realizar hashing.
    Return: int Valor Hashing.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    int hashFunction(int key) { 
      return (key % bucket);
    }
};

/* 
  Clase de tabla de Hash, junto con el método de manejo de desbordamiento quadratic.
*/
class HashTable {
  int size = 0;
  int *hashArray;
  int counter = 0;

public:

  /* 
    Constructor de la tabla de dispersión.
  */
  HashTable(int size) {
    if(size > 0){
      this->size = size;
      hashArray = new int[size];
      for (int i = 0; i < size; i++) {
        hashArray[i] = -1;
      }
    }
      
    else{
      std::cout << "Valor inválido de tamaño" << std::endl << std::endl;
    }
  }

  /* 
  Función Hash para manejar el desbordamiento mediante sondeo cuadrático,
  Param: (int keys) Elementos a insertar. (int n) Número de elementos a insertar.
  Return: Nada.
  Complejidad de tiempo: O(n*l), n siendo el numero a insertar y l siendo el tamaño del array.
  Complejidad de espacio: O(1).
  */
  void quadratic(int keys[], int n) {
 
    for(int i = 0; i < n; i++){
      if (counter == size) {
        std::cout << "Tabla llena." << std::endl << std::endl;
        break;
      }
      
      int hashValue = hashFunction(keys[i]);
    
      if (hashArray[hashValue] == -1) {
        hashArray[hashValue] = keys[i];
        counter++;
      }
  
      else {
        for (int j = 0; j < size; j++) {
          int t = hashFunction(hashValue + j * j);
  
          if (hashArray[t] == -1) {
            hashArray[t] = keys[i];
            counter++;
            break;
          } 
        }
      }
    }
    
    
  }

  /*
    Función para aplicar Hashing a un valor.
    Param: (int key) Valor a realizar hashing.
    Return: int Valor Hashing.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
  */
  int hashFunction(int key) { 
    return (key % size);
  }

  /*
    Función para imprimir la tabla Hash.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(n), n siendo el tamaño del array.
    Complejidad de espacio: O(1).
  */
  void displayHash() {
      std::cout << "Tabla Hash:" << std::endl;
      for (int i = 0; i < size; i++) {
        std::cout << hashArray[i] << " ";
      }
      std::cout << std::endl << std::endl;
  }
    
};

int main() {

  std::cout << "--------------Prueba 1. Tabla Hash con colisiones--------------" << std::endl;
  int num[] = {50, 700, 76, 85, 92, 73, 101};
  int n = 7;
  HashTable table1(n);
  table1.quadratic(num, n);
  table1.displayHash();

  std::cout << "--------------Prueba 2. Tabla de dispersión con colisiones--------------" << std::endl;
  Entry entry1(15, "Juan Carlos"); 
  Entry entry2(27, "Hallo");
  Entry entry3(56, "Elvira");
  Entry entry4(99, "Iris");
  Entry entry5(42, "Jesus");
  Entry entry6(34, "Ozner");
  Entry entry7(1, "Roble");
  Entry entry8(69, "Elizabeth");

  Entry entries[] = {entry1, entry2, entry3, entry4, entry5, entry6, entry7, entry8};
  dispersionTable table2(8);
  table2.chain(entries, 8);
  table2.displayDispersionList();

  std::cout << "--------------Prueba 3. Tabla Hash sin colisiones--------------" << std::endl;

  int num2[] = {60, 33, 7, 26, 17, 46};
  n = 6;
  HashTable table3(n);
  table3.quadratic(num2, n);
  table3.displayHash();

  std::cout << "--------------Prueba 4. Tabla de dispersión sin colisiones--------------" << std::endl;
  Entry entry9(43, "Fantasma"); 
  Entry entry10(25, "Pedrito");
  Entry entry11(8, "Taskete");
  Entry entry12(82, "Okidokie");

  Entry entries2[] = {entry9, entry10, entry11, entry12};
  dispersionTable table4(4);
  table4.chain(entries2, 4);
  table4.displayDispersionList();


  std::cout << "--------------Prueba 5. Errores--------------" << std::endl;
  dispersionTable tablePrueba1(0);
  HashTable tablePrueba2(0);
  HashTable tablePrueba3(2);
  int num3[] = {24, 84, 1, 8};
  tablePrueba3.quadratic(num2, 4);
  tablePrueba3.displayHash();
  return 0;
}