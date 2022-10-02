#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

/*
Ozner Axel Leyva Mariscal
A01742377
4 de Octubre del 2022
En este código e utilizarán las estructura de datos lineales de una Fila Priorizada y un Stack, 
en las cuales podremos usar métodos CRUD (create, read, update y del).
*/

template <class T>
class Node
{
public:

    T data;
    Node<T>* next;
    
    Node(T value) {
        data = value;
        next = nullptr;
    }  

};

template <class T>
class Stack{
private:

    Node<T>* head;
    Node<T>* top; 

public:

    int size = 0;

    Stack(){
        head = nullptr;
        top = nullptr;
    }

    /*
    Agrega un nodo con un elemento T a la estructura de datos en la ultima posición
    @Param: (T value) elemento añadir
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void create(T value){

        Node<T>* new_node = new Node<T>(value);

        if(head == nullptr){

            head = new_node;
            top = new_node;
            size++;

        }
      
        else{

            top->next = new_node;
            top = new_node;
            size++;

        }

    }

    /*
    Se imprime el valor del nodo que se encuentra en el tope de la estructura de datos
    @Param: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void read(){
        std::cout << top->data << "\n";
    }

    /*
    Modifica el valor del nodo que se encuentra en el tope de la estructura de datos
    @Param: (T newData) nuevo valor por el cual se va a actualizar 
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void update(T newData){
        top->data = newData; 
    }

    /* 
    Elimina el nodo que se encuentre en el tope de la estructura de datos
    @Param: nada 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(){

        if(head != nullptr){

            Node<T>* previous = nullptr;
            Node<T>* curr = head;
            
            if(size-1 == 0){

                head = curr->next;
                delete(curr);
                size--;

            }
            
            else{

                for(int i = 0 ; i<size-1 ; i++){

                    previous = curr;
                    curr = curr->next;

                }

                top = previous;
                previous->next = curr->next;
                delete(curr);
                size--;

            }

        }   
        
    }
        
    /*    
    Imprime todos los valores de los nodos que se encuentren en la estructura de datos
    @Param: nada 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void print(){

        Node<T>* current = head;

        while (current != NULL) {
            std::cout << current->data << "   ";
            current = current->next;
        }

        std::cout << "\n";
    } 

};

template <class T>
class PNode
{
public:

    T data;
    int priority=0;
    PNode<T>* next;
    PNode<T>* previous;

    PNode(T dataValue,int p) {
        data = dataValue;
        priority = p;
        next = nullptr;
        previous = nullptr;
    }  

};


template <class T>
class PriorityQueue{  
private:

    PNode<T>* head;
    PNode<T>* tail;

public:

    int size = 0;

    PriorityQueue(){
        head = nullptr;
        tail = nullptr;
    }

    /*
    Elimina todos los valores de los nodo que se encuentran en la estructura de datos
    @Param: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    ~PriorityQueue(){

        while (head != NULL) {
            PNode<T>* temp = head;
            head = head->next;
            delete temp;
        }

        tail = NULL;
    }

    /*
    Agrega un nodo con un elemento T a la estructura de datos en cierta posición dependiendo la prioridad que tenga el nodo
    @Param: (T data) elemento añadir del tipo T , (int p) prioridad del nodo a agregar  
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void create(T data, int p){

        PNode<T> *new_node = new PNode<T>(data, p);

        if(head == nullptr){

            new_node->next = head;
            head = new_node;
            tail = head;
            size++;
            
        }

        else {

            PNode<T>* current = head;

            while (current->next != nullptr && current->next->priority <= new_node->priority) {
                current = current->next;
            }

            if (current->next == nullptr){
                current->next = new_node; 
                new_node->previous = current;
                tail = new_node;
                size++;
            }

            else {
                new_node->next = current->next;
                current->next->previous = new_node;
                current->next = new_node;
                new_node->previous = current;
                size++;
            }
             
        }

    }

    /*
    Se imprime el valor del nodo que se encuentre en la primera posición de la estructura de datos
    @Param: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void read(){

        if (head == nullptr) {
            std::cout << "La lista esta vacia\n";
        }

        else {
            std::cout <<  head->data << "\n";
        }

    }

    /*
    Modifica el valor del nodo que se encuentra en la estructura de datos en la posición que se desee
    @Param: (T newData) nuevo valor por el cual se va a actualizar , (int index) posición en la cual se va a actualizar el valor del nodo 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void update(int index , T newData){

        if (index < 0) { 
            std::cout << "No existe una posición negativa" ;
        }


        if (head == nullptr) { 
            std::cout << "Error";
        }

        else {

            PNode<T>* last = head; 
            PNode<T>* previous = nullptr;

            if (index <= size/2){

                int i = 0;

                while (i < index && last->next != nullptr) {   
                    previous = last; 
                    last = last->next;
                    i++;
                }

                if (i == index) { 
                    last->data = newData; 
                }

            }

            else {

                PNode<T>* last = tail; 

                int i = size-1;

                while (i > index && last->previous != nullptr){   
                    previous = last; 
                    last = last->previous;
                    i--;
                }

                if (i == index){ 
                    last->data = newData; 
                }

            }


        }

    }

    /*
    Elimina el nodo que se encuentra en la primera posición de la estructura de datos
    @Param: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void del(){ 

        PNode<T>* temp = head;
        head = temp->next; 
        delete(temp);  
        size--;

    }

    /*    
    Imprime todos los valores de los nodo que se encuentran en la estructura de datos
    @Param: nada 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void print()
    {
        PNode<T>* current = head;

        while (current != NULL) {
            std::cout << current->data << "   ";
            current = current->next;
        }

        std::cout << "\n";

    }

    /*    
    Imprime el penúltimo valor de la estructura apuntando desde el último para comprobar que es una lista doblemente ligada 
    @Param: nada 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void test(){

        if (head == nullptr) {
            std::cout << "Error\n";
        }

        else {
            std::cout <<  tail->previous->data << "\n";
        }

    }

};



int main()
{

Stack<std::string>* stack = new Stack <std::string>();

std::cout << "------------------------------------------------------- Stack -------------------------------------------------------" << "\n\n";

std::cout << "A continuación se agregarán y mostrarán todos los valores en el stack: \n";
stack->create("valor 1 ");
stack->create("valor 2 ");
stack->create("valor 3 ");
stack->create("valor 4 ");
stack->create("valor 5 ");
stack->create("valor 6 ");
stack->create("valor 7 ");
stack->create("valor 8 ");
stack->print(); 
std::cout << "\n";

std::cout << "El valor del nodo que se encuentre en el tope del stack es: \n";
stack->read();
std::cout << "\n";

std::cout << "A continuación se modificará el nodo que se encuentra en el tope del stack\n";
stack->update("New");
std::cout << "El stack ahora tiene los siguientes elementos: \n";
stack->print(); 
std::cout << "\n";

std::cout << "A continuación se borrará el nodo que se encuentre en el tope del stack\n";
stack->del();
std::cout << "El stack ahora tiene el siguiente orden: \n";
stack->print(); 
std::cout << "\n";

std::cout << "------------------------------------------------------- Lista Priorizada -------------------------------------------------------" << "\n\n";

// Prioridades en la lista:  1: VIP       2: Express     3: Regular      4: Mala 

PriorityQueue<std::string>* listaPriorizada = new PriorityQueue<std::string>();

std::cout << "A continuación se agregarán y mostrarán todos los valores en la lista: \n";
listaPriorizada->create("Juan", 1);
listaPriorizada->create("Cristian", 3);
listaPriorizada->create("Pedro", 4);
listaPriorizada->create("Miguel", 2);
listaPriorizada->create("Sam", 3);
listaPriorizada->create("Brizeth", 1);
listaPriorizada->create("Kraken", 4);
listaPriorizada->create("Eduardo", 2);
listaPriorizada->print();
std::cout << "\n";

std::cout << "El valor del nodo que se encuentre en la posición 0 es: \n";
listaPriorizada->read();
std::cout << "\n";

std::cout << "A continuación se modificará el nodo que se encuentra en la posición 5 de la lista: \n";
listaPriorizada->update(5 , "NewPerson");
listaPriorizada->print();
std::cout << "\n";

std::cout << "A continuación se borrará el nodo que se encuentre en la primera posición de la lista\n";
listaPriorizada->del();
std::cout << "La lista ahora tiene los siguientes elementos: \n";
listaPriorizada->print();
std::cout << "\n";

std::cout << "A continuación se Imprimirá el penúltimo valor de la estructura apuntando desde el último nodo";
std::cout << "para comprobar que es una lista doblemente ligada\n";
listaPriorizada->test();
std::cout << "\n";

}