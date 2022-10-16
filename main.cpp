/*
Programa que realiza operaciones básicas (insertar y borrar) de un
Binary Search Tree y operaciones avanzadas, cumpliendo con las 
condiciones especiales de la estructura de datos
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 15 de octubre de 2022
*/

#include <iostream>
#include <queue>
#include <vector>
#include <locale.h>

/*
Entidad básica de las estructuras de datos. Es especial para los 
árboles, debido a que están conectadas a nodos hijos 
izquierdo y derecho. Puede contener solamente enteros.
*/
class Node{
  int data;
  public:
    Node* right;
    Node* left;

    /* Constructor de un nodo. Los nodos hijos son nulos.
    Param: Nada.
    Return: Nada.
    */
    Node(){
      right = nullptr;
      left = nullptr;
    }

    /* Destructor de un nodo.
    Param: Nada.
    Return: Nada.
    */
    ~Node(){
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


    /* Regresa el dato del nodo.
    Param: Nada.
    Return: int dato del nodo.
    */
    int getData(){
      return data;
    }
};

/*
Base del Binary Search Tree. Contiene las operaciones fundamentales
de un BST.
*/
class BST{
  Node* root;
  int h;

  /*
  Función recursiva ayudante de la inserción de datos en un BST.
  Param: (Node* current) Nodo actual del recorrido por el árbol. 
  (int data) información del nodo a insertar.
  Return: Node* Nodo regresado por el árbol para recorrer la estructura del BST.
  Caso promedio: Complejidad de tiempo O(logn)
  Peor caso: Complejidad de tiempo O(n)
  Complejidad de espacio: O(logn)
  */
  Node* insertRecursive(Node *current, int data){
      if(current == nullptr){
        current = new Node();
        current->setData(data);
      }

      else if(data > current->getData()){
        current->right = insertRecursive(current->right, data);
      }

      else if(data < current->getData()){
        current->left = insertRecursive(current->left, data);
      }

      else{
        std::cout<<"Elemento repetido. Inserte otro número"<<std::endl;
      }
      
      return current;
    }

  /* 
  Función que imprime los datos de los nodos en pre orden.
  Param: (Node* current) Nodo actual del recorrido por el árbol.
  Return: Nada.
  Complejidad de tiempo: O(n) 
  Complejidad de espacio: O(n)
  */
  void preOrder(Node* current){
    if(current != nullptr && root != nullptr){
      std::cout<< current->getData() << " ";
      preOrder(current->left);
      preOrder(current->right);
    }

    else if(root == nullptr){
      std::cout<<"Árbol vacio.";
    }
  }

  /* 
  Función que imprime los datos de los nodos en orden.
  Param: (Node* current) Nodo actual del recorrido por el árbol.
  Return: Nada.
  Complejidad de tiempo: O(n) 
  Complejidad de espacio: O(n)
  */
  void inOrder(Node* current){
    if(current != nullptr && root != nullptr){
      inOrder(current->left);
      std::cout<< current->getData() << " ";
      inOrder(current->right);
    }
      
    else if(root == nullptr){
      std::cout<<"Árbol vacio.";
    }
  }

  /* 
  Función que imprime los datos de los nodos en pos orden.
  Param: (Node* current) Nodo actual del recorrido por el árbol.
  Return: Nada.
  Complejidad de tiempo: O(n) 
  Complejidad de espacio: O(n)
  */
  void postOrder(Node* current){
    if(current != nullptr && root != nullptr){
      postOrder(current->left);
      postOrder(current->right);
      std::cout<< current->getData() << " ";
    }
      
    else if(root == nullptr){
      std::cout<<"Árbol vacio.";
    }
  }

  /* 
  Función que imprime los datos de los nodos por cada nivel del árbol.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(n) 
  Complejidad de espacio: O(n)
  */
  void levelByLevel(){
    if(root != nullptr){
      std::queue<Node*> q;
      Node* tmp = nullptr;
      q.push(root);

      while(q.empty() == false){
        tmp = q.front();
        std::cout<<tmp->getData()<<" ";
        q.pop();

        if(tmp->left != nullptr){
          q.push(tmp->left);
        }

        if(tmp->right != nullptr){
          q.push(tmp->right);
        }
      }
    }

    if(root == nullptr){
      std::cout<<"Árbol vacio.";
    }
  }

  /* 
  Función que obtiene el valor de la altura del árbol.
  Param: (Node* current) Nodo actual del recorrido por el árbol.
  Return: int Altura del árbol.
  Complejidad de tiempo: O(n)
  Complejidad de espacio: O(n)
  */
  int treeHeight(Node* current){
    if(root != nullptr){

      if(current == nullptr){
        return -1;
      }
      
      int leftHeight = treeHeight(current->left);
      int rightHeight = treeHeight(current->right);
      return std::max(leftHeight, rightHeight) + 1;
    }
    
    std::cout<<"Árbol vacio.\n"<<std::endl;
    return -1;
  }

  /* 
  Función que imprime los ancestros de un nodo.
  Param: (Node* current) Nodo actual del recorrido por el árbol.
  (int data) valor del nodo desde el cual se imprime sus ancestros.
  Return: bool bandera que revisa si se encontró el nodo desde el cual 
  se imprimiran sus ancestros.
  Complejidad de tiempo: O(n)
  Complejidad de espacio: O(H), H siendo la altura del árbol
  */
  bool printAncestors(Node* current, int data){
    if(root != nullptr){

      if(current == nullptr){
        return false;
      }

      if(current->getData() == data){
        return true;
      }

      else if(printAncestors(current->left, data) || printAncestors(current->right, data)){
        std::cout<<current->getData()<<" ";
        return true;
      }

      else{
        return false;
      }
    }
    
    std::cout<<"Árbol vacio."<<std::endl;
    return false;
  }

  /* 
  Función que obtiene el nivel del nodo buscado.
  Param: (Node* current) Nodo actual del recorrido por el árbol.
  (int data) valor del nodo buscado. (int level) nivel actual del árbol.
  Return: nivel del nodo buscado.
  Complejidad de tiempo: O(n)
  Complejidad de espacio: O(H), H siendo la altura del árbol
  */
  int getLevel(Node* current, int data, int level){
      if(current == nullptr){
        return -1;
      }
    
      else if(current->getData() == data){
        return level;
      }

      int downLevel = getLevel(current->left, data, level + 1);

      if (downLevel != -1){
        return downLevel;
      }
      
      downLevel = getLevel(current->right, data, level + 1);
      return downLevel;
  }

  public:

    /*
    Constructor del Binary Search Tree.
    */
    BST(){
      root = nullptr;
    }

    /*
    Función principal para insertar nodos en el árbol.
    Param: (int data) dato del nodo a insertar.
    Return: Nada.
    Caso promedio: Complejidad de tiempo O(logn)
    Peor caso: Complejidad de tiempo O(n)
    Complejidad de espacio: O(logn)
    */
    void insert(int data){
      root = insertRecursive(root, data);
    }

    /*
    Función principal para desplegar datos del árbol dependiendo
    del dato de entrada.
    Param: (int method) Método a usar para desplegar datos.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    void visit(int method){
      switch(method){
        case 1: 
          std::cout<<"Lectura pre orden"<<std::endl;
          preOrder(root);
          std::cout<<"\n"<<std::endl;
          break;
        case 2: 
          std::cout<<"Lectura en orden"<<std::endl;
          inOrder(root);
          std::cout<<"\n"<<std::endl;
          break;
        case 3: 
          std::cout<<"Lectura pos orden"<<std::endl;
          postOrder(root);
          std::cout<<"\n"<<std::endl;
          break;
        case 4: 
          std::cout<<"Lectura por nivel"<<std::endl;
          levelByLevel();
          std::cout<<"\n"<<std::endl;
          break;
        default: 
          std::cout<<"Comando equivocado."<<std::endl<<std::endl;
          break;
      }
    }

    /*
    Función principal para encontrar la altura del árbol.
    Param: Nada.
    Return: int Valor de la altura del árbol.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(n)
    */
    int height(){
      return treeHeight(root);
    }

    /*
    Función principal para desplegar los ancestros de un nodo específico.
    Param: (int data) dato del nodo buscado.
    Return: Nada.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(H), H siendo la altura del árbol
    */
    void ancestors(int data){
      bool flag;
      std::cout<<"Los ancestros del dato "<<data<<" son:"<<std::endl;
      flag = printAncestors(root, data);
      if(flag == false){
        std::cout<<"El nodo no se encuentra en el árbol";
      }
      std::cout<<std::endl<<std::endl;
    }

    /*
    Función principal para desplegar el nivel del nodo buscado.
    Param: (int data) dato del nodo buscado.
    Return: int Valor del nivel del nodo.
    Complejidad de tiempo: O(n)
    Complejidad de espacio: O(H), H siendo la altura del árbol
    */
    int whatlevelamI(int data){
      return getLevel(root, data, 0);
    }
  
};

int main() {
  setlocale(LC_ALL, "es_ES.UTF-8");
  std::vector<int> num = {710, 689, 2000, 143, 702, 1040, 2099, 70, 250, 1500, 3300, 178, 2504};
  BST* tree = new BST();
  BST* treeTwo = new BST();
  int data;
  
  std::cout<<"Inserción de datos en el BST\n"<<std::endl;
  for(int i = 0; i < num.size(); i++){
    tree->insert(num[i]);
  }

  std::cout<<"Despliegue de datos en el BST\n"<<std::endl;
  tree->visit(1);
  tree->visit(2);
  tree->visit(3);
  tree->visit(4);

  std::cout<<"Prueba de la función altura\n"<<std::endl;
  std::cout<<"El árbol tiene una altura de "<<tree->height()<<std::endl<<std::endl;

  std::cout<<"Prueba de la función ancestros\n"<<std::endl;
  tree->ancestors(178);

  std::cout<<"Prueba de la función en cuál nivel se encuentra un nodo\n"<<std::endl;
  data = 70;
  std::cout<<"El dato "<<data<<" está en el nivel "<<tree->whatlevelamI(data)<<std::endl<<std::endl;

  data = 100;
  std::cout<<"El dato "<<data<<" está en el nivel "<<tree->whatlevelamI(data)<<std::endl<<std::endl;


  std::cout<<"Prueba de errores\n"<<std::endl;
  treeTwo->visit(1);
  treeTwo->visit(2);
  treeTwo->visit(3);
  treeTwo->visit(4);
  treeTwo->visit(5);
  treeTwo->height();
  treeTwo->ancestors(710);
  data = 70;
  std::cout<<"El dato "<<data<<" está en el nivel "<<treeTwo->whatlevelamI(data)<<std::endl;
  
  return 0;
}