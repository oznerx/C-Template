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

    NodoPtr find(NodoPtr nodo, long long ip) {

        if (nodo == nullptr || ip == nodo->ip) {
            return nodo;
        }

        if (ip < nodo->ip) {
            return find(nodo->izquierdo, ip);
        }

        return find(nodo->derecho, ip);

    }

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

    NodoPtr find(long long  k) {

        NodoPtr x = find(this->raiz, k);

        if (x) {
            x->accesos++;
            biselar(x);
        }

        return x;
        
    }

    NodoPtr minimo(NodoPtr nodo) {

        while (nodo->izquierdo != nullptr) {
            nodo = nodo->izquierdo;
        }

        return nodo;

    }

    NodoPtr maximo(NodoPtr nodo) {

        while (nodo->derecho != nullptr) {
            nodo = nodo->derecho;
        }

        return nodo;

    }

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
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void inorder(NodoPtr r){ 

        if ( r != nullptr){ 
            inorder (r->izquierdo);
            imprimeIp(r->ip);
            inorder (r->derecho);
        }

    }

    void print() {
        //implementar print inorder
        inorder(this->raiz);
        cout << "\n";
    }

    int size() {
        return s;
    }

};

int main() {

    setlocale(LC_ALL, "es_ES.UTF-8");

    ArbolBiselado bst;
    bst.insert(333333333);
    bst.insert(44);
    bst.insert(64444447);
    bst.insert(62222229);
    bst.insert(4294967295);
    bst.insert(2);
    bst.insert(89);
    bst.insert(41);
    bst.insert(98);
    bst.insert(1);
    bst.imprimeArbol();
    bst.find(4294967295);
    bst.imprimeArbol();
    bst.find(44);
    bst.imprimeArbol();
    bst.del(333333333);
    bst.imprimeArbol();
    bst.del(41);
    bst.imprimeArbol();
    bst.del(98);
    bst.del(1);
    bst.del(44);
    bst.imprimeArbol();

    cout << bst.size() << "\n";
    bst.print();

    return 0;

}