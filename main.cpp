#include <iostream>
#include <list>
#include <string>
#include <array>
#include <iterator>

using namespace std;

class Entry {
public:

    int key;
    string value;

    Entry(int key, string value) {
        this->key = key;
        this->value = value;
    }

};

class DispersionTable {

  int BUCKET; // size 
  list<Entry> *table;

public:

    DispersionTable(int n) {
        this->BUCKET = n;
        table = new list<Entry>[BUCKET];
    }

    void insertItem(int key, string value) {
        Entry entry(key, value);

        int index = DispersionTableFunction(key);
        table[index].push_back(entry);
    }

    void deleteItem(int key) {
        // Stuff 
    }

    string searchItem(int key) {

        int index = DispersionTableFunction(key);
        list<Entry> list = table[index];
        std::list<Entry>::iterator it;

        for (it = list.begin(); it != list.end(); ++it) {
            if (it->key == key) {
            return it->value;
            }
        }

        return "No se encontró";

    }

    int DispersionTableFunction(int x) { 
        return (x % BUCKET); 
    }

    void displayDispersionTable() {
        
        for (int i = 0; i < BUCKET; i++) {
            std::cout << i;

            list<Entry> list = table[i];
            std::list<Entry>::iterator it;

            for (it = list.begin(); it != list.end(); ++it) {
                std::cout << "->" << "(" << it->key << "," << it->value << ")";
            }

            std::cout << "\n";

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
            cout << "La posición " << i << " contiene: " << table[i] << "\n";
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

        // En este "for" no es "BUCKET", es el número de elementos a insertar 
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
    /*
    int a[] = {100, 119, 367, 49, 116, 3};
    int n = 6;
    DispersionTable h(8);

    for (int i = 0; i < n; i++) {
    h.insertItem(a[i], "TEST" + to_string(i));
    h.displayDispersionTable();
    }


    cout << h.searchItem(49) << "\n";
    cout << h.searchItem(1) << "\n";

    */

    HashTable h(7);
    int elements[] = {50, 700, 76, 85, 92, 73, 101};
    int n = 7; // number of elements to insert
    h.quadratic(n , elements);
    h.display();

}

/*
Referencias: 

    GeeksforGeeks. (2022, September 20). Quadratic Probing in Hashing. https://www.geeksforgeeks.org/quadratic-probing-in-hashing.

*/