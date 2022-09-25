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
        std::cout << "no existe un elemento con esas caracteristicas" << "\n";
    }
    /*
    Actualiza un elemento T dentro de la estructura de datos en una posicion determinada 
    @Param T value: (int) indice en el cual se desea modificar el dato T  
    */
    void update(){

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
     lista->read(16807);
}