/*
Programa que realiza operaciones básicas de un Grafo, especialmente los recorridos búsqueda en 
anchura (Breadth First Search (BFS)) y búsqueda en profundidad (Depth First Search (DFS)), 
cumpliendo con las condiciones especiales de la estructura de datos.
Hecho por Juan Carlos Hernández Ríos, A01740821
Hecho el 08 de noviembre de 2022
*/

#include <iostream>
#include <list>
#include <map>
#include <vector>

/*
Base del Grafo. Contiene las estructuras de matriz de adyacencias y lista de
adyacencias y los dos tipos de recorridos.
*/
class Graph{
private:
  bool **adjMatrix;
  std::vector<std::vector<int>> adjList;
  int vertex;
  int edges;
  int counterEdges;

  /*
  Función para crear la base de la estructura de la matriz de adyacencias.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(V^2)
  Complejidad de espacio: O(V^2)
  */
  void loadMatrix() {
    adjMatrix = new bool *[vertex];

    for (int i = 0; i < vertex; i++) {
      adjMatrix[i] = new bool[vertex];

      for (int j = 0; j < vertex; j++) {
        adjMatrix[i][j] = false;
      }
    }
  }

  /*
  Función para crear la base de la estructura de la matriz de adyacencias.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(1)
  Complejidad de espacio: O(V)
  */
  void loadList() { 
    adjList.resize(vertex); 
  }

  /*
  Función para imprimir una matriz de adyacencias.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(V^2)
  Complejidad de espacio: O(1)
  */
  void printMatrix() {
    std::cout << "    ";

    for (int i = 0; i < vertex; i++) {
      std::cout << i << " ";
    }

    std::cout << std::endl;

    for (int i = 0; i < vertex; i++) {
      std::cout << i << " | ";

      for (int j = 0; j < vertex; j++) {
        std::cout << adjMatrix[i][j] << " ";
      }

      std::cout << std::endl;
    }

    std::cout << std::endl;
  }

  /*
  Función para imprimir una lista de adyacencias.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(V + E)
  Complejidad de espacio: O(1)
  */
  void printList() {
    for (int i = 0; i < adjList.size(); i++) {
      std::cout << i << " -> ";

      for (int j : adjList[i]) {
        std::cout << j << " ";
      }

      std::cout << std::endl;
    }
  }

public:

  /* Constructor de un grafo.
  Param: Nada.
  Return: Nada
  */
  Graph() {
    int vertex = 0;
    int edges = 0;
    int counterEdges = 0;
  }

  /* Función que brinda la estructura del grafo dependiendo del número de
  vertices y aristas, y realiza las conexiones pertinentes. 
  Param: (int n) número de vértices. (int m) número de aristas. 
  (map<int, pair<int, int>> links) Estructura donde se cargan las conexiones entre nodos a realizar.
  Return: Nada
  Complejidad de tiempo: O(V^2)
  Complejidad de espacio: O(V^2)
  */
  void loadGraph(int n, int m, std::map<int, std::pair<int, int>> links) {
    vertex = n;
    edges = m;
    loadList();
    loadMatrix();

    for (auto i : links) {
      addEdge(i.second.first, i.second.second);
    }
  }

  /*
  Función que realiza la conexión entre el nodo a al b en la matriz de
  adyacencia y lista de adyacencia. 
  Param: (int a) nodo inicial de la conexión. (int b) nodo final de la conexión. 
  Return: Nada. 
  Complejidad de tiempo: O(1)
  Complejidad de espacio: O(1)
  */
  void addEdge(int a, int b) {
    if (counterEdges < edges) {
      // añadir conexión a matriz de adyacencia.
      adjMatrix[a][b] = true;
      // añadir conexión a lista de adyacencia.
      adjList[a].push_back(b);
      counterEdges++;
    }

    else {
      std::cout << "Se llegó al máximo número de aristas." << std::endl;
      return;
    }
  }

  /*
  Función para imprimir las dos formas de estructuras de grafos.
  Param: Nada.
  Return: Nada.
  Complejidad de tiempo: O(V^2)
  Complejidad de espacio: O(1)
  */
  void print() {
    if(vertex != 0){
      std::cout << "Matriz de adyacencia:" << std::endl << std::endl;
      printMatrix();
      std::cout << "Lista de adyacencia:" << std::endl << std::endl;
      printList();
    }

    else{
      std::cout << "Grafo vacío" << std::endl;
    }

    std::cout << std::endl;
  }

  /*
  Función ayudante para realizar un recorrido Depth First Search (DFS) en una matriz de adyacencia. 
  Param: (int current) Nodo actual del recorrido por el grafo. 
  (vector<bool> &status) vector que anota cuáles nodos ya fueron procesados e impresos.
  Return: Nada. 
  Complejidad de tiempo: O(V^2) 
  Complejidad de espacio: O(V)
  */
  void recursiveDFS(int current, std::vector<bool> &status) {
    status[current] = true;
    std::cout << current << " ";

    for (int i = 0; i < sizeof(adjMatrix[current]); ++i) {
      
      if (adjMatrix[current][i] == true && (!status[i])) {
        recursiveDFS(i, status);
      }
    }
  }

  /*
  Función para realizar un recorrido Depth First Search (DFS) en una matriz de adyacencias. 
  Param: (int begin) Nodo en el que empieza el recorrido del grafo. 
  Return: Nada. 
  Complejidad de tiempo: O(V^2) 
  Complejidad de espacio: O(V)
  */
  void DFS(int begin) {
    if(vertex != 0){
      std::cout << "Búsqueda en profundidad (DFS): " << std::endl;
      std::vector<bool> status(vertex, false);
      recursiveDFS(begin, status);
    }

    else{
      std::cout << "Grafo vacío";
    }

    std::cout << std::endl << std::endl;
  }

  /*
  Función para realizar un recorrido Breadth First Search (BFS) en una lista de adyacencias. 
  Param: (int begin) Nodo en el que empieza el recorrido del grafo.  
  Return: Nada. 
  Complejidad de tiempo: O(V + E) 
  Complejidad de espacio: O(V)
  */
  void BFS(int begin) {
    if(vertex != 0){
      std::cout << "Búsqueda en anchura (BFS): " << std::endl;
      std::vector<bool> status(vertex, false);
      std::list<int> process;
      status[begin] = true;
      process.push_back(begin);
  
      while (!process.empty()) {
        int current = process.front();
        std::cout << current << " ";
        process.pop_front();
  
        for (auto i : adjList[current]) {
  
          if (!status[i]) {
            status[i] = true;
            process.push_back(i);
          }
        }
      }
    }

    else{
      std::cout << "Grafo vacío";
    }

    std::cout << std::endl << std::endl;
    
  }
};


int main() {

  Graph *graph1 = new Graph();
  Graph *graph2 = new Graph();
  Graph *graph3 = new Graph();
  Graph *graph4 = new Graph();
  Graph *graphTest = new Graph();
  std::cout << "----------Prueba 1. Grafo con estructura jerárquica----------" << std::endl;
  std::map<int, std::pair<int, int>> links = {{0, {0, 1}}, {1, {0, 7}}, {2, {0, 2}}, {3, {2, 5}}, {4, {2, 6}}, {5, {1, 3}}, {6, {1, 4}}};
  graph1->loadGraph(8, 7, links);
  graph1->print();
  graph1->DFS(0);
  graph1->BFS(0);
  
  std::cout << "----------Prueba 2. Grafo con estructura de telaraña----------" << std::endl;
  links = {{0, {0, 1}}, {1, {0, 2}}, {2, {0, 3}}, {3, {0, 4}}, {4, {0, 5}}, {5, {0, 6}}, {6, {1, 2}}, {7, {2, 3}}, {8, {3, 4}}, {9, {4, 5}}, {10, {5, 6}}, {11, {6, 1}}};
  graph2->loadGraph(7, 12, links);
  graph2->print();
  graph2->DFS(0);
  graph2->BFS(0);

  std::cout << "----------Prueba 3. Grafo sin ciclo----------" << std::endl;
  links = {{0, {0, 1}}, {1, {0, 7}}, {2, {1, 2}}, {3, {1, 5}}, {4, {2, 3}}, {5, {2, 4}}, {6, {3, 4}}, {7, {7, 3}}, {8, {2, 5}}, {9, {2, 6}}};
  graph3->loadGraph(8, 10, links);
  graph3->print();
  graph3->DFS(0);
  graph3->BFS(0);

  std::cout << "----------Prueba 4. Grafo con ciclo----------" << std::endl;
  links = {{0, {0, 4}}, {1, {4, 1}}, {2, {1, 0}}, {3, {4, 2}}, {4, {2, 3}}, {5, {0, 5}}, {6, {5, 3}}};
  graph4->loadGraph(6, 7, links);
  graph4->print();
  graph4->DFS(0);
  graph4->BFS(0);

  std::cout << "----------Prueba 5. Errores----------" << std::endl;
  graphTest->print();
  graphTest->DFS(0);
  graphTest->BFS(0);
  links = {{0, {0, 1}}, {1, {1, 0}}};
  graphTest->loadGraph(2, 1, links);

  return 0;
}