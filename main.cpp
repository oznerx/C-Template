#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

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

    Node<T>* head;
    Node<T>* tail; 


public:

    int size = 0;

    Stack(){
        head = nullptr;
        tail = nullptr;
    }

    void create(T value){

        Node<T>* new_node = new Node<T>(value);

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

    void read(){
        std::cout << tail->data << "\n";
    }

    void update(T newData){
        tail->data = newData; 
    }

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

                tail = previous;
                previous->next = curr->next;
                delete(curr);
                size--;

            }

        }   
        
    }
        

    void print(){

        Node<T>* current = head;

        while (current != NULL) {
            std::cout << current->data << " ";
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
class PriorityQueue { // Agregar comentarios y de ser posible optimizar la busqueda en el update  
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

    void read(){

        if (head == nullptr) {
            std::cout << "La lista esta vacia\n";
        }

        else {
            std::cout <<  head->data << "\n";
        }

    }

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

    void del(){ 

        PNode<T>* temp = head;
        head = temp->next; 
        delete(temp);  
        size--;

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

    void test(){

        if (head == nullptr) {
            std::cout << "Error\n";
        }

        else {
            //std::cout <<  head->next->next->next->previous->data << "\n";
            std::cout <<  tail->previous->data << "\n";
        }

    }

};



int main()
{


Stack<std::string>* stack = new Stack <std::string>();

stack->create("valor 1 ");
stack->create("valor 2 ");
stack->create("valor 3 ");
stack->create("valor 4 ");
stack->create("valor 5 ");
stack->create("valor 6 ");
stack->create("valor 7 ");
stack->create("valor 9 ");
stack->print(); 
stack->del();
stack->print(); 
stack->update("new");
stack->print();


/*
Prioridades en la lista 
1: VIP
2: Express
3: Regular 
4: Mala

PriorityQueue<std::string>* listaPriorizada = new PriorityQueue<std::string>();

listaPriorizada->create("Juan", 1);
listaPriorizada->create("Eduardo", 2);
listaPriorizada->create("Cristian", 3);
listaPriorizada->create("Pedro", 4);
listaPriorizada->create("Miguel", 2);
listaPriorizada->create("Sam", 3);
listaPriorizada->printList();

listaPriorizada->del();
listaPriorizada->printList();
listaPriorizada->read();

listaPriorizada->update(5 , "NewPerson");
listaPriorizada->printList();
listaPriorizada->test();
*/
}