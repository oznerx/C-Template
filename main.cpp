#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

template <class T>
class Node
{
public:

    T data;
    Node<T>* next; // Se crea el apuntador tipo T que hace referencia al siguiente nodo
    Node(T dataValue) {
        data = dataValue; // Se le agrega el dato al nodo 
        next = nullptr; // Se le asigna un valor al siguiente nodo, si existe pero no tiene nada
    }

};


template <class T>
class LinkedList {
private:

    Node<T>* head; // Se crea la cabeza (el primer dato que tiene)

public:
    int size = 0; // Para solicitar el size de la lista sin consumir tanta memoria 
    LinkedList() {
        head = nullptr; // Se indica que es una lista vacia pero existe 
    }
    /*
    Añade  T value a la lista
    @Param T value: elemento añadir del tipo T T
    */
    void add(T value) {
        size++;
        Node<T>* new_node = new Node<T>(value); // Se crea un nuevo nodo con el valor indicado en la funcion 
        if (head == nullptr) { // Si la lista no tierne ningun valor aun, entonces nuestro nodo va como primer dato
            head = new_node; 
        }
        else { // Si la lista ya tiene elementos (nodos) dentro, entonces: 
            Node<T>* current = head; // Se crea una variable que dice que nos encontramos en el primer elemento
            while (current->next != nullptr) { // Recorre todos los elementos de la lista hasta encontrar un elemento 'next' vacio 
                current = current->next;
            }
            current->next = new_node; // Una vez llegado al ultimo nodo de la lista, se agrega el nuevo nodo como siguiente 

        }


    }

    /*
     Remueve un elemento en la posición index
     @Param int index: ìndice del elemento a añadir
     */
    void removeAt(int index) 
    {
        if (index < 0) { // si la posicionn que quieres eliminar es negativa, simplemente te regresa 
            return;
        }
        Node<T>* last = head; // se crea la variable last para poder recorrer la lista
        Node<T>* previous = nullptr;
        if (head == nullptr) { // si el primer elemnto no existe, entonces solo se regresa 
            return;
        }
        else { // si la lista si tiene elementos, entonces se hace lo siguiente: 
            int i = 0;
            // basicamente se recorre la lista para asi terminar justo en el elemento a eliminar 
            while (i < index && last->next != NULL) { // mientras que el elemento 'next' de 'last' osea el el valor actual no este vacio, entonces se hace lo siguiente:  
                previous = last; // basicamente aqui 'previous' y 'last' tienen los mismos valores (el ultimo elemento recorrido)
                last = last->next; // el valor de 'last' se convierte en el elemento actual 
                i++;
            }
            // recuerda que 'last->next' es ahora el elemnto actual 
            if (i == 0) { // si el elemento 'next' de 'last' osea el el valor actual esta vacio (el elemnto a borrar es el primero en la lista) se hara lo siguiente:
                head = last->next; // nuetro primer elemento sera el actual, osea el de la posicion 1 ahora es el de la 0 
                free(last); // se eliminara el primer elemto que en este caso es 'last'  
                size--; // se reduce el size de la lista
                return;
            }
            if (i == index) { // si el elemento se encuentra despues de recorrer la lista, se hara lo siguiente: 
                previous->next = last->next; // se le asigna al siguiente elemento den 'previous' (actual) que ahora si es el actual 
                size--; // se reduce el size de la lista
                free(last); // se elimina el elemento actual de la lista
            }
        }
    }

    /*
  Remueve un elemento en la posición index
  @Param int index: ìndice del elemento a añadir
  */
    T get(int index)
    {
        if (index < 0) { // solo se verifica que el indice no sea negativo
            return 0;
        }
        Node<T>* last = head; // se dice que nuestro ultimo nodo leido es igual al primero de la lista
        Node<T>* previous = nullptr;
        if (head == nullptr) { // si la lista no existe entonces solo regresa 
            return 0;
        }
        else {
            int i = 0;
            while (i < index && last->next != nullptr) { // mientras que el elemento 'next' de 'last' osea el el valor actual no este vacio, entonces se hace lo siguiente:  
                previous = last; // basicamente aqui 'previous' y 'last' tienen los mismos valores (el ultimo elemento recorrido)
                last = last->next; // el valor de 'last' se convierte en el elemento actual
                i++;
            }
            if (i == index) { // si se encuentra el indice del  valor despues del while, se hace lo siguiente:
                return last->data; // como 'last' es el valor actual, se retorna la data del nodo
            }
        }
        return 0;
    }

    void printList()
    {
        Node<T>* current = head; // se dice que nos encontramos en el primer elemento de la lista  
        while (current != NULL) { // si la lista si tiene elementos, se hara lo siguiente: 
            cout << current->data << " "; // se imprime la data con un espacio entre cada valor 
            current = current->next; // se asigna al valor siguiente de la lista con el proposito de recorrela
        }
        cout << "\n";
    }


};

int main()
{
    LinkedList <int>* lista = new LinkedList<int>();
    lista->add(1);
    lista->add(2);
    //lista->printList();
    cout << lista->get(0);
}