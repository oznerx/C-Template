#include <iostream>
#include <list>
#include <string>

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

class dispersionTable {

  int BUCKET; // size 
  list<Entry> *table;

public:

    dispersionTable(int b) {
        this->BUCKET = b;
        table = new list<Entry>[BUCKET];
    }

    void insertItem(int key, string value) {
        Entry entry(key, value);

        int index = dispersionTableFunction(key);
        table[index].push_back(entry);
    }

    void deleteItem(int key) {
        // Stuff 
    }

    string searchItem(int key) {

        int index = dispersionTableFunction(key);
        list<Entry> list = table[index];
        std::list<Entry>::iterator it;

        for (it = list.begin(); it != list.end(); ++it) {
            if (it->key == key) {
            return it->value;
            }
        }

        return "No se encontró";

    }

    int dispersionTableFunction(int x) { 
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



class hashTable {

  int BUCKET; // size 

public:

  hashTable(int n);
  void insertItem(int key, string value);
  void deleteItem(int key);
  string searchItem(int key);
  int hashTableFunction(int x);
  void displayHashTable();

};

int main() {

  int a[] = {100, 119, 367, 49, 116, 3};
  int n = 6;
  dispersionTable h(8);

  for (int i = 0; i < n; i++) {
    h.insertItem(a[i], "TEST" + to_string(i));
    h.displayDispersionTable();
  }


  cout << h.searchItem(49) << "\n";
  cout << h.searchItem(1) << "\n";


  return 0;
}