/*
Programa que realiza operaciones básicas de un Árbol Biselado o Splay tree, 
cumpliendo con las condiciones especiales de la estructura de datos.
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 01 de noviembre de 2022
*/

#include <iostream>
#include <locale.h>
#include <vector>

/*
Entidad básica de las estructuras de datos. Es especial para los 
árboles biselados, debido a que están conectadas a nodos padre e hijos 
izquierdo y derecho, así como contiene el número de veces que se accedió al nodo. 
Puede contener solamente enteros.
*/
class Node{
  int access;
  int data;
  public:
    Node* father; 
    Node* left; 
    Node* right;
  
    /* Constructor de un nodo. Los nodos padre e hijos son nulos. 
    Param: Nada.
    Return: Nada.
    */
    Node(){
      access = 0;
      father = nullptr;
      left = nullptr;
      right = nullptr;
    }
  
    /* Destructor de un nodo.
    Param: Nada.
    Return: Nada.
    */
    ~Node(){
      father = nullptr;
      right = nullptr;
      left = nullptr;
    }
  
    /* Establece el dato del nodo.
    Param: (int newData) nuevo dato del nodo.
    Return: Nada.
    */
    void setData(int newData){
      data = newData;
    }
  
    /* Aumenta el número de acceso del nodo
    Param: Nada.
    Return: Nada.
    */
    void incrementAccess(){
      access++;
    }
  
    /* Regresa el dato del nodo.
    Param: Nada.
    Return: int dato del nodo.
    */
    int getData(){
      return data;
    }
  
    /* Regresa el número de accesos del nodo
    Param: Nada.
    Return:int Número de accesos del nodo.
    */
    int getAccess(){
      return access;
    }
};

typedef Node* NodePtr;

/*
Base del Árbol Biselado (Splay Tree). Contiene las operaciones fundamentales 
de un Splay Tree.
*/
class SplayTree{
  private:
    NodePtr root;
    int amount = 0;

    /*
    Función ayudante de la función principal para encontrar un nodo en el árbol. 
    Param: (NodePtr current) Nodo actual del recorrido del árbol. 
    (int data) Información del nodo a buscar.
    Return: NodePtr Nodo regresado por el árbol para recorrer la estructura del Splay Tree.
    Caso promedio:
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(logn)
    Peor caso:
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    NodePtr find(NodePtr current, int data){
      if(current == nullptr || data == current->getData()){
        return current;
      }
    
      if(data < current->getData()){
        return find(current->left, data);
      }
    
      return find(current->right, data);
    }

    /*
    Función ayudante de la función principal del para eliminar un nodo del árbol.
    Param: (NodePtr current) Nodo actual del recorrrido del árbol. 
    (int data) Información del nodo a buscar.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(NodePtr current, int data){
      NodePtr erased = nullptr;
      NodePtr t, s;
      while(current != nullptr){
        if(current->getData() == data){
          erased = current;
          break;
        }

        if(current->getData() < data){
          current = current->right;
        }
          
        else{
          current = current->left;
        }
      }

      if(erased == nullptr){
        std::cout << "No se encontró el dato." << std::endl;
        return;
      }
    
      divide(erased, s, t); 
      if(s->left){ // elimina el nodo
        s->left->father = nullptr;
      }
      
      //une los dos subárboles
      root = join(s->left, t);
      //libera memoria
      delete s;
      amount--;
    }
  
    /* 
    Función que imprime los datos de los nodos en orden.
    Param: (NodePtr current) Nodo actual del recorrido por el árbol.
    Return: Nada.
    Complejidad de tiempo: O(n) 
    Complejidad de espacio: O(n)
    */
    void inOrder(NodePtr current){
      if(current != nullptr && root != nullptr){
        inOrder(current->left);
        std::cout<< current->getData() << " ";
        inOrder(current->right);
      }
        
      else if(root == nullptr){
        std::cout<<"Árbol vacío.";
      }
    }

    /*
    Función ayudante para rotar a la izquierda los elementos de un árbol.
    Param: (NodePtr node) Nodo a rotar.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void leftRotation(NodePtr node){
      NodePtr y = node->right;
      node->right = y->left;
      
      if(y->left != nullptr){
          y->left->father = node;
      }
    
      y->father = node->father;
      
      if(node->father == nullptr){
          root = y;
      }
        
      else if(node == node->father->left){
          node->father->left = y;
      }
        
      else{
          node->father->right = y;
      }
      
      y->left = node;
      node->father = y;
    }

    /*
    Función ayudante para rotar a la derecha los elementos de un árbol.
    Param: (NodePtr node) Nodo a rotar.
    Return: Nada.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void rightRotation(NodePtr node){
      NodePtr y = node->left;
      //y es igual al hijo izquierdo
      node->left = y->right;
      
      //el izquierdo del nodo rotado apunta al derecho del hijo izquierdo, balanceo
      if (y->right != nullptr){
        y->right->father = node;
      }
      // si se hizo el balanceo el progenitor es el nuevo padre

      y->father = node->father;
      
      // si es raiz actualizar raíz
      if(node->father == nullptr){
        root = y;
      }
        
      else if(node == node->father->right){
        // el hijo derecho del padre del nodo es y
        node->father->right = y;
      }
        
      else{
        //el hijo izquierdo del padre del nodo es y
        node->father->left = y;
      }
      
      // establece lado derecho
      y->right = node;
    
      // establece padre
      node->father = y;
    }

    /*
    Función para biselar el árbol. Realiza las rotaciones pertinentes de acuerdo
    a la posición del nodo a biselar.
    Param: (NodePtr current) Nodo a biselar.
    Return: Nada.
    Caso promedio:
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(1)
    Peor caso:
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void splay(NodePtr current){
      while(current->father){
        if(!current->father->father){
          if(current == current->father->left){
              // zig
              rightRotation(current->father);
          }
            
          else{
              // zag 
              leftRotation(current->father);
          }
        }
          
        else if(current == current->father->left && current->father == current->father->father->left){
            // zig-zig 
            rightRotation(current->father->father);
            rightRotation(current->father);
        }
          
        else if(current == current->father->right && current->father == current->father->father->right){
            // zag-zag
            leftRotation(current->father->father);
            leftRotation(current->father);
        }
          
        else if(current == current->father->right && current->father == current->father->father->left){
            // zig-zag 
            leftRotation(current->father);
            rightRotation(current->father);
        }
          
        else{
            // zag-zig 
            rightRotation(current->father);
            leftRotation(current->father);
        }
      }
    }

    /*
    Función para unir dos subárboles separados.
    Param: (NodePtr s) Subárbol izquierdo. (NodePtr t) Subárbol derecho.
    Return: NodePtr Nodo raíz.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    NodePtr join(NodePtr s, NodePtr t) {
      if (!s) {
        return t;
      }

      if (!t) {
        return s;
      }
      
      NodePtr x = max(s);
      splay(x);
      x->right = t;
      t->father = x;
      return x;
    }

    /*
    Función para separar un árbol en dos subárboles.
    Param: (NodePtr& x) Dirección del nodo pivote (NodePtr& s) Dirección del subárbol izquierdo. (NodePtr& t) Dirección del subárbol derecho.
    Return: NodePtr Nodo raíz.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void divide(NodePtr& x, NodePtr& s, NodePtr& t) {
      splay(x);
      
      if(x->right){
        t = x->right;
        t->father = nullptr;
      }
        
      else{
        t = nullptr;
      }
      
      s = x;
      s->right = nullptr;
      x = nullptr;
    }

  public:

    /*
    Constructor del árbol biselado. 
    */
    SplayTree(){
      root = nullptr;
    }

    /*
    Función para saber si el nodo con el dato buscado se encuentra en el árbol, así como
    biselar el nodo buscado.
    Param: (int data) Dato del nodo buscado.
    Return: bool Comprabación si se encontró el nodo o no.
    Caso promedio:
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(logn)
    Peor caso:
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    bool find(int data){
      if(root != nullptr){
        NodePtr x = find(root, data);
      
        if(x){
          x->incrementAccess();
          splay(x);
          return true;
        }
      
        return false; 
      }

      else{
        std::cout<<"Árbol vacío."<<std::endl<<std::endl;
        return false;
      }
    }

    /*
    Función para encontrar el mínimo de un árbol.
    Param: (NodePtr current) Nodo actual del recorrido por el árbol.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    NodePtr min(NodePtr current){
      while(current->left != nullptr){
        current = current->left;
      }
    
      return current;
    }

    /*
    Función para encontrar el máximo de un árbol.
    Param: (NodePtr current) Nodo actual del recorrido por el árbol.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    NodePtr max(NodePtr current){
      while(current->right != nullptr){
        current = current->right;
      }
      
      return current;
    }

    /*
    Función para insertar un nodo en el árbol.
    Param: (int data) Dato del nodo a insertar.
    Return: Nada.
    Caso promedio:
    Complejidad de tiempo: O(logn)
    Complejidad de espacio: O(1)
    Peor caso:
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void insert(int data) {   
      NodePtr previous = nullptr;
      NodePtr current = root;

      while(current != nullptr) {
        previous = current;

        if(current->getData() == data) {
          std::cout<<"Dato duplicado. Intente con otro número."<<std::endl;
          return;
        }
      
        else if(data < current->getData()) {
            current = current->left;
        }
          
        else{
            current = current->right;
        }
      }

      NodePtr newNode = new Node();
      newNode->setData(data);
      
      // si nunca se asignó y AB vacío
      newNode->father = previous;
      
      if(previous == nullptr) {
        root = newNode;
      }// Si es menor, el valor a insertar es hijo izquierdo
      
      else if(newNode->getData() < previous->getData()) {
        previous->left = newNode;
      }// Si es mayor, el valor a insertar es hijo derecho
        
      else{
        previous->right = newNode;
      }
      //Biselar el nodo hasta la raíz
      splay(newNode);
      amount++;
    }

    /* Función principal para eliminar un nodo del árbol.
    Param: (int data) Dato del nodo a eliminar.
    Return: Nada.  
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(1)
    */
    void del(int data) {
      del(root, data);
    }

    /*
    Función principal para imprimir los datos de los nodos en orden ascendente.
    Param: Nada.
    Return: Nada. 
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void print() {
      if(root != nullptr) {
        inOrder(root); 
      }

      else{
        std::cout<<"Árbol vacío."<<std::endl<<std::endl;
      }
    }

    /*
    Función que regresa a cantidad de datos en el árbol.
    Param: Nada.
    Return: int cantidad de datos en el árbol.
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    int size(){
      return amount;
    }

    /*
    Función ayudante para imprimir todo el árbol.
    Param: (NodePtr current) Nodo actual del recorrido por el árbol.
    (string indent) identación del árbol
    (bool last) bandera que comprueba si el elemento es el último.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void printHelper(NodePtr current, std::string indent, bool last) {
      if (current != nullptr) {
        std::cout<<indent;
        if (last) {
          std::cout<<"└────";
          indent += "     ";
         }
        
        else {
          std::cout<<"├────";
          indent += "|    ";
        }
      
        std::cout<< current->getData() <<std::endl;
      
        printHelper(current->left, indent, false);
        printHelper(current->right, indent, true);
      }
    }

  /*
  Función para imprimir todo el árbol de manera bonita.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(n)
  Complejidad de espacio: O(n)
  */
  void prettyPrint() {
    printHelper(root, "", true);
  }

};

int main() {
  setlocale(LC_ALL, "es_ES.UTF-8");
  SplayTree* splayTree = new SplayTree();
  std::vector<int> num = {5, 20, 32, 40, 12, 13, 8, 82, 1, 3, 80, 200, 157, 134, 6};
  std::vector<int> search = {20, 20, 12, 13, 12, 8, 2, 7, 157, 3};

  std::cout<<"Prueba de inserción de elementos y otras funciones del Splay Tree. "<<std::endl;
  for(int i = 0; i < num.size(); i++){
    splayTree->insert(num[i]);
    splayTree->prettyPrint();
    std::cout<<std::endl;
    
    if(i % 3 == 0){
      std::cout<<"El árbol contiene "<<splayTree->size()<<" elementos."<<std::endl<<std::endl;
      std::cout<<"Impresión de elementos ascendentemente."<<std::endl;
      splayTree->print();
      std::cout<<std::endl<<std::endl;
    }
  }
  
  std::cout<<"Prueba de búsqueda de elementos."<<std::endl;
  for(int i = 0; i < search.size(); i++){
    if(splayTree->find(search[i])){
      std::cout<<"Se encontró el dato "<<search[i]<<" en el árbol."<<std::endl;
    }
      
    else{
      std::cout<<"No se encontró el dato "<<search[i]<<" en el árbol."<<std::endl;
    }
    splayTree->prettyPrint();
    std::cout<<std::endl<<std::endl;
  }

  std::cout<<"Prueba de eliminación de elementos."<<std::endl;
  for(int i = 0; i < num.size(); i++){
    splayTree->del(num[i]);
    splayTree->prettyPrint();
    std::cout<<std::endl<<std::endl;
  }

  std::cout<<"Prueba de errores y casos especiales."<<std::endl;
  splayTree->del(10);
  splayTree->find(10);
  splayTree->insert(5);
  splayTree->insert(5);
  splayTree->del(5);
  std::cout<<"El árbol contiene "<<splayTree->size()<<" elementos."<<std::endl<<std::endl;

  std::cout<<"Probando la inserción de elementos después de borrar todos los elementos de un Splay Tree."<<std::endl;
  splayTree->insert(50);
  splayTree->insert(70);
  splayTree->insert(1);
  splayTree->insert(42);
  splayTree->insert(20);
  splayTree->insert(25);
  splayTree->insert(80);
  splayTree->insert(34);
  splayTree->prettyPrint();
  
  return 0;
}

