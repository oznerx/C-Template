#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

/*
Ozner Axel Leyva Mariscal
A01742377
9 de Noviembre del 2022
En este código se implementará un grafo direccionado asi como algunas de sus funcionalidades como el recorrido por DFS y BFS. 
*/

class Graph {
private:

    bool** adjMatrix;
    std::map<int, std::list<int> > adjList;
    int numVertex;
    int numEdges;
    int currentEdges;
    std::map<int, bool> visited;

    /*
    Carga una matriz de adjacencia
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void loadMatrix() {

        adjMatrix = new bool*[numVertex];
        
        for (int i = 0; i < numVertex; i++) {
            adjMatrix[i] = new bool[numVertex];

            for (int j = 0; j < numVertex; j++) {
                adjMatrix[i][j] = false;
            }

        }

    }

    /*
    Carga una lista de adjacencia
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void loadList() {

        for (int i = 0; i < numVertex; i++) {
            std::list<int> temp;
            adjList.emplace(i, temp);
        }

    } 

    /*
    Agrega un arco entre 2 vértices de una matriz de adjacencia 
    @Param: (int a) vértice al cual se le va a agregar la conexión , (int b) vértice el cual será conectado
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void addEdgeToMatrix(int a, int b) {
        adjMatrix[a][b] = true;
        adjMatrix[b][a] = true;
    }

    /*
    Agrega un arco entre 2 vértices de una lista de adjacencia
    @Param: (int a) vértice al cual se le va a agregar la conexión , (int b) vértice el cual será conectado
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void addEdgeToList(int a, int b) {
        adjList[a].push_back(b); 
    }

    /*
    Imprime una idea general de la matriz de adjacencia del grafo creado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void printMatrix() {
            
        for (int i = 0; i < numVertex; i++) {

            std::cout << i << " : ";

            for (int j = 0; j < numVertex; j++) {
                std::cout << adjMatrix[i][j] << " " ;
            }

            std::cout << "\n";

        }

    }

    /*
    Imprime una idea general de la lista de adjacencia del grafo creado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void printList() {

        std::map<int, std::list<int>>::iterator i;

        for (i=adjList.begin(); i!=adjList.end(); i++) {

            std::cout << i->first << " : ";

            for (auto j : i->second) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

    }

    /*
    Establece todos los nodos como a "no visitados"
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void clearVisited() {

        for (int i = 0; i < visited.size() ;i++) {
            visited[i] = false;
        }

    }
    
public:

    /* Constructor de la clase de grafo */
    Graph() {
        int numVertex = 0;
        int numEdges = 0;
        int currentEdges = 0;
    }

    /*
    Carga los arcos del grafo, los almacena en una Matriz de Adjacencia y en una Lista de Adjacencia
    @Param:(int n) Cantidad de Vertices, (int m) Cantidad de Arcos
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void loadGraph(int n, int m, std::vector <std::pair<int, int>> edges) {

        this->numVertex = n;
        this->numEdges = m;
        loadList();
        loadMatrix();

        for (int i = 0; i < edges.size() ; i++) {
            addEdge(edges[i].first, edges[i].second);
        }

    }

    /*
    Agrega un arco entre 2 vertices
    @Param: (int a) vertice al cual se le va a agregar la conexión , (int b) vertice el cual será conectado
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void addEdge(int a, int b) {

        if (currentEdges < numEdges) {
            currentEdges++;
            addEdgeToMatrix(a, b);
            addEdgeToList(a, b);
        }

        else {
            std::cout << "Numero de conexiones máximo alcanzado\n";
            return;
        }
        
    }

    /*
    Imprime una idea general de la estrcutura del grafo creado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void print() {

        std::cout << "\nLa matriz se creó con la siguiente estructura:\n";
        printMatrix();
        std::cout << "\nLa lista se creó con la siguiente estructura:\n";
        printList();

    }

    /*
    Imprime el Recorrido de DFS de una lista de adjacencia a partir de un nodo inicial
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void listDFS(int a) {

        visited[a] = true;
        std::cout << a << " ";
    
        std::list<int>::iterator i;
        for (i = adjList[a].begin(); i != adjList[a].end(); ++i) {

            if (!visited[*i]) {
                listDFS(*i);
            }
                
        }
            
    }

    /*
    Imprime el Recorrido de DFS de una matriz de adjacencia a partir de un nodo inicial
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void _DFS(int a) {

        visited[a] = true;
        std::cout << a << " ";

        for (int i = a; i < sizeof(adjMatrix[a]); ++i) {

            if (adjMatrix[a][i] == true && (!visited[i])) {
                _DFS(i);
            }

        }
            
    }

    /*
    Ayudante de del método _DFS
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void DFS(int a) {
        clearVisited();
        _DFS(a);
    }

    /*
    Imprime el Recorrido de BFS de una lista de adjacencia a partir de un nodo inicial
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O()
    Complejidad de espacio: O() 
    */
    void BFS(int a) {

        clearVisited();
        std::list<int> queue;
        visited[a] = true;
        queue.push_back(a);
    
        while (!queue.empty()) {

            a = queue.front();
            std::cout << a << " ";
            queue.pop_front();
    
            for (auto i: adjList[a]) {

                if (!visited[i]) {
                    visited[i] = true;
                    queue.push_back(i);
                }

            }

        }

    }

};

int main()
{

    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{0,1}, {0,3}, {1,2}, {2,5}, {3,1}, {3,5}, {3,4}, {4,5}}; 
    g->loadGraph(6, 8, edges);
    g->print();
    std::cout << "\n";
    g->DFS(0);
    std::cout << "\n";
    g->BFS(0);
    std::cout << "\n";

    /*
    //Goes like: 012354
    Graph *g = new Graph();
    g->loadGraph(6, 7);

    g->addEdge(0, 1);

    g->addEdge(1, 2);
    g->addEdge(1, 3);

    g->addEdge(2, 0);
    g->addEdge(2, 5);

    g->addEdge(3, 4);
    
    g->addEdge(4, 5);

    g->print();
    std::cout << "\n";
    g->DFS(0);
    std::cout << "\n";
    g->BFS(0);
    std::cout << "\n";
    */
    
    /*
    //Goes like: 0 9 7 11 10 8 6 3 1 12 5 2 4 
    Graph *g = new Graph();
    g->loadGraph(13, 15);

    g->addEdge(0, 9);
    g->addEdge(0, 7);
    g->addEdge(0, 11);

    g->addEdge(3, 2);
    g->addEdge(3, 4);

    g->addEdge(6, 5);

    g->addEdge(7, 3);
    g->addEdge(7, 6);
    g->addEdge(7, 11);


    g->addEdge(8, 12);
    g->addEdge(8, 1);

    g->addEdge(9, 8);
    g->addEdge(9, 10);

    g->addEdge(10, 1);

    g->addEdge(12, 2);


    g->print();
    g->BFS(0);
    */
    
}

/*
Referencias: 

    GeeksforGeeks. (2022). Breadth First Search or BFS for a Graph. https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph

*/
