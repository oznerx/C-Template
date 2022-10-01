#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

int MAX = 7;

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

    T *nodesData = new T[MAX];
    int tope;

public:

    Stack(){
        tope = -1;
    }

    void create(T value){

        if (!isFull()){
            Node<T>* new_node = new Node<T>(value); 
            tope++;
            nodesData[tope] = new_node->data;
        }

        else {
            std::cout << "No es posible igresar el dato, el arreglo ya esta lleno\n";
        }

    }

    void read(){
        std::cout << nodesData[tope] << "\n";
    }

    void update(T newData){
        nodesData[tope] = newData; 
    }

    void del(){

        if(tope==MAX-1) {
            MAX-=1;
        }

        else {

            MAX-=1;
            for (int i = tope; i < MAX; i++) {
                nodesData[i]=nodesData[i+1];
            }

        }

    }

    bool isEmpty(){
        return (tope == -1);
    }

    bool isFull(){
        return (tope == MAX-1);
    }

    void print(){
        for (int i = 0 ; i < MAX ; i++ ){
            std::cout << nodesData[i] << "\n";
        }
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
                PNode<T>* prev = nullptr;

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
stack->print(); 
stack->create("valor 9 ");
stack->del();
stack->print(); 


/*
Prioridades en la lista 
1: VIP
2: Express
3: Regular 
4: Mala
*/
PriorityQueue<std::string>* listaPriorizada = new PriorityQueue<std::string>();

listaPriorizada->create("Juan", 1);
listaPriorizada->create("Eduardo", 2);
listaPriorizada->create("Cristian", 3);
listaPriorizada->create("Pedro", 4);
listaPriorizada->create("Miguel", 2);
listaPriorizada->create("Sam", 3);
listaPriorizada->printList();
/*
listaPriorizada->del();
listaPriorizada->printList();
listaPriorizada->read();
*/
listaPriorizada->update(5 , "NewPerson");
listaPriorizada->printList();
listaPriorizada->test();

}