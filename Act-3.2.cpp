#include <iostream>
using namespace std;

/*
Ozner Axel Leyva Mariscal
A01742377
20 de Octubre del 2022
En este programa se realizarán las operaciones de push, top, pop y empty utilizando un 
heap y simulando una fila priorizada de enteros con prioridad de valor mayor.
*/

class priority_queue {

public:

    int heapArray[1000];
    int s = 0;
    
    priority_queue() {

    }

    /*
    Agrega un dato a la fila priorizada
    @Param: (int value) valor que se desea agregar a la fila priorizada  
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void push(int value) {

        heapArray[s] = value; // n space
        s++;

        if (s > 1) {
            swiftUp((s / 2) - 1);
        }

    }

    /*
    Saca de la fila priorizada el dato que tiene mayor prioridad
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void pop() {
        
        int temp = heapArray[s-1];
        heapArray[s-1] = heapArray[0];
        heapArray[0] = temp;
        s--;

        if (s > 1) {
            swiftDown(0);
        }

    }

    /*
    Regresa el valor del dato que esta con mayor prioridad en la fila priorizada.    
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    int top() {

        return heapArray[0];

    }

    /*
    Regresa un valor boleando diciendo si la fila priorizada esta vacía o tiene datos.  
    @Param: nada  
    Salida: (bool) Valor que indica si la fila está vacía. (true si está vacía, false si es que contiene elementos).
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    bool empty() {

        if (s == 0) {
            return true;
        }

        else {
            return false;
        }

    }

    /*
    Regresa la cantidad de datos que tiene la fila priorizada    
    @Param: nada  
    Salida: (int s) cantidad de datos que tiene la fila.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    int size(){

        return s;

    }

    /*
    Intercambia los valores entre dos posiciones dadas de una fila   
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void swap(int x, int y) {
        
        int temp = heapArray[x];
        heapArray[x] = heapArray[y];
        heapArray[y] = temp;

    }

    /*
    Reacomoda elementos de abajo hacia arriba para colocar el nuevo valor en una posición dependiendo su prioridad  
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void swiftUp(int rootIndex) {
        
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
            swiftUp((rootIndex-1)/2);
        }

    }

    /*
    Reacomoda elementos de arriba hacia abajo cuando se elimina la raíz 
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void swiftDown(int rootIndex) {

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

    /*
    Imprime todo los valores que contiene la fila priorizada.
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void print() {

        for (int i = 0; i < s ; i++) {
            cout << heapArray[i] << " ";
        }

        cout << "\n";

    }

    /*
    Imprime la cantidad deseada de valores que contiene la fila priorizada.
    @Param: (int fullSize) cantidad de valores a imprimir
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void print(int fullSize) {

        for (int i = 0; i < fullSize ; i++) {
            cout << heapArray[i] << " ";
        }

        cout << "\n";

    }

};

 

 

int main()
{

    priority_queue *heap = new priority_queue();

    cout << "\nVerificando que la lista está vacía...\n\n";

    if (heap->empty()) {
        cout << "La fila está vacía\n\n";
    }

    else {
        cout << "La fila contiene elementos\n\n";
    }  



    cout << "Insertando valores a la fila con el método push...\n\n";

    heap->push(51);
    heap->print();
    heap->push(70);
    heap->print();
    heap->push(81);
    heap->print();
    heap->push(91);
    heap->print();
    heap->push(13);
    heap->print();
    heap->push(12);
    heap->print();
    heap->push(45);
    heap->print();
    heap->push(64);
    heap->print();
    heap->push(93);
    heap->print();
    heap->push(87);
    heap->print();
    cout << "\n" ;

    cout << "Eliminando valores dentro de la fila priorizada... \n\n";

    for (int i; i < 4 ;i++) {

        cout << "Ahora la fila tiene los siguientes valores: ";
        heap->print();

        cout << "El tope de la fila es: "; 
        cout << heap->top() << "\n";

        cout << "El tamaño de la fila priorizada es de: ";
        cout << heap->size() << "\n\n";

        heap->pop();
        
    }

}
