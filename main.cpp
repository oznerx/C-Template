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
    bool bipartiteGraph() { 

        // vector to store colour of vertex
        // assigning all to -1 i.e. uncoloured
        // colours are either 0 or 1
        // for understanding take 0 as red and 1 as blue
        std::vector<int> color(numVertex, -1);
    
        // queue for BFS storing {vertex , colour}
        std::queue<std::pair<int, int> > q;
    
        //loop incase graph is not connected
        for (int i = 0; i < numVertex; i++) {
        
            //if not coloured
            if (color[i] == -1) {
            
                //colouring with 0 i.e. red
                q.push({ i, 0 });
                color[i] = 0;
            
                while (!q.empty()) {
                    std::pair<int, int> p = q.front();
                    q.pop();
                
                    //current vertex
                    int v = p.first;
                    //colour of current vertex
                    int c = p.second;
                    
                    //traversing vertexes connected to current vertex
                    for (int j : adjList[v]) {
                    
                        //if already coloured with parent vertex color
                        //then bipartite graph is not possible
                        if (color[j] == c) {
                            return 0;
                        }
                    
                        //if uncoloured
                        if (color[j] == -1) {
                            //colouring with opposite color to that of parent
                            color[j] = (c) ? 0 : 1;
                            q.push({ j, color[j] });
                        }

                    }

                }

            }

        }

        //if all vertexes are coloured such that
        //no two connected vertex have same colours
        return 1;

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

    /*Diga si el Grafo Dirigido (DAG) es un árbol o no*/
    bool isTree() {
 
        clearVisited();

        for (int i = 0; i < numVertex; i++) {

            if (visited[i] == false) {
                _topologicalSort(i);
            }

        }

        std::cout << "size: " << stack.size() << "\n";
        return stack.size() == numVertex ? true : false;

    } 

};

int main()
{

    /*
    std::cout << "\n=================== Topological Sort ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}}; 
    g->loadGraph(6, 6, edges);
    g->print();
    g->topologicalSort();
    std::cout << "\n";
    */
    

    /*
    std::cout << "\n=================== Is Bipartite ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{0,1}, {0,3}, {1,0}, {1,2}, {2,1}, {2,3}, {3,0}, {3,2}}; 
    g->loadGraph(4, 8, edges);
    std::cout << g->bipartiteGraph() << "\n";
    g->print();
    g->bipartiteGraph() ? std::cout << "Yes" : std::cout << "No";
    */

    
    std::cout << "\n=================== Isn't Tree ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{0,1}, {1,2}, {2,0}}; 
    g->loadGraph(3, 3, edges);
    //std::cout << g->isTree() << "\n";
    g->print();
    g->isTree() ? std::cout << "Yes" : std::cout << "No";

    
    
    
    /*
    std::cout << "\n=================== Is Tree ===================\n";
    Graph *g = new Graph();
    std::vector <std::pair<int, int>> edges = {{0,1}, {0,2}, {1,3}, {1,4}, {4,5}, {4,6}, {2,7}, {7,8}}; 
    g->loadGraph(9, 8, edges);
    std::cout << g->isTree() << "\n";
    g->print();
    g->isTree() ? std::cout << "Yes" : std::cout << "No";
    */
    
    

}

/*
Referencias: 

    GeeksforGeeks. (2022). Topological Sorting. https://www.geeksforgeeks.org/topological-sorting.

    GeeksforGeeks. (2022). Check whether a given graph is Bipartite or not. https://www.geeksforgeeks.org/bipartite-graph.

*/