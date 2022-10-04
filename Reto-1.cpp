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

            new_node->previous = top;
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
    char read(){

        if (head != nullptr){
            return top->data ;
        }

        else {
            std::cout<<"Lista vacia.\n"<<std::endl;
        }

        return 0;
    }

    /*
    Modifica el valor del nodo que se encuentra en el tope de la estructura de datos
    @Param: (T newData) nuevo valor por el cual se va a actualizar 
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void update(T newData){

        if (head != nullptr){
            top->data = newData; 
        }

        else {
            std::cout<<"Lista vacia.\n"<<std::endl;
        }

    }

    /* 
    Elimina el nodo que se encuentre en el tope de la estructura de datos
    @Param: nada 
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
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
        
    /*    
    Imprime todos los valores de los nodos que se encuentren en la estructura de datos
    @Param: nada 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void print(){

        Node<T>* current = top;

        while (current != nullptr) {
            std::cout << current->data << "   ";
            current = current->previous;
        }

        std::cout << "\n";
    } 

};

/*    
Valida una cadena de texto para saber si los corechetes, comentarios y parentesis cierran correctamente
@Param: (string lineToValidate) La linea a validar
Complejidad de tiempo: O(n)
Complejidad de espacio: O(1)
*/
void validate(std::string lineToValidate){

    Stack<char>* stack = new Stack <char>();
    bool isValid = true;


    for (int i = 0 ; i < lineToValidate.length() ; i++ ){

        if (lineToValidate[i] == '(' || lineToValidate[i] == '{' || lineToValidate[i] == '[' || 
            (lineToValidate[i] == '/' && lineToValidate[i+1] == '*')){
            
            if (lineToValidate[i] == '/' && lineToValidate[i+1] == '*'){
                stack->create('+');
            }

            else{
                stack->create(lineToValidate[i]);
            }

            continue;

        }

        else{

            if ((lineToValidate[i] == ')' || lineToValidate[i] == '}' || lineToValidate[i] == ']' || lineToValidate[i] == '*' || lineToValidate[i] == '/')){

                if (stack->size == 0){
                    isValid = false;
                    break;
                }

                char value = stack->read();

                if(!((value == '(' && lineToValidate[i] == ')') || 
                    (value == '{' && lineToValidate[i] == '}') ||
                    (value == '[' && lineToValidate[i] == ']') || 
                    (value == '+' && lineToValidate[i] == '*'))){
                    isValid = true; 
                    break;
                }
                stack->read();
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

std::cout << "------------------------------------------------------- Casos de prueba -------------------------------------------------------\n\n";

std::string lineToValidate = "(aaaadddes)/*((99999999*/sssss()()[{}]";
std::cout << "El string:   "<<lineToValidate << "    ";
validate(lineToValidate);
std::cout << "\n\n";

std::string lineToValidate2 = "*/(aaaadddes)/*sssss()()[{}]";
std::cout << "El string:   "<<lineToValidate2 << "    ";
validate(lineToValidate2);
std::cout << "\n\n";

std::string lineToValidate3 = "(aaaadddes)/**/sssss()()[{}]]";
std::cout << "El string:   "<<lineToValidate3 << "    ";
validate(lineToValidate3);
std::cout << "\n\n";

}