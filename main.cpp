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

    DispersionTable(int n) {
        this->BUCKET = n;
        table = new std::list<Entry>[BUCKET];
    }

    int DispersionTableFunction(int x) { 
        return (x % BUCKET); 
    }

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

    void display() {
        
        for (int i = 0; i < BUCKET; i++) {
            
            std::cout << i << " -> ";

            for (auto it : table[i]) {
                std::cout << "(" << it.key << "," << it.value << ")" << " ";
            }

            std::cout << "\n";

        }

    }

    void chain(std::vector<std::pair<int,std::string>> entries) {

        for (auto i : entries) {
            Entry entry(i.first, i.second);
            int index = DispersionTableFunction(i.first);
            table[index].push_back(entry);
        }

    }

    //con arreglo de entries
    void chainarr(int n, Entry entries[]) {

        for (int i = 0; i < n; i++) {
            int index = DispersionTableFunction(entries[i].key);
            table[index].push_back(entries[i]);
        }

    }
};

class HashTable {

    int BUCKET;
    int *table;

public:

    HashTable(int n) {
        this->BUCKET = n;
        this->table = new int [n];
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
            }

            else {

                for (int j = 0; j < BUCKET; j++) {

                    key = hashFunction(elements[i]) + (j*j);
                    
                    if (table[key] == -1) {
                        table[key] = elements[i];
                        break;
                    }

                }

            }

        }

    }

};

int main() {

    /*int a[] = {50, 700, 76, 85, 92, 73, 101};
    int dtn = 6;
    DispersionTable h(8);

    for (int i = 0; i < dtn; i++) {
        h.insertItem(a[i], "TEST" + to_string(i));
    }
    
    h.displayDispersionTable();


    cout << h.searchItem(49) << "\n";
    cout << h.searchItem(1) << "\n";*/

    std::cout << "\n============ Dispersion Table ============\n\n"; 

    Entry entry1({50,"caballo"});
    Entry entry2({700, "perro"});
    Entry entry3({76, "gato"});
    Entry entry4({85, "cerdo"});
    Entry entry5({92, "vaca"});
    Entry entry6({73, "hámster"});
    Entry entry7({101, "perico"});
    Entry entries[] = {entry1, entry2, entry3, entry4, entry5, entry6, entry7};
    DispersionTable dt(7);
    dt.chainarr(7,entries);
    dt.display();

    
    std::cout << "\n=============== Hash Table ===============\n\n"; 
    HashTable ht(7);
    int elements[] = {50, 700, 76, 85, 92, 73, 101}; // can be changed for a vector
    int elementsNumber = 7; // number of elements to insert
    ht.quadratic(elementsNumber , elements);
    ht.display();

}

/*
Referencias: 

    GeeksforGeeks. (2022, September 20). Quadratic Probing in Hashing. https://www.geeksforgeeks.org/quadratic-probing-in-hashing.

*/