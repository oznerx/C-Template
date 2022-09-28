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
class DNode
{
public:

    T data;
    DNode<T>* next; 
    DNode<T>* prev; 

    DNode(T dataValue) {
        data = dataValue;  
        next = nullptr; 
        prev = nullptr; 
    }

};


template <class T>
class linkedList {
private:

    Node<T>* head;

public:
    int size = 0; 
    linkedList() {
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
    Busca e imprime un elemento T en la posicion indicada dentro de la estructura de datos  
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

template <class T>
class doubleLinkedList { 
private:

    DNode<T>* head;

public:

    int size = 0; 

    doubleLinkedList() {
        head = nullptr;
    }

    /*
    Agrega un elemento T a la estructura de datos en la ultima posición
    @Param T value: (T) elemento añadir del tipo T 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void createAtEnd(T value) {

        size++;
        DNode<T>* new_node = new DNode<T>(value); 

        if (head == nullptr) { 
            head = new_node; 
        }

        else { 

            DNode<T>* current = head; 
            while (current->next != nullptr) { 
                current = current->next;
            }
            current->next = new_node; 
            new_node->prev = current; 

        }

    }

    /*
    Agrega un elemento T a la estructura de datos en la primera posición
    @Param T value: (T) elemento añadir del tipo T 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void createAtFront(T value) {

        size++;
        DNode<T>* new_node = new DNode<T>(value); 

        if (head == nullptr) { 
            head = new_node; 
        }

        else { 

            new_node->next = head;
            head->prev = new_node;
            head = new_node; 

        }

    }

    /*
    Busca e imprime un elemento T en la posicion indicada dentro de la estructura de datos  
    @Param T value: (int) indice en el cual se encuentra el dato T 
    Complejidad de tiempo: O(n) 
    Complejidad de espacio: O(1)
    */
    void read(int index)
    {
        if (index < 0) { 
            std::cout << "no existe un elemento con posicion negativa";
        }

        DNode<T>* last = head; 
        DNode<T>* previous = nullptr;

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

        DNode<T>* last = head; 
        DNode<T>* previous = nullptr;

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

        DNode<T>* last = head; 
        DNode<T>* previous = nullptr;
        
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
                previous->prev = last->prev;
                size--;
                free(last); 
            }

        }

    }

    /*
    Imprime el penúltimo valor de la estructura para comprobar que es una lista doblemente ligada 
    @Param T value: nada 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void test(){

        DNode<T>* last = head; 
        DNode<T>* previous = nullptr;

        int i = 0;
        while (i < size - 1  && last->next != nullptr) { 
            previous = last; 
            last = last->next;
            last->prev = previous;
            i++;
        }

        if (i == size-1) {
            std::cout << last->prev->data << "\n"; 
        }

    }

};

template <class T>
class circularLinkedList { //No comentado todavia 
private:

Node<T>* head;

public:

    int size = 0; 

    circularLinkedList() {
        head = nullptr;
    }

    /*
    Agrega un elemento T a la estructura de datos en la ultima posición
    @Param T value: (T) elemento añadir del tipo T 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void create(T value) {

        Node<T>* new_node = new Node<T>(value); 

        if (head == nullptr) { 
            head = new_node; 
            size++;
        }

        else{
            
            Node<T>* current = head; 
            for(int i = 0 ; i < size - 1 ;i++){
                current = current->next;
            }
            current->next = new_node;  
            new_node->next = head;
            size++;
            
        }

    }

    /*
    Busca e imprime un elemento T en la posicion indicada dentro de la estructura de datos  
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

/*
    //Para testear
    void printList()
    {
        Node<T>* last = head; 
        Node<T>* previous = nullptr; 
        int i = 0;

        while (i < size - 1 ) { 
            previous = last; 
            last = last->next;
            std::cout << last->data << "\n";
            i++;
        }

    }
*/

    /*
    Imprime el primer valor de la estructura referenciado desde el último nodo para comprobar que es una lista circular 
    @Param T value: nada  
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void test(){

        Node<T>* last = head; 
        Node<T>* previous = nullptr;

        int i = 0;
        while (i < size - 1  && last->next != nullptr) { 
            previous = last; 
            last = last->next;
            i++;
        }

        if (i == size-1) {
            std::cout << last->next->data << "\n"; 
        }

    }

};

/*
Lee el archivo indicado y por cada linea se es creado un nuevo nodo en la lista ligada 
@Param T value: (string) archivo a leer, (LinkedList <std::string>) estructura de datos   
Complejidad de tiempo: O(n)
Complejidad de espacio: O(1)
*/
void readFile(std::string filePath,linkedList <std::string>* lista ){

    std::ifstream inputFile(filePath);
    std::string line;

    while (getline (inputFile , line)) {
        lista->create(line);
    }

}

/*
Lee el archivo indicado y por cada linea se es creado un nuevo nodo en la lista doblemente ligada   
@Param T value: (string) archivo a leer, (LinkedList <std::string>) estructura de datos   
Complejidad de tiempo: O(n)
Complejidad de espacio: O(1)
*/
void readFile2(std::string filePath,doubleLinkedList <std::string>* lista ){

    std::ifstream inputFile(filePath);
    std::string line;

    while (getline (inputFile , line)) {
        lista->createAtEnd(line);
    }

}

/*
Lee el archivo indicado y por cada linea se es creado un nuevo nodo en la lista ligada circularmente   
@Param T value: (string) archivo a leer, (LinkedList <std::string>) estructura de datos   
Complejidad de tiempo: O(n)
Complejidad de espacio: O(1)
*/
void readFileCirc(std::string filePath,circularLinkedList <std::string>* lista ){

    std::ifstream inputFile(filePath);
    std::string line;

    while (getline (inputFile , line)) {
        lista->create(line);
    }

}

int main()
{

    std::cout << "------------------------------------------------------------------------------ Lista Ligada ------------------------------------------------------------------------------" << "\n";

    //Leyendo el archivo y creando la lista ligada con cada linea 
    linkedList <std::string>* lista = new linkedList<std::string>();
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
    std::cout << "El nodo actualizado tiene la siguiente información:" << "\n";
    lista->update(2, "Nodo Actualizado");
    lista->read(2);
    std::cout << "Actualización exitosa \n\n";

    //Eliminando un nodo dentro de la estructura
    std::cout << "La posicón del nodo que se va a eliminar es: 0 \n";
    std::cout << "El nodo en la posición 0 que se va a eliminar tiene la siguiente información: \n";
    lista->read(0);
    lista->del(0);
    std::cout << "El nodo fue exitosamente eliminado \n";
    std::cout << "Ahora el nodo en la posición 0 es:\n";
    lista->read(0);
    std::cout << "\n";


    std::cout << "------------------------------------------------------------------------------ Lista Doblemente Ligada ------------------------------------------------------------------------------" << "\n";

    doubleLinkedList <std::string>* listaDoble = new doubleLinkedList<std::string>();
    readFile2("bitacora.txt", listaDoble);

    //Agrega un nuevo nodo a la estructura de datos en la ultima posición
    std::cout << "A continuación se agregará un nodo en la ultima posición" << "\n";
    listaDoble->createAtEnd("Nuevo Nodo");
    std::cout << "El nodo agregado tiene la siguiente informacion: " << "\n";
    listaDoble->read(listaDoble->size - 1);
    std::cout << "\n";
    
    //Buscando un elemento dentro de la estructura de datos 
    std::cout << "El nodo en la posición 4 tiene la siguiente información: ";
    listaDoble->read(4);
    std::cout << "\n";

    //Actualizando un nodo dentro de la estructura 
    std::cout << "La posicón del nodo que se va a actualizar es: 2 \n";
    std::cout << "Informacion del nodo a actualizar: ";
    listaDoble->read(2);
    std::cout << "El nodo actualizado tiene la siguiente información:" << "\n";
    listaDoble->update(2, "Nodo Actualizado");
    listaDoble->read(2);
    std::cout << "Actualización exitosa \n\n";

    //Eliminando un nodo dentro de la estructura
    std::cout << "La posicón del nodo que se va a eliminar es: 0 \n";
    std::cout << "El nodo en la posición 0 que se va a eliminar tiene la siguiente información: \n";
    listaDoble->read(0);
    listaDoble->del(0);
    std::cout << "El nodo fue exitosamente eliminado \n";
    std::cout << "Ahora el nodo en la posición 0 es:\n";
    listaDoble->read(0);
    std::cout << "\n";

    //Se imprime la información del penúltimo nodo para comprobar que si es una lista doblemente ligada 
    std::cout << "Imprimiendo la información del penúltimo nodo para comprobar que si es una lista doblemente ligada: \n";
    listaDoble->test();


    std::cout << "------------------------------------------------------------------------------ Lista Ligada Circularmente ------------------------------------------------------------------------------" << "\n";

/*
    circularLinkedList <std::string>* listaCircular = new circularLinkedList<std::string>();
    readFileCirc("bitacora.txt", listaCircular);

    //listaCircular->printList();
    //listaCircular->read(16806);
    listaCircular->create("Nodo creado");
    listaCircular->read(listaCircular->size - 1);
    listaCircular->update(listaCircular->size-1, "Nodo cambiado");
    listaCircular->read(listaCircular->size - 1);
    listaCircular->del(listaCircular->size-1);
    listaCircular->read(listaCircular->size - 1);
    listaCircular->test();
    //cambiar size a -1 en ves de 0
*/
    


}