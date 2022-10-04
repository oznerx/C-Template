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


    char read(){

        if (head != nullptr){
            return top->data ;
        }

        else {
            std::cout<<"Lista vacia.\n"<<std::endl;
        }

        return 0;
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

//"                           (aaaadddes)/*((99999999*/sssss()()[{}]                                     "

void validate(std::string lineToValidate){

    Stack<char>* stack = new Stack <char>();
    bool isValid = true;

    for (int i = 0 ; i < lineToValidate.length() ; i++ ){

        if (lineToValidate[i] == '(' || lineToValidate[i] == '{' || lineToValidate[i] == '[' || 
            lineToValidate[i] == '/' && lineToValidate[i+1] == '*'){
            
            if (lineToValidate[i] == '/' && lineToValidate[i+1] == '*'){
                stack->create('+');
            }

            else{
                stack->create(lineToValidate[i]);
            }

            continue;

        }

        else{

            if (lineToValidate[i] == ')' || lineToValidate[i] == '}' || lineToValidate[i] == ']' ||
                lineToValidate[i] == '*' && lineToValidate[i+1] == '/'){

                if (stack->size == 0){
                    isValid = false;
                    break;
                }

                char value = stack->read();

                if(!((value == '(' && lineToValidate[i] == ')') || 
                    (value == '{' && lineToValidate[i] == '}') ||
                    (value == '[' && lineToValidate[i] == ']') || 
                    (value == '*' && lineToValidate[i] == '/'))){
                    isValid = false; 
                    break;
                }

                stack->del();

            }

        }

    }

    if (isValid){
        std::cout << "Es valido" ; 
    }

    else{
        std::cout << "NO es valido" ; 
    }
    

}


int main()
{

std::string lineToValidate = "(aaaadddes)/*((99999999*/sssss()()[{}]";
std::cout << lineToValidate << "\n";

validate(lineToValidate);

}