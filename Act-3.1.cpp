#include <iostream>
#include <vector>
#include <queue>

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
class Bst
{
private:

    Node<T> *root;

public:

    Bst(){
        root = nullptr;
    }; 

    /*
    Retornará verdadero o falso dependiendo si se encuentra el dato buscado
    @Param: (int value) datos que se quiere buscar  
    Salida: (bool) si se encontró es verdadero, si no, es falso
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    bool search(int value){

        if (root == nullptr) {
            return false;
        }

        else {

            Node<T> *current = root;

            while (current != nullptr){ 

                if (current->data == value){
                    return true;
                }

                else{
                    current = ( current->data > value ? current->left : current->right);
                }

            }

            return false;

        }

    }

    /*
    Agrega datos al árbol 
    @Param: (T value) datos que se quiere agregar   
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void create(T value){
        
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = root;
        Node<T>* father = nullptr;

        if (root == nullptr){
            root = newNode;
        }

        else{

            while(current != nullptr){
                
                father = current;
                
                if(value == current->data){
                }

                else if(value < current->data){
                    current = current->left;
                }

                else{
                    current = current->right;
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

    /*
    Imprime los datos del árbol en preorder  
    @Param: (Node<T>* r) raíz del arbol a imprimir    
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void preorder(Node<T>* r){

        if (r != nullptr) {
            std::cout << r->data << " ";
            preorder(r->left);
            preorder(r->right);
        }

    }

    /*
    Imprime los datos del árbol en inorder  
    @Param: (Node<T>* r) raíz del arbol a imprimir    
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void inorder(Node<T>* r){ 

        if ( r != nullptr){ 
            inorder (r->left);
            std::cout << r->data << " ";
            inorder (r->right);
        }

    }

    /*
    Imprime los datos del árbol en postorder  
    @Param: (Node<T>* r) raíz del arbol a imprimir    
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void postorder(Node<T>* r){ 

        if ( r != nullptr){
            postorder (r->left);
            postorder (r->right);
            std::cout << r->data << " ";
        }

    }

    /*
    Imprime los datos del árbol nivel por nivel  
    @Param: (Node<T>* r) raíz del arbol a imprimir    
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void levelByLevel(Node<T>* r){
        
        if(r == nullptr){
            return;
        }

        std::queue<Node<T>*> que;
        que.push(r);

        while(!que.empty()){

            r = que.front();
            que.pop();
            std::cout << r->data << " ";

            if(r->left != nullptr){
                que.push(r->left);
            }

            if(r->right != nullptr){
                que.push(r->right);
            }

        }

    }

    /*
    Desplegará cada uno de los datos almacenados en el BST dependiendo del parámetro en entrada
    @Param:(int opc) opción del orden en el que se quiere desplegar los datos 
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void visit(int opc){

        if (root == nullptr) {
            std::cout << "El árbol no existe\n";
        }

        else {
            
            if (opc == 1){
                preorder(root);
                std::cout << "\n";
            }
            
            else if (opc == 2){
                inorder(root);
                std::cout << "\n";
            }

            else if (opc == 3){
                postorder(root);
                std::cout << "\n";
            }

            else if (opc == 4){
                levelByLevel(root);
                std::cout << "\n";
            }

            else {
                std::cout << "Opción invalida\n";
            }

        }

    }

    /*
    Retornará la altura del árbol
    @Param: (Node<T>* node) raíz del arbol   
    Salida: (int) altura del árbol
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    int getHeight(Node<T>* node){

        if (node == nullptr) {
            return -1;
        }

        else {
            
            int heightLeft = getHeight(node->left);
            int heightRight = getHeight(node->right);

            if (node->left!=nullptr) {
                heightLeft = getHeight(node->left);
            }
                
            if (node->right!=nullptr) {
                heightRight = getHeight(node->right);
            }
                
            if (heightLeft > heightRight) {
                return heightLeft + 1;
            }

            else {
                return heightRight + 1;
            }

        }

    }

    /*
    Retornará la altura del BST
    @Param: nada
    Salida: (int height) altura del BST
    Complejidad de tiempo: O(log n)
    Complejidad de espacio: O(log n)
    */
    int height(){

        if (root == nullptr) {
            std::cout << "El árbol no existe\n";
        }
        
        return getHeight(root);

    }

    /*
    Desplegará los ancestros de un dato
    @Param: (int value) El dato del cual se desea conocer los ancestros
    Salida: nada
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1) 
    Nota: no se usa stack para no tener una complejidad de O(n), 
    es por ello que se imprimen los datos de raiz hasta el valor deseado y no viceversa 
    */
    void ancestors(int value){
        
        if (root == nullptr) {
            std::cout << "El árbol no existe\n";
        }

        else if (search(value)) {
                    
            if (root->data == value) {
                std::cout << "El dato no tiene ancestros, es el nodo raíz\n";
            }

            else {

                Node<T>* current = root;

                while (current != nullptr && current->data != value ) {

                    std::cout << current->data << " ";

                    if (value < current->data) {
                        current = current->left;
                    }

                    else {
                        current = current->right;
                    }

                }

                std::cout << "\n";

            }

        }

        else {
            std::cout << "El dato no existe en el árbol\n";
        }
        
    }

    /*
    Regresará un entero que indica el nivel en que se encuentra un dato, 
    regresa -1 en caso de que no se encuentre en el BST
    @Param: (int value) El dato a buscar su nivel
    Salida: (int level) Entero indicando el nivel del dato en el BST, o -1 si no se encuentra
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    int whatlevelamI (int value){
        
        if (root == nullptr || !search(value)) {
            return -1;
        }

        else {

            int level;
            Node<T>* current = root;

            while (current != nullptr && current->data != value ) {

                if (value < current->data) {
                    current = current->left;
                }

                else {
                    current = current->right;
                }

                level++;

            }

            return level;

        }

    }

};

int main()
{
    
    std::cout << "\n-------- Funciones de con un árbol binario de busqueda BST --------\n\n";

    std::cout << "Creando árbol...\n\n";
    std::vector <int> numbers = {12, 7, 4, 2, 9, 8, 11, 21, 16, 19, 25};
    Bst<int>* binarySearchTree = new Bst<int>();

    for( int i = 0 ; i < numbers.size() ; i++ ){
        binarySearchTree->create(numbers[i]);
    };
    
    std::cout << "Desplegando datos en Preorder: ";
    binarySearchTree->visit(1);
    std::cout << "\n";

    std::cout << "Desplegando datos Inorder: ";
    binarySearchTree->visit(2);
    std::cout << "\n";

    std::cout << "Desplegando datos en Postorder: ";
    binarySearchTree->visit(3);
    std::cout << "\n";

    std::cout << "Desplegando datos Level by Level: ";
    binarySearchTree->visit(4);
    std::cout << "\n";

    std::cout << "La altura del árbol es de: ";
    std::cout << binarySearchTree->height();
    std::cout << "\n\n";

    std::cout << "Desplegando todos los ancestros del dato 11: ";
    binarySearchTree->ancestors(11);
    std::cout << "\n";

    std::cout << "Desplegando todos los ancestros del dato 4: ";
    binarySearchTree->ancestors(4);
    std::cout << "\n";

    std::cout << "Desplegando todos los ancestros del dato 21: ";
    binarySearchTree->ancestors(21);
    std::cout << "\n";

    std::cout << "Desplegando todos los ancestros del dato 19: ";
    binarySearchTree->ancestors(19);
    std::cout << "\n";

    std::cout << "Nivel en el que se encuentra el dato 16: ";
    std::cout << binarySearchTree->whatlevelamI(16);
    std::cout << "\n\n";

    std::cout << "Nivel en el que se encuentra el dato 2: ";
    std::cout << binarySearchTree->whatlevelamI(2);
    std::cout << "\n\n";

    std::cout << "Nivel en el que se encuentra el dato 8: ";
    std::cout << binarySearchTree->whatlevelamI(8);
    std::cout << "\n\n";

    std::cout << "Nivel en el que se encuentra el dato 25: ";
    std::cout << binarySearchTree->whatlevelamI(25);
    std::cout << "\n\n";

    std::cout << "------------------------ Prueba de errores ------------------------\n\n";

    Bst<int>* emptyBinarySearchTree = new Bst<int>();

    std::cout << "Ingresando un BST no válido al desplegar datos: ";
    emptyBinarySearchTree->visit(1);
    std::cout << "\n";

    std::cout << "Ingresando una opción incorrecta para desplegar datos: ";
    binarySearchTree->visit(0);
    std::cout << "\n";

    std::cout << "Ingresando un BST no válido para desplegar la altura: ";
    emptyBinarySearchTree->height();
    std::cout << "\n";

    std::cout << "Ingresando un BST no válido para desplegar los ancestros: ";
    emptyBinarySearchTree->ancestors(1);
    std::cout << "\n";

    std::cout << "Ingresando el nodo raíz con valor de 12 para desplegar los ancestros: ";
    binarySearchTree->ancestors(12);
    std::cout << "\n";

    std::cout << "El dato no se encuentra en el árbol para desplegar los ancestros: ";
    binarySearchTree->ancestors(1);
    std::cout << "\n";

    std::cout << "Ingresando un BST no válido para desplegar el nivel: ";
    std::cout << emptyBinarySearchTree->whatlevelamI(0);
    std::cout << "\n\n";

    std::cout << "El dato no se encuentra en el árbol para desplegar el nivel: ";
    std::cout << binarySearchTree->whatlevelamI(1);
    std::cout << "\n\n";

}

/*
Referencias:

    CppNuts. (2021, 11 de mayo). Level Order Traversal Of Binary Tree - BFS [video]. YouTube. https://www.youtube.com/watch?v=YJN-r6qjdQU
        
*/