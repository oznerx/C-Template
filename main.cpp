#include <iostream>
#include <fstream>
#include <unordered_set>
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

    /*
    Ordena en forma ascendente los datos con el método de Merge    
    @Param: (int current) nodo actual en el que se encuentra
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void _topologicalSort(int current) {

        visited[current] = true;

        for (auto i = adjList[current].begin(); i != adjList[current].end(); ++i) {

            if (!visited[*i]) {
                _topologicalSort(*i);
            }

        }

        stack.push(current);
    
    }

    /*
    Imprime el Recorrido de DFS de una lista de adjacencia a partir de un nodo inicial
    @Param: (int a) nodo inicial
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void _DFS(int a) {

        visited[a] = true;
    
        std::vector<int>::iterator i;
        for (i = adjList[a].begin(); i != adjList[a].end(); ++i) {

            if (!visited[*i]) {
                _DFS(*i);
            }
                
        }
            
    }

    /*
    Verifica que el grafo esté conectado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V)
    */
    bool isConnected() {
        
        clearVisited();
    
        _DFS(0);    

        for (int i = 0; i < numVertex; i++) {
            
            if (!visited[i]) {
                return false;
            }

        }

        return true;

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

        std::cout << "\nLa lista de adyacencia se creó con la siguiente estructura:\n\n";
        
        for (auto i : adjList) {

            std::cout << i.first << " : ";

            for (auto j : i.second) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

        std::cout << "\n";

    }

    /*
    Verifica que el Grafo Dirigido (DAG) puede ser representado como Grafo bipartita.    
    @Param: (int current) nodo actual en el que se encuentra
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
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

    /*
    Ordena en forma ascendente los datos con el método de Merge    
    @Param: (int current) nodo actual en el que se encuentra
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
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


    /*
    Verifica que el Grafo Dirigido (DAG) es un árbol
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    bool isTree() {
        return isConnected() && numEdges == numVertex - 1;
    } 

    /*
    Verifica que el Grafo Dirigido (DAG) es un árbol utilizando ordenación topológica
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    bool topologicalSortCheck() {
        // Create a vector to store
        // indegrees of all
        // vertices. Initialize all
        // indegrees as 0.
        std::vector<int> in_degree(numVertex, 0);
    
        // Traverse adjacency lists
        // to fill indegrees of
        // vertices.  This step
        // takes O(V+E) time
        for (int u = 0; u < numVertex; u++) {
            std::vector<int>::iterator itr;
            for (itr = adjList[u].begin();itr != adjList[u].end(); itr++) {
                in_degree[*itr]++;
            }
        }
    
        // Create an queue and enqueue
        // all vertices with indegree 0
        std::queue<int> q;
        for (int i = 0; i < numVertex; i++) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

    
        // Initialize count of visited vertices
        int cnt = 0;
    
        // Create a vector to store
        // result (A topological
        // ordering of the vertices)
        std::vector<int> top_order;
    
        // One by one dequeue vertices
        // from queue and enqueue
        // adjacents if indegree of
        // adjacent becomes 0
        while (!q.empty()) {
            // Extract front of queue
            // (or perform dequeue)
            // and add it to topological order
            int u = q.front();
            q.pop();
            top_order.push_back(u);
    
            // Iterate through all its
            // neighbouring nodes
            // of dequeued node u and
            // decrease their in-degree
            // by 1
            std::vector<int>::iterator itr;
            for (itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {
                // If in-degree becomes zero,
                // add it to queue
                if (--in_degree[*itr] == 0) {
                    q.push(*itr);
                }
            }

            cnt++;

        }

        // Check if there was a cycle
        if (cnt != numVertex) {
            std::cout << "There exists a cycle in the graph\n";
            return false;
        }

        return true;
    
    }


};

int main()
{

    std::cout << "\n======================== Primer Grafo ========================\n";
    Graph *g1 = new Graph(); // Topological sort
    std::vector <std::pair<int, int>> edges1 = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}}; 
    g1->loadGraph(6, 6, edges1);
    g1->print();
    g1->isTree() ? std::cout << "El grafo es un árbol\n\n" : std::cout << "El grafo no es un árbol\n\n";
    std::cout << "El ordenamiento topologico del grafo es: ";
    g1->topologicalSort();
    g1->bipartiteGraph() ? std::cout << "\n\nEl grafo es bipartita\n" : std::cout << "\n\nEl grafo no es bipartita\n";
    std::cout << "\n";
    
    std::cout << "\n======================== Segundo Grafo ========================\n";
    Graph *g2 = new Graph(); // is bipartite
    std::vector <std::pair<int, int>> edges2 = {{0,1}, {0,3}, {1,0}, {1,2}, {2,1}, {2,3}, {3,0}, {3,2}}; 
    g2->loadGraph(4, 8, edges2);
    g2->print();
    g2->isTree() ? std::cout << "El grafo es un árbol\n\n" : std::cout << "El grafo no es un árbol\n\n";
    std::cout << "El ordenamiento topologico del grafo es: ";
    g2->topologicalSort();
    g2->bipartiteGraph() ? std::cout << "\n\nEl grafo es bipartita\n" : std::cout << "\n\nEl grafo no es bipartita\n";
    std::cout << "\n";

    std::cout << "\n======================== Tercer Grafo ========================\n";
    Graph *g3 = new Graph(); // isnt a tree
    std::vector <std::pair<int, int>> edges3 = {{0,1}, {1,2}, {2,0}}; 
    g3->loadGraph(3, 3, edges3);
    g3->print();
    g3->isTree() ? std::cout << "El grafo es un árbol\n\n" : std::cout << "El grafo no es un árbol\n\n";
    std::cout << "El ordenamiento topologico del grafo es: ";
    g3->topologicalSort();
    g3->bipartiteGraph() ? std::cout << "\n\nEl grafo es bipartita\n" : std::cout << "\n\nEl grafo no es bipartita\n";
    std::cout << "\n";
    
    std::cout << "\n======================== Cuarto Grafo ========================\n";
    Graph *g4 = new Graph(); // is a tree
    std::vector <std::pair<int, int>> edges4 = {{0,1}, {0,2}, {1,3}, {1,4}, {4,5}, {4,6}, {2,7}, {7,8}}; 
    g4->loadGraph(9, 8, edges4);
    g4->print();
    g4->isTree() ? std::cout << "El grafo es un árbol\n\n" : std::cout << "El grafo no es un árbol\n\n";
    std::cout << "El ordenamiento topologico del grafo es: ";
    g4->topologicalSort();
    g4->bipartiteGraph() ? std::cout << "\n\nEl grafo es bipartita\n" : std::cout << "\n\nEl grafo no es bipartita\n";
    std::cout << "\n";
    
}

/*
Referencias: 

    GeeksforGeeks. (2022). Topological Sorting. https://www.geeksforgeeks.org/topological-sorting.

    GeeksforGeeks. (2022). Check whether a given graph is Bipartite or not. https://www.geeksforgeeks.org/bipartite-graph.

    GeeksforGeeks. (2022). Kahn's algorithm for Topological Sorting. https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution.

*/