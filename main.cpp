#include <iostream>
#include <list>
#include <string>
#include <array>
#include <iterator>
#include <vector>

/*
Ozner Axel Leyva Mariscal
A01742377
22 de Noviembre del 2022
En este código se implementará una tabla hash y una tabla de dispersión que incluye su técnica 
de hashing así como el manejo de colisiones a través de dirección abierta y sondeo lineal.
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

class DispersionTable {

  int BUCKET;
  std::list<Entry> *table;

public:

    DispersionTable(int n) {
        this->BUCKET = n;
        table = new std::list<Entry>[BUCKET];
    }

    /*
    Aplica una función de hashing a un valor 
    @Param: (int x) valor al cual se le aplicará la función de hashing
    Salida: (int) resultado de la función
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
    */
    int DispersionTableFunction(int x) { 
        return (x % BUCKET); 
    }

    /*
    Busca un valor dentro de la tabla
    @Param: (int key) llave del valor a buscar en la tabla 
    Salida: (string) valor encontrado
    Complejidad de tiempo: O(b) siendo b el tamaño de la tabla
    Complejidad de espacio: O(1) 
    */
    std::string searchItem(int key) {

        int index = DispersionTableFunction(key);
        std::list<Entry> list = table[index];

        for (auto it : list) {

            if (it.key == key) {
                return it.value;
            }

        }

        return "No se encontró";

    }

    /*
    Imprime todos los elementos que contiene la tabla de dispersión
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(b + n) siendo b el tamaño de la tabla y n el número de elementos insertados en la tabla  
    Complejidad de espacio: O(1) 
    */
    void display() {
        
        for (int i = 0; i < BUCKET; i++) {
            
            std::cout << i << " -> ";

            for (auto it : table[i]) {
                std::cout << "(" << it.key << "," << it.value << ")" << " ";
            }

            std::cout << "\n";

        }

    }

    /*
    Inserta un elemento a la tabla de dispersión
    @Param: (Entry entry) elemento a insertar en la tabla de dispersión
    Salida: nada
    Complejidad de tiempo: O(1) 
    Complejidad de espacio: O(1) 
    */
    void insertItem(Entry entry) {
        int index = DispersionTableFunction(entry.key);
        table[index].push_back(entry);
    }

    /*
    Maneja el desbordamiento por encadenamiento e inserta los elementos 
    @Param: (int n) número de elementos a insertar, (Entry entries[]) arreglo que contiene todas los elementos a insertar 
    Salida: nada
    Complejidad de tiempo: O(n) siendo n el número de elementos a insertar 
    Complejidad de espacio: O(n) siendo n el número de elementos a insertar
    */
    void chain(int n, Entry entries[]) {

        for (int i = 0; i < n; i++) {
            insertItem(entries[i]);
        }

    }

};

class HashTable {

    int BUCKET;
    int *table;
    int memoryUsed;

public:

    HashTable(int n) {
        this->BUCKET = n;
        this->table = new int [n];
        this->memoryUsed = 0;
    }

    /*
    Aplica una función de hashing a un valor 
    @Param: (int x) valor al cual se le aplicará la función de hashing
    Salida: (int) resultado de la función
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
    */
    int hashFunction(int x) {
        return (x % BUCKET);
    }

    /*
    Imprime todos los elementos que contiene la tabla de hash
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(b) siendo b el tamaño de la tabla
    Complejidad de espacio: O(1) 
    */
    void display() {
        for (int i = 0; i < BUCKET; i++) {
            std::cout << i << " -> " << table[i] << "\n";
        }
    }

    /*
    Inicializa los valores de la tabla como -1
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(b) siendo b el tamaño de la tabla  
    Complejidad de espacio: O(1) 
    */
    void loadTable() {
        for (int i = 0; i < BUCKET; i++) {
            table[i] = -1;
        }
    }

    /*
    Inserta un elemento a la tabla de hash
    @Param: (int item) elemento a insertar en la tabla de hash
    Salida: nada
    Complejidad de tiempo: O(1) 
    Complejidad de espacio: O(1) 
    */
    void insertItem(int item) {

        if (memoryUsed != BUCKET) {
            int key = hashFunction(item);
            table[key] = item;
            memoryUsed++;
        }

        std::cout << "Ya no hay espacio disponible\n";
    }

    /*
    Maneja el desbordamiento por sondeo cuadrático e inserta los elementos 
    @Param: (int n) número de elementos a insertar, (int elements[]) arreglo que contiene todas los elementos a insertar 
    Salida: nada
    Complejidad de tiempo: O(b * n) siendo b el tamaño de la tabla, siendo n el número de elementos a insertar 
    Complejidad de espacio: O(1)
    */
    void quadratic(int n, int elements[]) {

        loadTable();

        for (int i = 0; i < n; i++) {

            int key = hashFunction(elements[i]) + (i*i);

            if (table[key] == -1) {
                table[key] = elements[i];
                memoryUsed++;
            }

            else {

                for (int j = 0; j < BUCKET; j++) {

                    key = hashFunction(elements[i]) + (j*j);
                    
                    if (table[key] == -1 && (memoryUsed != BUCKET)) {
                        table[key] = elements[i];
                        memoryUsed++;
                        break;
                    }

                }

            }

        }

    }

};

int main() {

    std::cout << "\n============ Tabla de Dispersión ============\n"; 
    Entry entry1({50,"caballo"});
    Entry entry2({700, "perro"});
    Entry entry3({76, "gato"});
    Entry entry4({85, "cerdo"});
    Entry entry5({92, "vaca"});
    Entry entry6({73, "hámster"});
    Entry entry7({101, "perico"});
    Entry entries[] = {entry1, entry2, entry3, entry4, entry5, entry6, entry7};
    int entriesNumber = 7;
    DispersionTable dt(entriesNumber);
    dt.chain(entriesNumber,entries);
    dt.display();

    std::cout << "\n=============== Tabla de Hash ===============\n"; 
    HashTable ht(7);
    int elements[] = {50, 700, 76, 85, 92, 73, 101}; 
    int elementsNumber = 7; 
    ht.quadratic(elementsNumber , elements);
    ht.display();

}

/*
Referencias: 

    GeeksforGeeks. (2022, September 20). Quadratic Probing in Hashing. https://www.geeksforgeeks.org/quadratic-probing-in-hashing.

*/