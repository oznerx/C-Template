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

class Hash {
  int BUCKET;
  list<Entry> *table;

public:
  Hash(int b);
  void insertItem(int key, string value);
  void deleteItem(int key);
  string searchItem(int key);
  int hashFunction(int x) { return (x % BUCKET); }
  void displayHash();
};

Hash::Hash(int b) {
  this->BUCKET = b;
  table = new list<Entry>[BUCKET];
}

void Hash::insertItem(int key, string value) {
  Entry entry(key, value);

  int index = hashFunction(key);
  table[index].push_back(entry);
}

void Hash::deleteItem(int key) {
    /*
  int index = hashFunction(key);
  list<Entry> list = table[index];
  std::list<Entry>::iterator it;

  for (it = list.begin(); it != list.end(); ++it) {
    if (it->key == key) {
      list.erase(it);
      break;
    }
  }
  */
}

string Hash::searchItem(int key) {
  int index = hashFunction(key);
  list<Entry> list = table[index];
  std::list<Entry>::iterator it;

  for (it = list.begin(); it != list.end(); ++it) {
    if (it->key == key) {
      return it->value;
    }
  }
  return "NO SE ENCONTRÓ";
}

void Hash::displayHash() {
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

int main() {
  int a[] = {100, 119, 367, 49, 116, 3};
  int n = 6;
  Hash h(8);
  for (int i = 0; i < n; i++)
    h.insertItem(a[i], "TEST" + to_string(i));
  h.displayHash();

  cout << h.searchItem(49) << "\n";
  cout << h.searchItem(1) << "\n";


  return 0;
}