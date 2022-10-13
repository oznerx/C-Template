#include <iostream>
#include <vector>

/*
Ozner Axel Leyva Mariscal
A01742377
16 de Octubre del 2022
En este código se implementarán y agregarán las funcionalidades avanzadas 
al ADT de un BST con las funcionalidades fundamentales
*/

template <class T>
class Node { 
public:

    T data;
    Node *left;
    Node *right;

    Node(){ 
        left = nullptr;
        right= nullptr; 
    }

    Node(T value){
        data = value; 
        left = nullptr;
        right= nullptr; 
    }

};

template <class T>
class BST
{
private:

    Node<T> *root;

public:

    BST(){
        root = nullptr;
    }; 

    bool search(int valor){

        Node<T> *current = root;

        while (current != nullptr){ 

            if (current->data == valor){
                return true;
            }

            else{
                current = ( current->data > valor ? current->left : current->right);
            }

        }

        return false;

    }

    void create(T value){
        
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = root;
        Node<T>* father = nullptr;

        if (root == nullptr){
            root = newNode;
            std::cout << "root\n";
        }

        else{

            while(current != nullptr){
                
                father = current;
                
                if(value == current->data){
                    std::cout << "error";
                }

                else if(value < current->data){
                    current = current->left;
                    std::cout << "left\n";
                }

                else{
                    current = current->right;
                    std::cout << "right\n";
                }

            }

            if( value < father->data ){
                father->left = newNode;
            }
            else{
                father->right = newNode;
            }

        }

    } 
};

/*
Desplegará cada uno de los datos almacenados en el BST dependiendo del parámetro en entrada
@Param:(int opc) opción del orden en el que se quiere desplegar los datos 
Salida: nada
Complejidad de tiempo: O()
Complejidad de espacio: O()
*/
void visit (int opc){
    //validar si es un BST válido

}

/*
Regresará la altura del BST
@Param: nada
Salida: (int height) altura del BST
Complejidad de tiempo: O()
Complejidad de espacio: O()
*/
int height (){
    //validar si es un BST válido
    int height;
    return height;
}

/*
Desplegará los ancestros de un dato
@Param: (int data) El dato del cual se desea conocer los ancestros
Salida: nada
Complejidad de tiempo: O()
Complejidad de espacio: O()
*/
void ancestors (int data){
    //validar si es un BST válido
}

/*
Regresará un entero que indica el nivel en que se encuentra un dato, 
regresa -1 en caso de que no se encuentre en el BST
@Param: (int data) El dato a buscar su nivel
Salida: (int level) Entero indicando el nivel del dato en el BST, o -1 si no se encuentra
Complejidad de tiempo: O()
Complejidad de espacio: O()
*/
int whatlevelamI (int data){
    //validar si es un BST válido
    int level; // retorna -1 si no se encuentra 
    return level;
}


int main()
{
    std::vector <int> numbers = {30,21,33,32,41,43};
    BST<int>* binarySearchTree = new BST<int>();

    for( int i = 0 ; i < numbers.size() ; i++ ){
        binarySearchTree->create(numbers[i]);
    };

    if (binarySearchTree->search(43)){
        std::cout << "Si\n";
    }

    else{
        std::cout << "No\n";
    }

}