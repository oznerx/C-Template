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
    Complejidad de tiempo: O()
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
    Complejidad de tiempo: O() 
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
    }
    /*
    Actualiza un elemento T dentro de la estructura de datos en una posicion determinada 
    @Param T value: (int) indice en el cual se desea modificar el dato T  
    Complejidad de tiempo: O()
    */
    void update(int index, T newData){
        if (index < 0) { 
            std::cout << "No existe una posición negativa" ;
        }
        Node<T>* last = head; 
        Node<T>* previous = nullptr;
        if (head == nullptr) { 
            std::cout << "Error";
        }
        else {
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
    }
    /*
    Elimina un elemento dentro de la estructura de datos en una posicion indicada 
    @Param T value: (int) indice en el cual se eliminara el dato T  
    Complejidad de tiempo: O()
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
Complejidad de tiempo: O()
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
    //Leyendo el archivo y creando la lista ligada con cada linea 
    LinkedList <std::string>* lista = new LinkedList<std::string>();
    readFile("bitacora.txt", lista);

    std::string newData;
    std::string newNode;
    int indexToRead, indexToUpdate; 

    //Agrega un nuevo dato a la estructura 
    std::cout << "Ingresa la informacion del nuevo nodo a agregar a la estructura: " << "\n";
    std::cin >> newNode;
    lista->create(newNode);
    std::cout << "El nodo agregado tiene la siguiente informacion: " << "\n";
    lista->read(lista->size - 1);
    std::cout << "\n";
    
    //Buscando un elemento dentro de la estructura de datos 
    std::cout << "Ingresa la posición del nodo que deseas leer: ";
    std::cin >> indexToRead;
    lista->read(indexToRead);
    std::cout << "\n";

    //Modificando un dato dentro de la estructura 
    std::cout << "Ingresa la posición del nodo que deseas actualizar: ";
    std::cin >> indexToUpdate ;
    std::cout << "Informacion del nodo a actualizar: ";
    lista->read(indexToUpdate);
    std::cout << "Ingresa el nuevo dato:" << "\n";
    std::cin >> newData;
    lista->update(indexToUpdate, newData);
    std::cout << "Actualización exitosa, la informacion del nodo es la siguiente: " << "\n";
    lista->read(indexToUpdate);
    std::cout << "\n";

    lista->printAll();
}