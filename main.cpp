/*
Este programa utiliza dos estructuras de datos: Stacks y listas 
priorizadas, para realizar pruebas con las operaciones básicas CRUD 
(create, read, update y delete), cumpliendo con las condiciones 
especiales de cada estructura.
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 01 de octubre de 2022
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>

std::unordered_map<std::string, int> PRIORITY_INDEX = {
  {"Económica", -1}, {"Express", 0}, {"Regular", 1}, {"VIP", 2}, {"Mega VIP", 3},
};

std::vector<std::string> PRIORITY{"Económica", "Express", "Regular", "VIP", "Mega VIP"};

/*
Entidad básica de las estructuras de datos. Es especial para las 
listas doblemente ligadas, debido a que están conectadas a un nodo 
de atrás y otro de adelante. Puede contener cualquier tipo de 
datos en ella.
Puede contener un string de prioridad dentro de ella. 
*/
template <class T>
class DoubleNode{
  T data;
  std::string priority;
  public:
    DoubleNode<T>* next;
    DoubleNode<T>* prev;

    /* Constructor de un nodo. El nodo siguiente y anterior son
    nodos nulos.
    Param: Nada.
    Return: Nada.
    */
    DoubleNode(){
      next = nullptr;
      prev = nullptr;
    }

    /* Destructor de un nodo.
    Param: Nada.
    Return: Nada.
    */
    ~DoubleNode(){
      next = nullptr;
      prev = nullptr;
    }

    /* Establece el dato del nodo.
    Param: (T newData) nuevo dato del nodo.
    Return: Nada.
    */
    void setData(T newData){
      data = newData;
    }

    /* Establece la prioridad del nodo.
    Param: (string newPriority) nueva prioridad del nodo.
    Return: Nada.
    */
    void setPriority(std::string newPriority){
      priority = newPriority;
    }

    /* Regresa el dato del nodo.
    Param: Nada.
    Return: T dato del nodo.
    */
    T getData(){
      return data;
    }

    /* Regresa la prioridad del nodo.
    Param: Nada
    Return: String prioridad del nodo.
    */
    std::string getPriority(){
      return priority;
    }
};

/*
Esta clase es la base del Stack. 
Contiene las operaciones CRUD delimitadas por las condiciones
especiales de un Stack.
*/
template <class T>
class Stack{
  DoubleNode<T>* head;
  DoubleNode<T>* top;  
  DoubleNode<T>* current;
  int size = 0;
  public:

    /* Constructor del Stack. 
    El nodo cabeza y tope son nulos.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    Stack(){
      head = nullptr;
      top = nullptr;
    }

    /* Destructor del Stack. 
    Se eliminan todos los nodos.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    ~Stack(){
      current = head;
      while(current != nullptr){
        DoubleNode<T>* tmp = current;
        current = current->next;
        delete tmp;
      }
      head = nullptr;
      top = nullptr;
    }

    /* Operación crear. Inserta un nodo en el Stock.
    Param: (T data) dato del nuevo nodo.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void create(T data){
      DoubleNode<T>* newNode = new DoubleNode<T>();
      newNode->setData(data);
      
      if(head == nullptr){
        head = newNode;
        top = newNode;
      }
      
      else{
        newNode->prev = top;
        top->next = newNode;
        top = newNode;
      }
      
      size++;
    }

    /* Operación leer. Imprime el dato del nodo tope.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void read(){
      if(head != nullptr){
        std::cout<<"El nodo tope contiene: "<<top->getData()<<std::endl;
        std::cout<<std::endl;
      }
      
      else{
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }
    }

    /* Operación actualizar. Actualiza el dato del nodo tope.
    Param: (T newData) nuevo dato del nodo tope.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void update(T newData){
      if(head != nullptr){
        top->setData(newData);
      }
      
      else{
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }
    }

    /* Operación eliminar. Elimina el nodo tope.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void del(){
      if(head != nullptr){
        
        if(head == top){
          head = nullptr;
          top = nullptr;
        }
        
        else{
          top = top->prev;
          delete top->next;
        }
        
        size--;
      }
                
      else{
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }
    }

    /* Imprime todos los datos de la lista.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void printNodes(){
      current = head;
      
      while(current != nullptr){
        std::cout<<current->getData()<<std::endl;
        current = current->next;
      }
    }
};

/*
Esta clase es la base de la lista priorizada. 
Contiene las operaciones CRUD delimitadas por las condiciones
especiales de una lista priorizada.
*/
template <class T>
class PrioritizedList{
  DoubleNode<T>* head;
  DoubleNode<T>* tail;  
  DoubleNode<T>* current;
  int size = 0;
  public:

    /* Constructor de la lista priorizada. 
    El nodo cabeza y cola son nulos.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    PrioritizedList(){
      head = nullptr;
      tail = nullptr;
    }

    /* Destructor de la lista priorizada. 
    Se eliminan todos los nodos.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    ~PrioritizedList(){
      current = head;
      while(current != nullptr){
        DoubleNode<T>* tmp = current;
        current = current->next;
        delete tmp;
      }
      head = nullptr;
      tail = nullptr;
    }

    /* Operación crear. Inserta un nodo en la estructura de datos.
    Param: (T data) dato del nuevo nodo. (string priority) prioridad del nuevo nodo.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void create(T data, std::string priority){
      if(std::find(std::begin(PRIORITY), std::end(PRIORITY), priority) != std::end(PRIORITY)){
        DoubleNode<T>* newNode = new DoubleNode<T>();
        newNode->setData(data);
        newNode->setPriority(priority);
        size++;
        
        if(head == nullptr){
          head = newNode;
          tail = newNode;
        }
        
        else{
          current = tail;
          
          while(PRIORITY_INDEX[newNode->getPriority()] > PRIORITY_INDEX[current->getPriority()]){
            
            if(current->prev == nullptr){
              newNode->next = head;
              head->prev = newNode;
              head = newNode;
              return;
            }
            
            current = current->prev;
          }
          
          if(current == tail){
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            return;
          }
          
          newNode->next = current->next;
          current->next->prev = newNode;
          current->next = newNode;
          newNode->prev = current;
        }
      }
        
      else{
        std::cout<<"La prioridad del nodo es invalida\n"<<std::endl;
      }
    }

    /* Operación leer. Imprime el dato del nodo indicado.
    Param: (int index) índice del nodo a imprimir.
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
        
        std::cout<<"El nodo en la posición "<<index<<" con prioridad "<<current->getPriority()<<" contiene: "<<current->getData()<<std::endl;
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
    Param: (int index) índice del nodo a modificar. (T newData) nuevo dato del nodo.
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

    /* Operación eliminar. Elimina el nodo cabeza.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void del(){
      if(head != nullptr){
        if(head == tail){
          head = nullptr;
          tail = nullptr;
        }
          
        else{
          head = head->next;
          delete head->prev;
        }
        
        size--;
      }
            
      else{
        std::cout<<"Error. La lista está vacia.\n"<<std::endl;
      }
    }

    /* Imprime todos los datos de la lista.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void printNodes(){
      current = head;
      
      while(current != nullptr){
        std::cout<<current->getData()<<" y su prioridad: "<<current->getPriority()<<std::endl;
        current = current->next;
      }
    }
};



int main(){
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::string names[10] = {"John", "Mary", "Oscar", "Elvira", "Juan Pablo", "Ned", "Peter", "Ben", "Kevin", "Gwen"};
  std::string priorities[10] = {"VIP", "Express", "Regular", "Regular", "Express", "VIP", "VIP", "Express", "Regular", "Express"};
  Stack<int>* stack = new Stack<int>();
  PrioritizedList<std::string>* list = new PrioritizedList<std::string>();
  
  std::cout<<"---------Stack---------\n"<<std::endl;
  std::cout<<"Prueba del operador Create\n"<<std::endl;
  
  for(int i = 0; i<10; i++){
    stack->create(arr[i]);
  }

  std::cout<<"Prueba del operador Read\n"<<std::endl;
  stack->read();
  
  std::cout<<"Prueba del operador Update\n"<<std::endl;
  stack->update(11);
  stack->read();

  std::cout<<"Prueba del operador Delete\n"<<std::endl;
  for(int i = 0; i<10; i++){
    stack->read();
    stack->del();
  }

  std::cout<<"Prueba de errores de diversos operadores\n"<<std::endl;
  stack->read();
  stack->update(10);
  stack->del();

  std::cout<<"Prueba de crear contenido en el Stack después de eliminar todo su contenido\n"<<std::endl;
  stack->create(12);
  stack->read();
  stack->create(13);
  stack->read();

  std::cout<<"---------Listas priorizadas---------\n"<<std::endl;
  std::cout<<"Prueba 1 del operador Create\n"<<std::endl;
  for(int i = 0; i<10; i++){
    list->create(names[i], priorities[i]);
  }
  list->printNodes();
  
  std::cout<<"\nPrueba 2 del operador Create (prioridad superior a los demás)\n"<<std::endl;
  list->create("Johnny", "Mega VIP");
  list->printNodes();

  std::cout<<"\nPrueba 3 del operador Create (prioridad inferior a los demás)\n"<<std::endl;
  list->create("Jacobo", "Económica");
  list->printNodes();

  std::cout<<"\nPrueba del operador Read\n"<<std::endl;
  list->read(5);

  std::cout<<"Prueba del operador Update\n"<<std::endl;
  list->update(5, "Anya");
  list->read(5);
  
  std::cout<<"Prueba de errores de diversos operadores\n"<<std::endl;
  list->update(20, "Prueba");
  list->read(20);

  std::cout<<"Prueba del operador Delete\n"<<std::endl;
  for(int i = 0; i<12; i++){
    list->read(0);
    list->del();
  }

  std::cout<<"Prueba de errores de diversos operadores\n"<<std::endl;
  list->read(5);
  list->del();
  list->update(0, "Prueba");
  list->create("Hi", "Super Duper VIP");

  std::cout<<"Prueba de crear contenido en la lista priorizada después de eliminar todo su contenido\n"<<std::endl;
  for(int i = 0; i<4; i++){
    list->create(names[i], priorities[i]);
  }
  list->printNodes();
  
  delete stack;
  delete list;
  
  return 0;
}

/*
Referencias:
https://stackoverflow.com/questions/14515274/how-to-check-if-a-string-is-in-a-list-of-strings
*/