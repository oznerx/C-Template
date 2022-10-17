#include <iostream>
using namespace std;

class Heap {

public:

    int heapArray[1000];
    int s = 0;
    
    Heap() {

    }

    void push(int value) {

        heapArray[s] = value;
        s++;

        if (s > 1) {
            swiftUp((s / 2) - 1);
        }

    }

    void pop() {
        
        int temp = heapArray[s - 1];
        heapArray[s-1] = heapArray[0];
        heapArray[0] = temp;
        s--;

        if (s > 1) {
            swiftDown(0);
        }

    }

    void swap(int x, int y) {
        
        int temp = heapArray[x];
        heapArray[x] = heapArray[y];
        heapArray[y] = temp;

    }


    void  swiftUp(int rootIndex) {
        
        int max = rootIndex;
        int left = (2 * rootIndex) + 1;
        int right = (2 * rootIndex) + 2;

        if (left<s&&heapArray[max] < heapArray[left]) {
            max = left;
        }

        if (right < s && heapArray[max] < heapArray[right]) {
            max = right;
        }

        if (max != rootIndex) {
        
            swap(max, rootIndex);
            swiftUp((rootIndex-1)/2);
        }

    }

    void  swiftDown(int rootIndex) {

        int max = rootIndex;
        int left = (2 * rootIndex) + 1;
        int right = (2 * rootIndex) + 2;

        if (left < s && heapArray[max] < heapArray[left]) {
            max = left;
        }

        if (right < s && heapArray[max] < heapArray[right]) {
            max = right;
        }

        if (max != rootIndex) {
            swap(max, rootIndex);
            swiftDown(max);
        }

    }

    void print() {

        for (int i = 0; i < s; i++) {
            cout << heapArray[i] << " ";
        }

        cout << endl;

    }

    void print(int fullSize) {

        for (int i = 0; i < fullSize; i++) {
            cout << heapArray[i] << " ";
        }

        cout << "\n";
    }

    void top() {

    }

    void empty() {

    }

    void size(){

    }

};

 

 

int main()
{
    Heap *heap = new Heap();
    heap->push(5);
    heap->push(7);
    heap->push(8);
    heap->push(9);
    heap->push(10);
    heap->push(12);
    heap->push(5);
    heap->print();
  //  heap->add(90);
  //  heap->add(10);
  //  heap->add(5);
  //  heap->add(2);
    heap->pop();
    heap->print();
    heap->pop();
    heap->print();
    heap->pop();
    heap->print();
    heap->pop();
    heap->print();
    heap->pop();
    heap->print();
    heap->pop();
 

    heap->print();
    heap->print(7);

}
