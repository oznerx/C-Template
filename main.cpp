#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

#define MAX = 10;

/*
Ozner Axel Leyva Mariscal
Se utilizará una estructura de datos lineal de una Fila Priorizada y un Stack.


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

    T datos[7];
    int tope;

public:

    Stack(){
        tope = -1;
    }

    void create(T value){
        Node<T>* new_node = new Node<T>(value); 
        tope++;
        datos[tope] = new_node->data;
    }

    void read(){
        std::cout << datos[tope];
    }

    void del(){
        datos[tope] = nullptr;
    }

    bool isEmpty(){
        return (tope == -1);
        std::cout << "El stack esta vacio\n";
    }

    bool isFull(){
        return (tope == 7-1);
        std::cout << "El stack esta lleno\n";
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
class PriorityQueue {
private:

    PNode<T>* head;
    PNode<T>* tail;

public:
    int size = 0;

    PriorityQueue() {
        head = nullptr;
        tail = nullptr;
    }

    ~PriorityQueue() {
        while (head != NULL) {
            PNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;
    }
 
    void create(T data, int p){

        PNode<T> *new_node = new PNode<T>(data, p);

        if(head == nullptr){
            new_node->next = head;
            head = new_node;
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

    void read(){
        /* No se si cuente como read el peek */
    }

    void update(){
        /* Por prioridad?, el primero?, el ultimo? */
    }

    void del(int index){ 
        PNode<T>* previous = nullptr;
        PNode<T>* current = head;

        if(index == 0){
          head = current->next;
          tail->next = head;
          delete(current);
          size--;
        }
        
        else{

          for(int i = 0; i < index ; i++){
            previous = current;
            current = current->next;

            if(i == size-1){
              tail = previous;
            }

          }
          
          previous->next = current->next;
          delete(current);
          size--;

        }

    }

    T peek()
    {
        if (head == nullptr) {
            return NULL;
        }
        else {
            return head->data;
        }
    }

    void printList()
    {
        PNode<T>* current = head;
        while (current != NULL) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

};



int main()
{
/*
Prioridades en la lista 
1: VIP
2: Express
3: Regular 
4: Mala
*/

PriorityQueue<std::string>* listaPriorizada = new PriorityQueue<std::string>();
Stack<std::string>* stack = new Stack <std::string>();

stack->create("valor 1 ");
stack->create("valor 1 ");
stack->create("valor 1 ");
stack->create("valor 1 ");
stack->create("valor 1 ");
stack->create("valor 1 ");
stack->create("valor 1 ");
stack->create("valor 1 ");
stack->read();
//stack->isFull();

/*
listaPriorizada->create("Persona 1", 1);
listaPriorizada->create("Persona 2", 2);
listaPriorizada->create("Persona 3", 3);
listaPriorizada->create("Persona 4", 4);
listaPriorizada->create("Persona 2.1", 2);
listaPriorizada->create("Persona 3.1", 3);
listaPriorizada->printList();
listaPriorizada->del(1);
listaPriorizada->printList();
*/


}