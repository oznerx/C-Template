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

    int numVertex;
    int numEdges;
    int currentEdges;
    std::map<int, bool> visited;
    std::map<int, std::list<int>> adjList;

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
    Imprime el Recorrido de DFS de una lista de adjacencia a partir de un nodo inicial
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void _DFS(int a) {

        visited[a] = true;
        std::cout << a << " ";
    
        std::list<int>::iterator i;
        for (i = adjList[a].begin(); i != adjList[a].end(); ++i) {

            if (!visited[*i]) {
                _DFS(*i);
            }
                
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
    Complejidad de espacio: O(V) 
    */
    void loadGraph(int n, int m, std::vector <std::pair<int, int>> edges) {

        this->numVertex = n;
        this->numEdges = m;
        loadList();

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
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(1) 
    */
    void print() {
        std::cout << "\nLa lista se creó con la siguiente estructura:\n";
        printList();
        std::cout << "\n";
    }

    /*
    Ayudante de del método _DFS
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void DFS(int a) {
        _DFS(a);
        std::cout << "\n";
    }

};

int main()
{

    std::cout << "\n=================== Primer Grafo ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges1 = {{0,1}, {0,3}, {1,2}, {2,5}, {3,1}, {3,5}, {3,4}, {4,5}}; 
    g->loadGraph(6, 8, edges1);
    g->print();
    std::cout << "Recorrido por DFS: ";
    g->DFS(0);

}

/*
Referencias: 

    GeeksforGeeks. (2022). Depth First Search or DFS for a Graph. https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph.

*/