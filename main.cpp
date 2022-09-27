#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

/*
Ozner Axel Leyva Mariscal
A01742377
28 de septiembre del 2022
En este código se crerá una lista ligada con una estructura de datos lineal a partir de una archivo de texto
en el cual podremos usar métodos como  create, read, update y del.
*/

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
    Agrega un elemento T a la estructura de datos en la ultima posición
    @Param T value: (T) elemento añadir del tipo T 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
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
    Complejidad de tiempo: O(n) 
    Complejidad de espacio: O(1)
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
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
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
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(int index){

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

            else if (i == index) {
                previous->next = last->next; 
                size--;
                free(last); 
            }

        }

    }

};

/*
Elimina un elemento dentro de la estructura de datos en una posicion indicada 
@Param T value: (string) archivo a leer, (LinkedList <std::string>) estructura de datos   
Complejidad de tiempo: O(n)
Complejidad de espacio: O(1)
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
   
    //Agrega un nuevo nodo a la estructura de datos
    std::cout << "A continuación se agregará un nodo en la ultima posición" << "\n";
    lista->create("Nuevo Nodo");
    std::cout << "El nodo agregado tiene la siguiente informacion: " << "\n";
    lista->read(lista->size - 1);
    std::cout << "\n";
    
    //Buscando un elemento dentro de la estructura de datos 
    std::cout << "El nodo en la posición 4 tiene la siguiente información: ";
    lista->read(4);
    std::cout << "\n";

    //Actualizando un nodo dentro de la estructura 
    std::cout << "La posicón del nodo que se va a actualizar es: 2 \n";
    std::cout << "Informacion del nodo a actualizar: ";
    lista->read(2);
    std::cout << "El nodo tiene la siguiente información:" << "\n";
    lista->update(2, "Nodo Actualizado");
    lista->read(2);
    std::cout << "Actualización exitosa \n\n";

    //Eliminando un nodo dentro de la estructura
    std::cout << "La posicón del nodo que se va a eliminar es: 0 \n";
    std::cout << "El nodo en la posición 0 que se va a eliminar tiene la siguiente información: \n";
    lista->read(0);
    lista->del(0);
    std::cout << "El nodo fue exitosamente eliminado \n";
    
}