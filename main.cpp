

#include<iostream>
#include <list>
using namespace std;
class Hash {
    int BUCKET;
    list < int >* table;
public:
    Hash(int V);
    void insertItem(int x);
    void deleteItem(int key);
    int hashFunction(int x) {
        return (x % BUCKET);
    }
    void displayHash();
};
Hash::Hash(int b) {
    this->BUCKET = b;
    table = new list < int >[BUCKET];
}
void Hash::insertItem(int key) {
}
void Hash::deleteItem(int key) {
}
void Hash::displayHash() {
}
int main() {
    int a[] = { 100, 119, 367, 49, 116,3 };
    int n = 6;
    Hash h(8);
    for (int i = 0; i < n; i++)
        h.insertItem(a[i]);
    h.displayHash();

    h.deleteItem(119);
    h.displayHash();


    return 0;
}
