#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>



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
    std::map<int, std::vector<int>> adjList;
    std::stack<int> stack; 

    /*
    Carga una lista de adjacencia
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V)
    Complejidad de espacio: O(V) 
    */
    void loadList() {

        for (int i = 0; i < numVertex; i++) {
            std::vector<int> temp;
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

    /*Ordene en forma ascendente los datos con el método de Merge*/
    void _topologicalSort(int current) {

        visited[current] = true;

        for (auto i = adjList[current].begin(); i != adjList[current].end(); ++i) {

            if (!visited[*i]) {
                _topologicalSort(*i);
            }

        }

        stack.push(current);
    
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
    Imprime una idea general de la lista de adjacencia del grafo creado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(1) 
    */
    void print() {

        std::cout << "\nLa lista se creó con la siguiente estructura:\n";
        
        for (auto i : adjList) {

            std::cout << i.first << " : ";

            for (auto j : i.second) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

        std::cout << "\n";

    }

    /*bipartiteGraph*/
    bool _bipartiteGraph(int colorArr[]) {

        colorArr[0] = 1;
    
        // Create a queue (FIFO) of vertex numbers a
        // nd enqueue source vertex for BFS traversal
        std::queue<int> q;
        q.push(0);
    
        // Run while there are vertices in queue (Similar to
        // BFS)
        while (!q.empty()) {
            // Dequeue a vertex from queue ( Refer
            // http://goo.gl/35oz8 )
            int u = q.front();
            q.pop();
    
            // Return false if there is a self-loop
            if (adjList[u][u] == 1) {
                return false;
            }
    
            // Find all non-colored adjacent vertices
            for (int v = 0; v < numVertex; ++v) {
                // An edge from u to v exists and
                // destination v is not colored
                if (adjList[u][v] && colorArr[v] == -1) {
                    // Assign alternate color to this
                    // adjacent v of u
                    colorArr[v] = 1 - colorArr[u];
                    q.push(v);
                }
    
                // An edge from u to v exists and destination
                // v is colored with same color as u
                else if (adjList[u][v] && colorArr[v] == colorArr[u]) {
                    return false;
                }
            }
        }
    
        // If we reach here, then all adjacent vertices can
        // be colored with alternate color
        return true;
    }
    
    bool bipartiteGraph() { 
        // Create a color array to store colors assigned to all
        // vertices. Vertex/ number is used as index in this
        // array. The value '-1' of colorArr[i] is used to
        // indicate that no color is assigned to vertex 'i'.
        // The value 1 is used to indicate first color is
        // assigned and value 0 indicates second color is
        // assigned.
        int colorArr[numVertex];
        for (int i = 0; i < numVertex; ++i) {
            colorArr[i] = -1;
        }
    
        // This code is to handle disconnected graph
        for (int i = 0; i < numVertex; i++) {
            if (colorArr[i] == -1) {
                if (_bipartiteGraph(colorArr) == false) {
                    return false;
                }
            }
        }

    
        return true;
    }


    /*Diga si el Grafo Dirigido (DAG) es un árbol o no*/
    void isTree() {

    } 

    /*Ordene en forma ascendente los datos con el método de Merge*/
    void topologicalSort() {
 
        clearVisited();

        for (int i = 0; i < numVertex; i++) {

            if (visited[i] == false) {
                _topologicalSort(i);
            }

        }

        while (stack.empty() == false) {
            std::cout << stack.top() << " ";
            stack.pop();
        }

    }




};

int main()
{
/*
    std::cout << "\n=================== Primer Grafo ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges1 = {{0,1}, {0,3}, {1,2}, {2,5}, {3,1}, {3,5}, {3,4}, {4,5}}; 
    g->loadGraph(6, 8, edges1);
    g->print();
    std::cout << "Recorrido por DFS: ";
    g->DFS(0);
    g->topologicalSort();
*//*
    std::cout << "\n=================== Topological Sort ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}}; 
    g->loadGraph(6, 6, edges);
    g->topologicalSort();
    std::cout << "\n";*/

    std::cout << "\n=================== Is Bipartite ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{0,1}, {0,3}, {1,0}, {1,3}, {2,1}, {2,3}, {3,0}, {3,2}}; 
    g->loadGraph(4, 8, edges);
    std::cout << g->bipartiteGraph() << "\n";
    g->print();
    g->bipartiteGraph() ? std::cout << "Yes" : std::cout << "No";

}

/*
Referencias: 

    GeeksforGeeks. (2022). Topological Sorting. https://www.geeksforgeeks.org/topological-sorting.

*/