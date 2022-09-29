/*
Este programa utiliza tres estructuras de datos lineales: listas 
ligadas, listas doblemente ligadas y listas circulares,
que contienen información del archivo bitácora.txt, para realizar
pruebas con las operaciones básicas CRUD (create, read, update y delete).
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 27 de septiembre de 2022
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*
Es la entidad básica de las estructuras de datos. Se puede contener 
cualquier tipo de datos en ella.
*/
template <class T>
class node{
  T data;
  public:
    node<T>* next;
    node<T>* prev;

    /* Constructor de un nodo. El nodo siguiente y anterior son
    nodos nulos.
    Param: Nada.
    Return: Nada.
    */
    node(){
      next = nullptr;
      prev = nullptr;
    }

    /* Establece el dato del nodo.
    Param: T nuevo dato del nodo.
    Return: Nada.
    */
    void setData(T newData){
      data = newData;
    }

    /* Regresa el dato del nodo.
    Param: Nada.
    Return: T dato del nodo.
    */
    T getData(){
      return data;
    }
};

/*
Esta clase es la base de la lista ligada. Contiene todas las operaciones
CRUD.
Cada nodo, excepto la cola, apunta hacia el siguiente nodo.
*/
template <class T>
class linkedList{
  node<T>* head;
  node<T>* tail;  
  node<T>* current;
  int size = 0;
  public:

    /* Constructor de la lista ligada. El nodo cabeza y cola son nulos.
    Param: Nada.
    Return: Nada.
    */
    linkedList(){
      head = nullptr;
      tail = nullptr;
    }

    /* Operación crear. Inserta un nodo en la estructura de datos.
    Param: T dato del nuevo nodo.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void create(T data){
      node<T>* new_node = new node<T>();
      new_node->setData(data);
      
      if(head == nullptr){
        head = new_node;
        tail = new_node;
        size++;
      }
      
      else{
        tail->next = new_node;
        tail = new_node;
        size++;
      }
    }

    /* Operación leer. Imprime el dato del nodo indicado.
    Param: int índice del nodo a imprimir.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void read(int index){
      if(head != nullptr && (size > index && index >= 0)){
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
        }
        
        std::cout<<"El nodo en la posición "<<index<<" contiene: "<<current->getData()<<std::endl;
        std::cout<<std::endl;
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Operación actualizar. Actualiza el dato del nodo indicado.
    Param: int índice del nodo a modificar. T nuevo dato del nodo.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void update(int index, T newData){
      if(head != nullptr && (size > index && index >= 0)){
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
        }
        
        current->setData(newData);
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Operación eliminar. Elimina el nodo indicado.
    Param: int índice del nodo a eliminar.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(int index){
      if(head != nullptr && (size > index && index >= 0)){
        node<T>* previous = nullptr;
        current = head;
        
        if(index == 0){
          head = current->next;
          free(current);
          size--;
        }
          
        else{
          for(int i = 1; i<=index; i++){
            previous = current;
            current = current->next;
            if(i == size-1){
              tail = previous;
            }
          }
          
          previous->next = current->next;
          free(current);
          size--;
        }
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Imprime todos los datos de la lista.
    Param: Nada.
    Return: Nada.
    */
    void printNodes(){
      current = head;
      
      while(current != nullptr){
        std::cout<<current->getData()<<std::endl;
        current = current->next;
      }
    }

    /* Regresa el tamaño de la lista.
    Param: Nada.
    Return: int tamaño de la lista.
    */
    int getSize(){
      return size - 1;
    }
};

/*
Esta clase es la base de la lista doblemente ligada. 
Contiene todas las operaciones CRUD y una operación especial.
Cada nodo, excepto la cabeza y la cola, apunta hacia el siguiente
nodo y el anterior.
*/
template <class T>
class doubleLinkedList{
  node<T>* head;
  node<T>* tail;  
  node<T>* current;
  int size = 0;
  int i;
  public:

    /* Constructor de la lista doblemente ligada. 
    El nodo cabeza y cola son nulos.
    Param: Nada.
    Return: Nada.
    */
    doubleLinkedList(){
      head = nullptr;
      tail = nullptr;
    }

    /* Operación crear. Inserta un nodo en la estructura de datos.
    Param: T dato del nuevo nodo.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void create(T data){
      node<T>* new_node = new node<T>();
      new_node->setData(data);
      
      if(head == nullptr){
        head = new_node;
        tail = new_node;
        size++;
      }
      
      else{
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
        size++;
      }
    }

    /* Operación leer. Imprime el dato del nodo indicado.
    Param: int índice del nodo a imprimir.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void read(int index){
      if(head != nullptr && (size > index && index >= 0)){
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
        }
        
        std::cout<<"El nodo en la posición "<<index<<" contiene: "<<current->getData()<<std::endl;
        std::cout<<std::endl;
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Operación actualizar. Actualiza el dato del nodo indicado.
    Param: int índice del nodo a modificar. T nuevo dato del nodo.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void update(int index, T newData){
      if(head != nullptr && (size > index && index >= 0)){
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
        }
        
        current->setData(newData);
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Operación eliminar. Elimina el nodo indicado.
    Param: int índice del nodo a eliminar.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(int index){
      if(head != nullptr && (size > index && index >= 0)){
        node<T>* previous = nullptr;
        current = head;
        
        if(index == 0){
          head = current->next;
          free(current);
          size--;
        }
        
        else{
          
          for(int i = 1; i<=index; i++){
            previous = current;
            current = current->next;
            
            /* Caso especial de las listas doblemente ligadas 
            cuando la cola se quiere eliminar*/
            if(i == size - 1){
              tail = previous;
              free(current);
              size--;
              return;
            }
          }
          
          previous->next = current->next;
          current->next->prev = previous;
          free(current);
          size--;
        }
      }
            
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Imprime todos los datos de la lista.
    Param: Nada.
    Return: Nada.
    */
    void printNodes(){
      current = head;
      
      while(current != nullptr){
        std::cout<<current->getData()<<std::endl;
        current = current->next;
      }
    }

    /* Regresa el tamaño de la lista.
    Param: Nada.
    Return: int tamaño de la lista.
    */
    int getSize(){
      return size - 1;
    }

    /* Función especial de la lista doblemente ligada para comprobar
    su funcionalidad. Lee desde la cola de lista.
    Param: int índice (empezando desde la cola) del nodo a imprimir.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)*/
    void readBackwards(int index){
      if(head != nullptr && (size > index && index >= 0)){
        current = tail;
        
        for(i = 1; i<=index; i++){
          current = current->prev;
        }
        
        std::cout<<"El nodo en la posición "<<size - index - 1<<" contiene: "<<current->getData()<<std::endl;
        std::cout<<std::endl;
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }
};

/*
Esta clase es la base de la lista circular. 
Contiene todas las operaciones CRUD y una operación especial.
Cada nodo apunta hacia el siguiente nodo. El último nodo apunta hacia la
cabeza.
*/
template <class T>
class circularList{
  node<T>* head;
  node<T>* tail;  
  node<T>* current;
  int size = 0;
  public:

    /* Constructor de la lista circular. 
    El nodo cabeza y cola son nulos.
    Param: Nada.
    Return: Nada.
    */
    circularList(){
      head = nullptr;
      tail = nullptr;
    }

    /* Operación crear. Inserta un nodo en la estructura de datos.
    Param: T dato del nuevo nodo.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void create(T data){
      node<T>* new_node = new node<T>();
      new_node->setData(data);
      
      if(head == nullptr){
        head = new_node;
        tail = new_node;
        size++;
      }
      
      else{
        tail->next = new_node;
        tail = new_node;
        size++;
      }
      
      tail->next = head;
    }

    /* Operación leer. Imprime el dato del nodo indicado.
    Param: int índice del nodo a imprimir.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void read(int index){
      if(head != nullptr && (size > index && index >= 0)){
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
        }
        
        std::cout<<"El nodo en la posición "<<index<<" contiene: "<<current->getData()<<std::endl;
        std::cout<<std::endl;
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Operación actualizar. Actualiza el dato del nodo indicado.
    Param: int índice del nodo a modificar. T nuevo dato del nodo.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void update(int index, T newData){
      if(head != nullptr && (size > index && index >= 0)){
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
        }
        
        current->setData(newData);
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Operación eliminar. Elimina el nodo indicado.
    Param: int índice del nodo a eliminar.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(int index){
      if(head != nullptr && (size > index && index >= 0)){
        node<T>* previous = nullptr;
        current = head;
        
        if(index == 0){
          head = current->next;
          tail->next = head;
          free(current);
          size--;
        }
        
        else{
          for(int i = 1; i<=index; i++){
            previous = current;
            current = current->next;
            if(i == size-1){
              tail = previous;
            }
          }
          
          previous->next = current->next;
          free(current);
          size--;
        }
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }

    /* Imprime todos los datos de la lista.
    Param: Nada.
    Return: Nada.
    */
    void printNodes(){
      current = head;
      
      while(current != nullptr){
        std::cout<<current->getData()<<std::endl;
        current = current->next;
      }
    }

    /* Regresa el tamaño de la lista.
    Param: Nada.
    Return: int tamaño de la lista.
    */
    int getSize(){
      return size - 1;
    }

    /* Función especial de la lista circular para comprobar
    su funcionalidad. 
    Después de llegar al nodo del índice indicado, recorre la lista
    el número de nodos indicado por la variable spaces.
    Al recorrer la lista, el nodo del final conecta al nodo del inicio.
    Param: int índice del nodo a imprimir. int número de espacios a 
    recorrer en la lista.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)*/
    void spin(int index, int spaces){
      if(head != nullptr && (size > index && index >= 0)){
        int count = 0;
        current = head;
        
        for(int i = 1; i<=index; i++){
          current = current->next;
          count++;
        }
        
        for(int j = 0; j<spaces; j++){
          current = current->next;
          count++;
          
          if(count>=size){
            count = 0;
          }
        }
        
        std::cout<<"Después de moverse "<<spaces<<" espacios desde la posición "<<index<<", el nodo "<<count<<" contiene lo siguiente: "<<current->getData()<<std::endl;
        std::cout<<std::endl;
      }
      
      else if(head == nullptr){
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }

      else{
        std::cout<<"Error. Índice incorrecto.\n"<<std::endl;
      }
    }
};



int main() {
  std::string str;
  int size;
  linkedList<std::string> list, list2;
  doubleLinkedList<std::string> dList, dList2;
  circularList<std::string> cList, cList2;
  std::ifstream file("bitacora.txt");
  
  while(std::getline(file, str)){
    list.create(str);
    dList.create(str);
    cList.create(str);
  }
  
  std::cout<<"Lista ligada\n"<<std::endl;
  std::cout<<"Prueba del operador Update\n"<<std::endl;
  list.read(50);
  list.update(50, "Nuevo string");
  list.read(50);
  
  std::cout<<"Prueba 1 del operador Delete (en la cabeza de la lista)\n"<<std::endl;
  list.read(0);
  list.del(0);
  list.read(0);
  
  std::cout<<"Prueba 2 del operador Delete (en la cola de la lista)\n"<<std::endl;
  size = list.getSize();
  list.read(size);
  list.del(size);
  size = list.getSize();
  list.read(size);

  std::cout<<"Prueba 3 del operador Delete\n"<<std::endl;
  list.read(49);
  list.del(49);
  list.read(49);

  std::cout<<"Prueba de errores\n"<<std::endl;
  std::cout<<"Índice superior al tamaño del arreglo"<<std::endl;
  size = list.getSize();
  list.read(size);
  list.read(size + 1);
  std::cout<<"Índice negativo"<<std::endl;
  list.update(-1, "Hallo");
  std::cout<<"Leer lista vacia"<<std::endl;
  list2.del(0);
  
  std::cout<<"Lista doblemente ligada\n"<<std::endl;
  std::cout<<"Prueba del operador Update\n"<<std::endl;
  dList.read(0);
  dList.update(0, "Prueba 2");
  dList.read(0);
  
  std::cout<<"Prueba del operador especial ReadBackwards de lista doblemente ligada\n"<<std::endl;
  size = dList.getSize();
  dList.read(size);
  dList.readBackwards(0);
  
  std::cout<<"Prueba 2 del operador especial ReadBackwards de lista doblemente ligada\n"<<std::endl;
  dList.del(size);
  dList.readBackwards(0);
  dList.readBackwards(1);
  
  std::cout<<"Prueba 3 del operador especial ReadBackwards de lista doblemente ligada\n"<<std::endl;
  size = dList.getSize();
  dList.del(size-1);
  dList.readBackwards(0);
  dList.readBackwards(1);
  dList.readBackwards(2);

  std::cout<<"Prueba de errores\n"<<std::endl;
  std::cout<<"Índice superior al tamaño del arreglo"<<std::endl;
  size = dList.getSize();
  dList.read(size);
  dList.read(size + 1);
  std::cout<<"Índice negativo"<<std::endl;
  dList.update(-1, "Hallo");
  dList.readBackwards(-1);
  std::cout<<"Leer lista vacia"<<std::endl;
  dList2.del(0);
  
  std::cout<<"Lista circular\n";
  std::cout<<"Prueba del operador Update\n"<<std::endl;
  cList.read(60);
  cList.update(60, "Prueba 3");
  cList.read(60);
  
  std::cout<<"Prueba 1 del operador especial Spin de lista circular\n"<<std::endl;
  size = cList.getSize();
  cList.spin(size - 2, 5);
  
  std::cout<<"Prueba 2 del operador especial Spin de lista circular\n"<<std::endl;
  cList.del(size);
  size = cList.getSize();
  cList.spin(size, 1);
  
  std::cout<<"Prueba 3 del operador especial Spin de lista circular\n"<<std::endl;
  cList.del(0);
  size = cList.getSize();
  cList.spin(size, 1);

  std::cout<<"Prueba de errores\n"<<std::endl;
  std::cout<<"Índice superior al tamaño del arreglo"<<std::endl;
  size = cList.getSize();
  cList.read(size);
  cList.read(size + 1);
  std::cout<<"Índice negativo"<<std::endl;
  cList.update(-1, "Hallo");
  cList.spin(-1, 10);
  std::cout<<"Leer lista vacia"<<std::endl;
  cList2.del(0);
  
  return 0;
}