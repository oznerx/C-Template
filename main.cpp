#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string>

/*
Ozner Axel Leyva Mariscal
A01742377
4 de Octubre del 2022
Reto 1
*/

template <class T>
class Node
{
public:

    T data;
    Node<T>* next;
    Node<T>* previous;

    Node(T value) {
        data = value;
        next = nullptr;
        previous = nullptr;
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

    void create(T value){

        Node<T>* new_node = new Node<T>(value);

        if(head == nullptr){

            head = new_node;
            top = new_node;
            size++;

        }
      
        else{

            new_node->previous = top;
            top = new_node;
            size++;

        }

    }


    void read(){
        if (head != nullptr){
            std::cout << top->data << "\n";
        }

        else {
            std::cout<<"Lista vacia.\n"<<std::endl;
        }
    }

    
    void update(T newData){

        if (head != nullptr){
            top->data = newData; 
        }

        else {
            std::cout<<"Lista vacia.\n"<<std::endl;
        }

    }

    void del(){

        if(head != nullptr){

            if(head == top){

                head = nullptr;
                top = nullptr;
                size--;

            }

            else{

                Node<T>* temp = top;
                top = top->previous;
                delete (temp); 
                size--;

            }
            
        }   

        else {
            std::cout<<"Lista vacia.\n"<<std::endl;
        }
        
    }
        

    void print(){

        Node<T>* current = top;

        while (current != nullptr) {
            std::cout << current->data << "   ";
            current = current->previous;
        }

        std::cout << "\n";
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

delete (stack);

}