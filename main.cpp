/*
Programa que realiza operaciones complementarios de un Grafo, relacionados a grafos de arboles y bipartitos, cumpliendo con las condiciones especiales de la estructura de datos.
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 14 de noviembre de 2022
*/

#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <locale.h>

/*
Base del Grafo. Contiene las estructuras de matriz de adyacencias y lista de
adyacencias y los dos tipos de recorridos.
*/
class Graph{
  std::vector<std::vector<int>> adjList;
  int vertex;
  int edges;
  int counterEdges;
  public:

    /* Constructor de un grafo.
    Param: Nada.
    Return: Nada
    */
    Graph(){
      vertex = 0;
      edges = 0;
      counterEdges = 0;
    }
  
    /* Función que brinda la estructura del grafo dependiendo del número de
    vertices y aristas, y realiza las conexiones pertinentes. 
    Param: (int n) número de vértices. (int m) número de aristas. 
    (map<int, pair<int, int>> links) Estructura donde se cargan las conexiones entre nodos a realizar.
    Return: Nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V + E)
    */
    void loadGraph(int n, int m, std::map<int, std::pair<int, int>> links) {
      vertex = n;
      edges = m;
      adjList.resize(vertex); 
  
      for (auto i : links) {
        addEdge(i.second.first, i.second.second);
      }
    }
  
    /*
    Función que realiza la conexión entre el nodo x al nodo y en la matriz de
    adyacencia y lista de adyacencia. 
    Param: (int x) nodo inicial de la conexión. (int y) nodo final de la conexión. 
    Return: Nada. 
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1)
    */
    void addEdge(int x, int y) {
      if (counterEdges < edges && x < vertex && y < vertex) {
        // añadir conexión a lista de adyacencia.
        adjList[x].push_back(y);
        counterEdges++;
      }
  
      else if (counterEdges >= edges){
        std::cout << "Se llegó al máximo número de aristas." << std::endl;
        return;
      }

      else{
        std::cout << "Vértice no permitido." << std::endl;
        return;
      }
    }


    /*
    Función ayudante de isTree, que revisa si hay un ciclo en el grafo.
    Param: (int current) Nodo actual del recorrido del grafo. 
    (vector<bool> &visited) Vector donde se checa si un nodo fue visitado o no.
    (int parent) Padre del nodo actual.
    Return: bool Hay un ciclo en el grafo o no.
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V)
    */
    bool isCyclicUtil(int current, std::vector<bool> &visited, int parent) {
      visited[current] = true;
      std::vector<int>::iterator i;
      for (i = adjList[current].begin(); i != adjList[current].end(); ++i){
        
        if (!visited[*i]){
          
          if (isCyclicUtil(*i, visited, current)){
            return true;
          }
        }
          
        else if (*i != parent){
          return true;
        }
      }
      return false;
    }


    /* Función que realiza el orden topológico de un DAG.
    Param: Nada.
    Return: Nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V)
    */
    void topologicalSort(){
      if(vertex != 0){
        std::vector<int> inDegree(vertex, 0);
        for (int u = 0; u < vertex; u++) {
          std::vector<int>::iterator itr;
          for (itr = adjList[u].begin(); itr != adjList[u].end(); itr++){
            inDegree[*itr]++;
          }
        }
     
        std::queue<int> queue;
        for (int i = 0; i < vertex; i++){
          if (inDegree[i] == 0){
            queue.push(i);
          }
        }
            
        int counter = 0;
        std::vector<int> topOrder;
    
        while (!queue.empty()) {
          int current = queue.front();
          queue.pop();
          topOrder.push_back(current);
          std::vector<int>::iterator itr;
          for (itr = adjList[current].begin(); itr != adjList[current].end(); itr++){
    
            if (--inDegree[*itr] == 0){
              queue.push(*itr);
            }
          }
    
          counter++;
        }
     
        if (counter != vertex) {
          std::cout << "Hay un ciclo en el grafo." << std::endl << std::endl;
          return;
        }
    
        for (int i = 0; i < topOrder.size(); i++){
          std::cout << topOrder[i] << " ";
        }
            
        std::cout << std::endl << std::endl;
      }

      else{
        std::cout << "Grafo vacío" << std::endl << std::endl;
      }
      
    }

    /*
    Función que revisa si un DAG es un árbol.
    Param: (int begin) Nodo donde se inicia el recorrido del DAG para comprobar si es un árbol.
    Return: bool DAG es un árbol o no.
    Complejidad de tiempo: O(V + E)
    Complejidad de tiempo: O(V)
    */
    bool isTree(int begin){
      if(vertex != 0){
        std::vector<bool> visited(vertex, false);
   
        if (isCyclicUtil(begin, visited, begin - 1)){
          return false;
        }
                 
        for (int i = 0; i < visited.size(); i++){
          if (!visited[i]){
            return false;
          } 
        }
      
      return true;
      }

      else{
        std::cout << "Grafo vacío" << std::endl << std::endl;
        return false;
      }
      
    }

    /* Función que checa si un DAG es un grafo Bipartito.
    Param: Nada.
    Return: bool DAG es un grafo Bipartito o no.
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V)
    */
    bool isBipartite() {
      if(vertex != 0){
        std::vector<int> color(vertex, -1);
        std::queue<std::pair<int, int> > queue;
    
        for (int i = 0; i < vertex; i++) {
    
          if (color[i] == -1) {
            queue.push({ i, 0 });
            color[i] = 0;
            
            while (!queue.empty()) {
              std::pair<int, int> p = queue.front();
              queue.pop();
              int current = p.first;
              int currentColor = p.second;
              
              for (int j : adjList[current]) {
                
                if (color[j] == currentColor){
                  return false;
                }
                
                if (color[j] == -1) {
                  
                  if(currentColor){
                    color[j] = 0;
                  }
                    
                  else{
                    color[j] = 1;
                  }
                  queue.push({j,color[j]});
                }
              }
            }
          }
        }
        
        return true;
      }

      else{
        std::cout << "Grafo vacío" << std::endl << std::endl;
        return false;
      }
      
    }
  
    /*
    Función para imprimir una lista de adyacencias.
    Param: Nada.
    Return: Nada.
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(1)
    */
    void printList() {
      if(vertex != 0){
        std::cout << "Lista de adyacencia:" << std::endl << std::endl;
        for (int i = 0; i < adjList.size(); i++) {
          std::cout << i << " -> ";
    
          for (int j = 0; j < adjList[i].size(); j++) {
            std::cout << adjList[i][j] << " ";
          }
    
          std::cout << std::endl;
        }
      }
  
      else {
        std::cout << "Grafo vacío" << std::endl;
      }
    std::cout << std::endl;
    }

};

int main(){
  setlocale(LC_ALL, "es_ES.UTF-8");
  Graph *graph1 = new Graph();
  Graph *graph2 = new Graph();
  Graph *graph3 = new Graph();
  Graph *graph4 = new Graph();
  Graph *graphTest = new Graph();
  Graph *graphTest2 = new Graph();

  std::cout << "----------Prueba 1. Grafo con estructura jerárquica----------" << std::endl;
  std::map<int, std::pair<int, int>> links = {{0, {0, 2}}, {1, {0, 1}}, {2, {2, 5}}, {3, {1, 3}}, {4, {1, 4}}, {5, {1, 6}}, {6, {4, 7}}};
  graph1->loadGraph(8, 7, links);
  graph1->printList();
  graph1->topologicalSort();
  if(graph1->isTree(0)){
    std::cout << "El grafo es un árbol" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un árbol" << std::endl << std::endl;;
  }

  if(graph1->isBipartite()){
    std::cout << "El grafo es un grafo bipartito" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un grafo bipartito" << std::endl << std::endl;;
  }
  
  
  std::cout << "----------Prueba 2. Grafo bipartito----------" << std::endl;
  links = {{0, {0, 2}}, {1, {3, 1}}, {2, {3, 4}}, {3, {4, 0}}, {4, {2, 3}}};
  graph2->loadGraph(5, 5, links);
  graph2->printList();
  graph2->topologicalSort();
  if(graph2->isTree(0)){
    std::cout << "El grafo es un árbol" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un árbol" << std::endl << std::endl;;
  }

  if(graph2->isBipartite()){
    std::cout << "El grafo es un grafo bipartito" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un grafo bipartito" << std::endl << std::endl;;
  }

  std::cout << "----------Prueba 3. Grafo con ciclo----------" << std::endl;
  links = {{0, {0, 1}}, {1, {1, 2}}, {2, {2, 3}}, {3, {3, 4}}, {4, {4, 0}}};
  graph3->loadGraph(5, 5, links);
  graph3->printList();
  graph3->topologicalSort();
  if(graph3->isTree(0)){
    std::cout << "El grafo es un árbol" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un árbol" << std::endl << std::endl;;
  }

  if(graph3->isBipartite()){
    std::cout << "El grafo es un grafo bipartito" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un grafo bipartito" << std::endl << std::endl;;
  }
  

  std::cout << "----------Prueba 4. Grafo sin ciclo----------" << std::endl;
  links = {{0, {0, 2}}, {1, {0, 5}}, {2, {0, 6}}, {3, {2, 1}}, {4, {1, 5}}, {5, {1, 3}}, {6, {3, 4}}, {7, {6, 4}}, {8, {6, 5}}};
  graph4->loadGraph(7, 9, links);
  graph4->printList();
  graph4->topologicalSort();
  if(graph4->isTree(0)){
    std::cout << "El grafo es un árbol" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un árbol" << std::endl << std::endl;;
  }

  if(graph4->isBipartite()){
    std::cout << "El grafo es un grafo bipartito" << std::endl << std::endl;;
  }

  else{
    std::cout << "El grafo no es un grafo bipartito" << std::endl << std::endl;;
  }

  std::cout << "----------Prueba 5. Errores----------" << std::endl;
  graphTest->printList();
  graphTest->isTree(0);
  graphTest->isBipartite();
  links = {{0, {0, 1}}, {1, {0, 2}}, {2, {0, 1}}};
  graphTest->loadGraph(2, 2, links);
  links = {{0, {0, 1}}, {1, {1, 0}}};
  graphTest2->loadGraph(2, 1, links);
  
  return 0;
}