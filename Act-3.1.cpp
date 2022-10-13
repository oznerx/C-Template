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
class BST
{
private:

    Node<T> *root;

public:

    BST(){
        root = nullptr;
    }; 

    bool search(int value){

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

    void preorder(Node<T>* r){

        if (r != nullptr) {
            std::cout << r->data << " ";
            preorder(r->left);
            preorder(r->right);
        }

    }

    void inorder(Node<T>* r){ 

        if ( r != nullptr){ 
            inorder (r->left);
            std::cout << r->data << " ";
            inorder (r->right);
        }

    }

    void postorder(Node<T>* r){ 

        if ( r != nullptr){
            postorder (r->left);
            postorder (r->right);
            std::cout << r->data << " ";
        }

    }

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
    Complejidad de tiempo: O()
    Complejidad de espacio: O()
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

    int getHeight(Node<T>* node){

        int heightLeft = 0;
        int heightRight = 0;

        if (node->left!=nullptr) {
            heightLeft = getHeight(node->left);
        }
            
        if (node->right!=nullptr) {
            heightRight = getHeight(node->right);
        }
            
        if (heightLeft > heightRight) {
            return heightLeft+1;
        }

        else {
            return heightRight+1;
        }

    }

    /*
    Regresará la altura del BST
    @Param: nada
    Salida: (int height) altura del BST
    Complejidad de tiempo: O()
    Complejidad de espacio: O()
    */
    int height(){

        if (root == nullptr) {
            std::cout << "El árbol no existe\n";
        }
        
        return getHeight(root);

    }

    /*
    Desplegará los ancestros de un dato
    @Param: (int data) El dato del cual se desea conocer los ancestros
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O()
    */
    void ancestors(int value){
        
        if (root == nullptr) {
            std::cout << "El árbol no existe\n";
        }

        else {
            
            Node<T>* current = root;

            while (current != nullptr && current->data != value ){

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



};







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
    std::vector <int> numbers = {12, 7, 4, 2, 9, 8, 11, 21, 16, 19, 25};
    BST<int>* binarySearchTree = new BST<int>();

    for( int i = 0 ; i < numbers.size() ; i++ ){
        binarySearchTree->create(numbers[i]);
    };

    if (binarySearchTree->search(19)){
        std::cout << "Existe\n";
    }

    else{
        std::cout << "No existe\n";
    }

    binarySearchTree->visit(4);

    std::cout << binarySearchTree->height();
    std::cout << "\n";

    binarySearchTree->ancestors(11);

}

/*
Referencias:

    https://www.youtube.com/watch?v=YJN-r6qjdQU    
    https://stackoverflow.com/questions/2597637/finding-height-in-binary-search-tree
    
*/