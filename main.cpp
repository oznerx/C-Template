#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

template <class T>
class Node
{
public:

    T data;
    Node<T>* next; 
    Node(T dataValue) {
        data = dataValue;  
        next = nullptr; 
    }

};


template <class T>
class LinkedList {
private:

    Node<T>* head;

public:
    int size = 0; 
    LinkedList() {
        head = nullptr; 
    }
    /*
    Añade un elemento T a la estructura de datos
    @Param T value: (T) elemento añadir del tipo T 
    */
    void create(T value) {
        size++;
        Node<T>* new_node = new Node<T>(value); 
        if (head == nullptr) { 
            head = new_node; 
        }
        else { 
            Node<T>* current = head; 
            while (current->next != nullptr) { 
                current = current->next;
            }
            current->next = new_node;  

        }


    }
    /*
    Busca un elemento T en la posicion indicada dentro de la estructura de datos  
    @Param T value: (int) indice en el cual se encuentra el dato T  
    */
    void read(int index)
    {
        if (index < 0) { 
            std::cout << "no existe un elemento con posicion negativa";
        }
        Node<T>* last = head; 
        Node<T>* previous = nullptr;
        if (head == nullptr) { 
            std::cout << "la lista no existe";
        }
        else {
            int i = 0;
            while (i < index && last->next != nullptr) { 
                previous = last; 
                last = last->next;
                i++;
            }
            if (i == index) {
                std::cout << last->data << "\n"; 
            }
        }
        //std::cout << "no existe un elemento con esas caracteristicas" << "\n";
    }
    /*
    Actualiza un elemento T dentro de la estructura de datos en una posicion determinada 
    @Param T value: (int) indice en el cual se desea modificar el dato T  
    */
    void update(int index, T newData){
        if (index < 0) { // solo se verifica que el indice no sea negativo
            std::cout << "No existe una posición negativa" ;
        }
        Node<T>* last = head; // se dice que nuestro ultimo nodo leido es igual al primero de la lista
        Node<T>* previous = nullptr;
        if (head == nullptr) { // si la lista no existe entonces solo regresa 
            std::cout << "Error";
        }
        else {
            int i = 0;
            while (i < index && last->next != nullptr) { // mientras que el elemento 'next' de 'last' osea el el valor actual no este vacio, entonces se hace lo siguiente:  
                previous = last; // basicamente aqui 'previous' y 'last' tienen los mismos valores (el ultimo elemento recorrido)
                last = last->next; // el valor de 'last' se convierte en el elemento actual
                i++;
            }
            if (i == index) { // si se encuentra el indice del  valor despues del while, se hace lo siguiente:
                last->data = newData; // como 'last' es el valor actual, se retorna la data del nodo
            }
        }
    }
    /*
    Elimina un elemento dentro de la estructura de datos en una posicion indicada 
    @Param T value: (int) indice en el cual se eliminara el dato T  
    */
    void del(int index) 
    {
        if (index < 0) {  
            return;
        }
        Node<T>* last = head; 
        Node<T>* previous = nullptr;
        if (head == nullptr) {  
            return;
        }
        else { 
            int i = 0;
            while (i < index && last->next != NULL) {   
                previous = last;
                last = last->next; 
                i++;
            }
            
            if (i == 0) {
                head = last->next; 
                free(last);  
                size--;
                return;
            }
            if (i == index) {
                previous->next = last->next; 
                size--;
                free(last); 
            }
        }
    }

    void printAll()
    {
        Node<T>* current = head;  
        while (current != NULL) {
            std::cout << current->data << "\n"; 
            current = current->next; 
        }
        std::cout << "\n";
    }

};
/*
Elimina un elemento dentro de la estructura de datos en una posicion indicada 
@Param T value: (string) archivo a leer, (LinkedList <std::string>) estructura de datos   
*/
void readFile(std::string filePath,LinkedList <std::string>* lista ){
    std::ifstream inputFile(filePath);
    std::string line;
    while (getline (inputFile , line)) {
    lista->create(line);
    }
}

int main()
{
    LinkedList <std::string>* lista = new LinkedList<std::string>();
    readFile("bitacora.txt", lista);
    //lista->printAll();
    //lista->read(0);

    std::string newData;
    int index; 
    std::cout << "Ingresa la posición del dato que deseas actualizar: ";
    std::cin >> index;
    std::cout << "Dato a actualizar: ";
    lista->read(index);
    std::cout << "Ingresa un nuevo dato:" << "\n";
    std::cin >> newData;
    std::cout << "Actualización exitosa" << "\n";
    lista->read(index);
}