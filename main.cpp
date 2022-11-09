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
    int edgesCounter;

    /*
    Carga una matriz de adjacencia
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V^2)
    Complejidad de espacio: O(V^2) 
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
    Complejidad de tiempo: O(V)
    Complejidad de espacio: O(V) 
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
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
    */
    void addEdgeToMatrix(int a, int b) {
        adjMatrix[a][b] = true;
    }

    /*
    Agrega un arco entre 2 vértices de una lista de adjacencia
    @Param: (int a) vértice al cual se le va a agregar la conexión , (int b) vértice el cual será conectado
    Salida: nada
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
    */
    void addEdgeToList(int a, int b) {
        adjList[a].push_back(b); 
    }

    /*
    Imprime una idea general de la matriz de adjacencia del grafo creado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V^2)
    Complejidad de espacio: O(1) 
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
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(1) 
    */
    void printList() {

        for (auto i : adjList) {

            std::cout << i.first << " : ";

            for (auto j : i.second) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

    }

    /*
    Establece todos los nodos como a "no visitados"
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V)
    Complejidad de espacio: O(1) 
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
    Complejidad de tiempo: O(V^2)
    Complejidad de espacio: O(V^2) 
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
    Complejidad de tiempo: O(1)
    Complejidad de espacio: O(1) 
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
    Complejidad de tiempo: O(V^2)
    Complejidad de espacio: O(1) 
    */
    void print() {

        std::cout << "\nLa matriz se creó con la siguiente estructura:\n";
        printMatrix();
        std::cout << "\nLa lista se creó con la siguiente estructura:\n";
        printList();
        std::cout << "\n";

    }

    /*
    Imprime el Recorrido de DFS de una lista de adjacencia a partir de un nodo inicial
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
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
    Complejidad de tiempo: O(V^2)
    Complejidad de espacio: O(V) 
    */
    void _DFS(int a) {

        visited[a] = true;
        std::cout << a << " ";

        for (int i = 0; i < sizeof(adjMatrix[a]); ++i) {

            if (adjMatrix[a][i] == true && (!visited[i])) {
                _DFS(i);
            }

        }
           
    }

    /*
    Ayudante de del método _DFS
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V^2)
    Complejidad de espacio: O(V) 
    */
    void DFS(int a) {
        clearVisited();
        _DFS(a);
        std::cout << "\n";
    }

    /*
    Imprime el Recorrido de BFS de una lista de adjacencia a partir de un nodo inicial
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
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

        std::cout << "\n";

    }

};

int main()
{

    std::cout << "\n=================== Primer Grafo ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges1 = {{0,1}, {1,2}, {1,3}, {2,0}, {2,5}, {3,4}, {4,5}}; 
    g->loadGraph(6, 8, edges1);
    g->print();
    std::cout << "Recorrido por DFS: ";
    g->DFS(0);
    std::cout << "\nRecorrido por BFS: ";
    g->BFS(0);

    std::cout << "\n=================== Segundo Grafo ===================\n";
    Graph *g2 = new Graph();
    std::vector <std::pair<int, int>> edges2 = {{0,1}, {0,2}, {1,3}, {2,3}, {2,4}, {3,5}, {5,6}}; 
    g2->loadGraph(7, 7, edges2);
    g2->print();
    std::cout << "Recorrido por DFS: ";
    g2->DFS(0);
    std::cout << "\nRecorrido por BFS: ";
    g2->BFS(0);

    std::cout << "\n=================== Tercer Grafo ===================\n";
    Graph *g3 = new Graph();
    std::vector <std::pair<int, int>> edges3 = {{0,1}, {0,2}, {1,2}, {1,3}, {1,4}, {2,5}, {2,6}, {4,3}, {5,6}}; 
    g3->loadGraph(7, 9, edges3);
    g3->print();
    std::cout << "Recorrido por DFS: ";
    g3->DFS(0);
    std::cout << "\nRecorrido por BFS: ";
    g3->BFS(0);

    std::cout << "\n=================== Cuarto Grafo ===================\n";
    Graph *g4 = new Graph();
    std::vector <std::pair<int, int>> edges4 = {{0,1}, {0,3}, {3,4}, {4,5}, {4,2}}; 
    g4->loadGraph(6, 5, edges4);
    g4->print();
    std::cout << "Recorrido por DFS: ";
    g4->DFS(0);
    std::cout << "\nRecorrido por BFS: ";
    g4->BFS(0);

}

/*
Referencias: 

    GeeksforGeeks. (2022). Breadth First Search or BFS for a Graph. https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph.

    GeeksforGeeks. (2022). Depth First Search or DFS for a Graph. https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph.

*/