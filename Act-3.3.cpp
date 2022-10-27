/*
Ozner Axel Leyva Mariscal
A01742377
3 de Noviembre del 2022
En este código se implementará un splay tree y sus funcionalidades como insert, delete, find, print y size. 
Referencias: http://algorithmtutor.com/ip-Structures/Tree/Splay-Trees/
*/

#include <iostream>
#include <locale.h>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Nodo {
public:

    Nodo(long long valor ) {
        accesos = 0;
        ip = valor;
        progenitore = NULL;
        izquierdo = NULL;
        derecho = NULL;
    }

    long long ip=0; 
    int accesos = 0; 
    Nodo* progenitore; 
    Nodo* izquierdo; 
    Nodo* derecho; 

};

typedef Nodo* NodoPtr;
class ArbolBiselado {
private:

    NodoPtr raiz;
    int s = 0;

    /*
    Encuentra un dato del Splay Tree
    @Param: (NodoPtr nodo) nodo a partir de donde se quiere buscar, (long long ip) dato que se desea buscar en el Splay Tree  
    Salida: (NodoPtr x) nodo buscado
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(1) (sin tomar en cuenta la multiplicacion de complejidades con "biselar")
    */
    NodoPtr find(NodoPtr nodo, long long ip) {

        if (nodo == nullptr || ip == nodo->ip) {
            return nodo;
        }

        if (ip < nodo->ip) {
            return find(nodo->izquierdo, ip);
        }

        return find(nodo->derecho, ip);

    }

    /*
    Elimina un dato del Splay Tree
    @Param: (long long ip) dato que se desea borrar del Splay Tree , (NodoPtr nodo) nodo raíz del árbol
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(n) ?????
    */
    void del(NodoPtr nodo, long long ip) {

        NodoPtr eliminado = nullptr;
        NodoPtr t, s;

        while (nodo != nullptr) {

            if (nodo->ip == ip) {
                eliminado = nodo;
            }

            if (nodo->ip <= ip) {
                nodo = nodo->derecho;
            }

            else {
                nodo = nodo->izquierdo;
            }

        }

        if (eliminado == nullptr) {
            cout << "No se encontró la IP" << endl;
            return;
        }

        divide(eliminado, s, t);

        if (s->izquierdo) { // elimina el nodo
            s->izquierdo->progenitore = nullptr;
        }

        //une los dos subárboles
        raiz = une(s->izquierdo, t);

        //libera memoria
        delete(s);
        s = nullptr;

    }

    /*
    Imprime la ip del nodo 
    @Param: (long long value) valor del nodo que se desea imprimir 
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void imprimeIp(long long value) {

        string valorAImprimir = "";
        int contador = 0;
        stack<int>*s = new stack<int>();

        while (value > 0) {
            s->push(value % 256);
            value = value / 256;
            contador++;
        }

        int contador2 = contador;

        while (contador < 4) {
            cout << "0.";
            contador++;
        }

        while (!s->empty() ){

            cout << s->top();

            if (contador2 > 1) {
                cout << ".";
            }

            s->pop();
            contador2--;

        }
        
        cout << "  ";

    }

    /*
    Imprime una simulación de un árbol
    @Param: (NodoPtr raiz) nodo raíz, (string relleno) caracteres especiales para la estructura, (bool ultimo) bandera para identificar el último elemento 
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void imprime(NodoPtr raiz, string rellleno, bool ultimo) {

        if (raiz != nullptr) {

            cout << rellleno;

            if (ultimo) {
                cout << "└────";
                rellleno += "     ";
            }

            else {
                cout << "├────";
                rellleno += "|    ";

            }

            imprimeIp(raiz->ip);
            cout <<  "," << raiz->accesos << endl;
            imprime(raiz->izquierdo, rellleno, false);
            imprime(raiz->derecho, rellleno, true);

        }

    }

    /*
    Rota los elemntos del árbol hacia la izquierda 
    @Param: (NodoPtr nodo) nodo progenitor del cual se va a rotar 
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void rotarIzquierda(NodoPtr nodo) {

        NodoPtr y = nodo->derecho;
        nodo->derecho = y->izquierdo;

        if (y->izquierdo != nullptr) {
            y->izquierdo->progenitore = nodo;
        }

        y->progenitore = nodo->progenitore;

        if (nodo->progenitore == nullptr) {
            this->raiz = y;
        }

        else if (nodo == nodo->progenitore->izquierdo) {
            nodo->progenitore->izquierdo = y;
        }

        else {
            nodo->progenitore->derecho = y;
        }

        y->izquierdo = nodo;
        nodo->progenitore = y;

    }

    /*
    Rota los elemntos del árbol hacia la derecha 
    @Param: (NodoPtr nodo) nodo progenitor del cual se va a rotar 
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void rotarDerecha(NodoPtr nodo) {

        NodoPtr y = nodo->izquierdo;
        //y es igual al hijo izquierdo

        nodo->izquierdo = y->derecho;
        //l izquierdo del nodo rotado apunta al derecho del hijo izquierdo, balanceo

        if (y->derecho != nullptr) {
            y->derecho->progenitore = nodo;
        }
        // si se hizo el balanceo el progenitor es el nuevo padre

        y->progenitore = nodo->progenitore;
        // si es raiz actualizar raíz

        if (nodo->progenitore == nullptr) {
            this->raiz = y;
        }

        else if (nodo == nodo->progenitore->derecho) {
            // el hijo derecho del padre del nodo es y
            nodo->progenitore->derecho = y;
        }

        else {
            //el  hijo izquierdo del padre del nodo es y
            nodo->progenitore->izquierdo = y;
        }

        // establece lado derecho
        y->derecho = nodo;
        // establece padre

        nodo->progenitore = y;

    }

    /*
    Hace el biselado en el árbol
    @Param: (NodoPtr nodo) nodo progenitor del cual se va a rotar para el biselado
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void biselar(NodoPtr nodo) {

        while (nodo->progenitore) {

            if (!nodo->progenitore->progenitore) {

                if (nodo == nodo->progenitore->izquierdo) {
                    // zig
                    rotarDerecha(nodo->progenitore);
                }

                else {
                    // zag 
                    rotarIzquierda(nodo->progenitore);
                }

            }

            else if (nodo == nodo->progenitore->izquierdo && nodo->progenitore == nodo->progenitore->progenitore->izquierdo) {
                // zig-zig 
                rotarDerecha(nodo->progenitore->progenitore);
                rotarDerecha(nodo->progenitore);
            }

            else if (nodo == nodo->progenitore->derecho && nodo->progenitore == nodo->progenitore->progenitore->derecho) {
                // zag-zag
                rotarIzquierda(nodo->progenitore->progenitore);
                rotarIzquierda(nodo->progenitore);
            }

            else if (nodo == nodo->progenitore->derecho && nodo->progenitore == nodo->progenitore->progenitore->izquierdo) {
                // zig-zag 
                rotarIzquierda(nodo->progenitore);
                rotarDerecha(nodo->progenitore);
            }

            else {
                // zag-zig 
                rotarDerecha(nodo->progenitore);
                rotarIzquierda(nodo->progenitore);
            }

        }

    }

    /*
    Une las dos secciones del árbol dividido
    @Param: (NodoPtr s) parte izquierda del árbol , (NodoPtr t) parte derecha del árbol
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    NodoPtr une(NodoPtr s, NodoPtr t) {

        if (!s) {
            return t;
        }

        if (!t) {
            return s;
        }

        NodoPtr x = maximo(s);
        biselar(x);
        x->derecho = t;
        t->progenitore = x;
        return x;

    }

    /*
    Divide en dos secciones el árbol 
    @Param: (NodoPtr x) progenitor , (NodoPtr s) parte izquierda del árbol , (NodoPtr t) parte derecha del árbol
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    void divide(NodoPtr& x, NodoPtr& s, NodoPtr& t) {

        biselar(x);

        if (x->derecho) {
            t = x->derecho;
            t->progenitore = nullptr;
        }

        else {
            t = nullptr;
        }

        s = x;
        s->derecho = nullptr;
        x = nullptr;

    }

public:

    ArbolBiselado() {
        raiz = nullptr;
    }

    /*
    Encuentra un dato del Splay Tree
    @Param: (long long k) dato que se desea buscar en el Splay Tree  
    Salida: (bool) valor que indica si se encontró el dato en el árbol, true si se encontra, false si no se encuentra    
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(1) (sin tomar en cuenta la multiplicacion de complejidades con "biselar")
    */
    bool find(long long k) {

        NodoPtr x = find(this->raiz, k);

        if (x) {
            x->accesos++;
            biselar(x);
            return true;
        }

        return false; 
        
    }

    /*
    Retorna el mínimo nodo del árbol
    @Param: (NodoPtr nodo) nodo a partir del cual se va a empezar el recorrido  
    Salida: (NodoPtr nodo) nodo minimo
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1) 
    */
    NodoPtr minimo(NodoPtr nodo) {

        while (nodo->izquierdo != nullptr) {
            nodo = nodo->izquierdo;
        }

        return nodo;

    }

    /*
    Retorna el máximo nodo del árbol
    @Param: (NodoPtr nodo) nodo a partir del cual se va a empezar el recorrido  
    Salida: (NodoPtr nodo) nodo máximo
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1) 
    */
    NodoPtr maximo(NodoPtr nodo) {

        while (nodo->derecho != nullptr) {
            nodo = nodo->derecho;
        }

        return nodo;

    }

    /*
    Agrega un dato al Splay Tree
    @Param: (long long key) valor que se desea agregar al Splay Tree  
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(1) (sin tomar en cuenta la multiplicacion de complejidades con "biselar")
    */
    void insert(long long key) {

        s++;
        NodoPtr nodo = new Nodo(key);
        nodo->progenitore = nullptr;
        nodo->izquierdo = nullptr;
        nodo->derecho = nullptr;
        nodo->ip = key;
        NodoPtr y = nullptr;
        NodoPtr x = this->raiz;

        while (x != nullptr) {

            y = x;

            if (nodo->ip < x->ip) {
                x = x->izquierdo;
            }

            else {
                x = x->derecho;
            }

        }

        // si  nunca se asignó y  AB vacío
        nodo->progenitore = y;
        
        if (y == nullptr) {
            raiz = nodo;
        }// Si es menor el valor a insertar es hijo izquierdo

        else if (nodo->ip < y->ip) {
            y->izquierdo = nodo;
        }// Si es mayor el valor a insertar es hijo derecho

        else {
            y->derecho = nodo;
        }

        //Biselar el nodo hasta la raíz
        biselar(nodo);

    }

    /*
    Elimina un dato del Splay Tree
    @Param: (long long key) dato que se desea borrar del Splay Tree  
    Salida: nada
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(n) ?????
    */ 
    void del(long long ip) {
        s--;
        del(this->raiz, ip);
    }

    void imprimeArbol() {
        imprime(this->raiz, "", true);
    }

    /*
    Imprime los datos del árbol en inorder  
    @Param: (Node<T>* r) raíz del arbol a imprimir    
    Salida: nada
    Complejidad de tiempo: O(n) (sin tomar en cuenta la multiplicación de imprimir los datos)
    Complejidad de espacio: O(n) 
    */
    void inorder(NodoPtr r){ 

        if ( r != nullptr){ 
            inorder (r->izquierdo);
            imprimeIp(r->ip);
            inorder (r->derecho);
        }

    }

    /*
 	Despliega en orden ascendentemente el contenido del Splay Tree.    
    @Param: nada  
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n) 
    */
    void print() {
        inorder(this->raiz);
        cout << "\n";
    }

    /*
    Regresa la cantidad de datos que tiene el Splay Tree.
    @Param: nada  
    Salida: (int s) Un valor que represena la cantidad de datos el Splay Tree.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
    */
    int size() {
        return s;
    }

};

int main() {

    setlocale(LC_ALL, "es_ES.UTF-8");

    ArbolBiselado bst;
    vector <long long int> numbers = {333333333, 44, 64444447, 62222229, 4294967295, 2, 89, 41, 98, 1};

    cout << "\nCreando árbol...\n";
    for (int i = 0; i < numbers.size(); i++) {
        bst.insert(numbers[i]);  
    }

    cout << "Elementos del árbol:\n";
    bst.print();
    cout << "El tamaño del árbol es de: ";
    cout << bst.size() << "\n\n";

    for (int i = 0; i < numbers.size()/2; i++) {

        cout << "Verificando que se encuentre el elemento " + to_string(numbers[i+i]) + " en el árbol: ";

        if ( bst.find(numbers[i+i]) ) {
            cout << "Si se encontró el dato en el árbol";
        }

        else {
            cout << "NO se encontró el dato en el árbol";
        }

        cout << "\n\n";

    } 

    cout << "Eliminando elementos del árbol...\n"; 
    for (int i = 0; i < numbers.size()-1; i++) {
        bst.del(numbers[i]);
        bst.print();
        cout << "El tamaño del árbol es de: ";
        cout << bst.size() << "\n\n";
    }

}