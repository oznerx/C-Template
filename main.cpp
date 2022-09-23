#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

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
    Añade  T value a la lista
    @Param T value: elemento añadir del tipo T T
    */
    void add(T value) {
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
     Remueve un elemento en la posición index
     @Param int index: ìndice del elemento a añadir
     */
    void removeAt(int index)
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

    /*
  Remueve un elemento en la posición index
  @Param int index: ìndice del elemento a añadir
  */
    T get(int index)
    {
        if (index < 0) {
            return NULL;
        }
        Node<T>* last = head;
        Node<T>* previous = nullptr;
        if (head == nullptr) {
            return NULL;
        }
        else {
            int i = 0;
            while (i < index && last->next != nullptr) {
                previous = last;
                last = last->next;
                i++;
            }
            if (i == index) {
                return last->data;
            }
        }
        return NULL;
    }

    void printList()
    {
        Node<T>* current = head;
        while (current != NULL) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n";
    }


};

int main()
{
    LinkedList <int>* lista = new LinkedList<int>();
    lista->add(1);
    lista->add(2);
    lista->printList();
}