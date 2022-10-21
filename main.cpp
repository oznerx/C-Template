/*
Programa que realiza operaciones básicas de un Heap, 
cumpliendo con las condiciones especiales de la estructura de datos.
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 18 de octubre de 2022 */

#include <iostream>
#include <vector>

/*
Base del Heap. Contiene las operaciones fundamentales de un Heap.
*/
class Heap{
  int amount = 0;
  int *heapArray;
  int capacity;
  public:

    /* Constructor del Heap.
    Param: (int tam) Tamaño del Heap.
    Return: Nada.
    */
    Heap(int tam){
      heapArray = new int[tam];
      capacity = tam;
    }

    /* Inserta un elemento al Heap.
    Param: (int data) Valor del dato a insertar en el Heap.
    Return: Nada.
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(logn)
    */
    void push(int data) {
     if(capacity != amount){
       heapArray[amount++] = data;
        
       if(amount > 1){
           swiftUp(amount/2 - 1);
       }
     }
       
     else{
       std::cout<<"El Heap esta lleno"<<std::endl;
     }
    }

    /* Elimina un elemento del Heap.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(logn)
    */
    void pop() {
      if(amount != 0){
        amount--;
        swap(heapArray[amount], heapArray[0]);
        
        if (amount > 1) {
          swiftDown(0);
        }
      }

      else{
        std::cout<<"Heap vacío."<<std::endl;
      }
    }

    /* Intercambia valores de dos posiciones de un Heap.
    Param: (int &x) Dirección del primer valor a intercambiar.
    (int &y) Dirección del segundo valor a intercambiar.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void swap(int &x, int &y) {
      int temp = x;
      x = y;
      y = temp;
    }

    /* Ayudante de la función push. 
    Empuja los índices necesarios para cumplir con la prioridad del Heap.
    Param: (int rootIndex) Índice del valor a empujar hacia arriba si es necesario.
    Return: Nada.
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(logn)
    */
    void swiftUp(int rootIndex) {
      int max = rootIndex;
      int left = 2*rootIndex + 1;
      int right = 2*rootIndex + 2;
      if (left < amount && heapArray[max] < heapArray[left]) {
         max = left;
      }
      
      else if (right < amount && heapArray[max] < heapArray[right]) {
         max = right;
      }
      
      if (max != rootIndex) {
         swap(heapArray[max], heapArray[rootIndex]);
         swiftUp((rootIndex - 1) / 2);
      }
    }

    /* Ayudante de la función pop. 
    Empuja los índices necesarios para cumplir con la prioridad del Heap.
    Param: (int rootIndex) Índice del valor a empujar hacia abajo si es necesario.
    Return: Nada.
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(logn)
    */
    void swiftDown(int rootIndex) {
      int max = rootIndex;
      int left = 2*rootIndex + 1;
      int right = 2*rootIndex + 2;
      
      if (left < amount && heapArray[max] < heapArray[left]) {
        max = left;
      }
        
      else if(right < amount && heapArray[max] < heapArray[right]) {
        max = right;
      }
      
      if(max != rootIndex) {
        swap(heapArray[max], heapArray[rootIndex]);
        swiftDown(max);
      }
    }

    /* Checa cuál es el valor arriba del Heap.
    Param: Nada.
    Return: int Valor arriba del Heap.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    int top(){
      if(amount != 0){
        return heapArray[0];
      }
        
      else{
        std::cout<<"Heap vacío."<<std::endl;
        return 0;
      }
    }

    /* Checa si el Heap está vacío.
    Param: Nada.
    Return: bool Estado de vacuidad del Heap.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    bool empty(){
      return amount == 0;
    }

    /* Checa el tamaño del Heap.
    Param: Nada.
    Return: int Tamaño del Heap.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    int size(){
      return amount;
    }

    /* Imprime todo el Heap.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void print() {
      for (int i = 0; i < amount; i++) {
        std::cout << heapArray[i] << " ";
      }
      
      std::cout << std::endl;
    }

};

int main(){
  std::vector<int> num1 = {1, 9, 8, 10, 3, 5, 2, 6, 3, 10, 12, 14, 20, 7, 13};
  Heap *heap = new Heap(15);

  std::cout<<"Probando que el Heap está vacío."<<std::endl;
  if(heap->empty()){
    std::cout<<"El Heap está vacío."<<std::endl;
  }

  else{
    std::cout<<"El Heap no está vacío."<<std::endl;
  }
  std::cout<<std::endl;

  std::cout<<"Prueba de inserción de elementos y diversos funciones del Heap. "<<std::endl;
  for(int i = 0; i < num1.size(); i++){
    std::cout<<"Inserción "<<i + 1<<std::endl;
    heap->push(num1[i]);
    heap->print();
    if(i % 3 == 0){
      std::cout<<"Tamaño actual del Heap: "<<heap->size()<<std::endl;
      std::cout<<"Top actual del Heap: "<<heap->top()<<std::endl;
    }
    std::cout<<std::endl;
  }

  std::cout<<"Probando que el Heap no está vacío."<<std::endl;
  if(heap->empty()){
    std::cout<<"El Heap está vacío."<<std::endl;
  }

  else{
    std::cout<<"El Heap no está vacío."<<std::endl;
  }
  std::cout<<std::endl;

  std::cout<<"Prueba de la eliminación de elementos del Heap."<<std::endl;
  for(int i = 0; i < num1.size(); i++){
    std::cout<<"Eliminación "<<i<<std::endl;
    heap->print();
    heap->pop();
    std::cout<<std::endl;
  }

  std::cout<<"Probando que el Heap está vacío."<<std::endl;
  if(heap->empty()){
    std::cout<<"El Heap está vacío."<<std::endl;
  }

  else{
    std::cout<<"El Heap no está vacío."<<std::endl;
  }
  std::cout<<std::endl;
  
  std::cout<<"Probando la inserción de elementos después de borrar todos los elementos de un Heap."<<std::endl;
  heap->push(5);
  heap->push(10);
  heap->push(15);
  heap->push(20);
  heap->push(6);
  heap->push(8);
  heap->push(16);
  heap->push(30);
  heap->print();
  std::cout<<std::endl;

  std::cout<<"Probando que el Heap no está vacío."<<std::endl;
  if(heap->empty()){
    std::cout<<"El Heap está vacío."<<std::endl;
  }

  else{
    std::cout<<"El Heap no está vacío."<<std::endl;
  }
  std::cout<<std::endl;
  
  return 0;
}