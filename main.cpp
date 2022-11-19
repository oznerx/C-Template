#include <iostream>
#include <list>
#include <string>
#include <array>
#include <iterator>
#include <vector>

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

    /*
    Constructor de la tabla de dispersión
    @Param: (int n) tamaño de la tabla 
    Salida: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
    */
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
    Complejidad de tiempo: O(b) siendo b el tamaño del arreglo
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
    B
    @Param:
    Salida:
    Complejidad de tiempo: O(b + n) siendo b el tamaño del arreglo y n el número de elementos insertados en la tabla  
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

    void insertItem(Entry entry) {
        int index = DispersionTableFunction(entry.key);
        table[index].push_back(entry);
    }

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

    int hashFunction(int x) {
        return (x % BUCKET);
    }

    void display() {
        for (int i = 0; i < BUCKET; i++) {
            std::cout << i << " -> " << table[i] << "\n";
        }
    }

    void loadTable() {
        for (int i = 0; i < BUCKET; i++) {
            table[i] = -1;
        }
    }

    void insertItem(int item) {

        if (memoryUsed != BUCKET) {
            int key = hashFunction(item);
            table[key] = item;
            memoryUsed++;
        }

        std::cout << "Ya no hay espacio disponible\n";
    }

    /*
    Time: O(N * B) N is the number of elements to insert, B is the size of the hash table 
    Space: O(1)
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

    std::cout << "\n============ Dispersion Table ============\n\n"; 
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

    std::cout << "\n=============== Hash Table ===============\n\n"; 
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