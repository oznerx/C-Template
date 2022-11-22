#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>


class Graph {
private:

    int numVertex;
    int numEdges;
    int currentEdges;
    std::vector<bool> visited;
    std::vector<std::vector<int>> adjList;
    std::stack<int> stack; 
    std::vector<int> fanOut; // usar mapa si se trata de nodos descritos con letras 
    std::unordered_map<int, bool> conection; // 

    /*
    Carga una lista de adjacencia
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V)
    Complejidad de espacio: O(V) 
    */
    void loadList() {
        adjList.resize(numVertex);
        fanOut.resize(numVertex, 0);
        visited.resize(numVertex);
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
        fanOut[a] += 1;
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
    Ordena nodos de manera topologica
    @Param: (int current) nodo actual en el que se encuentra
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void _topologicalSort2(int current) {

        visited[current] = true;

        for (auto i = adjList[current].begin(); i != adjList[current].end(); ++i) {

            if (!visited[*i]) {
                _topologicalSort2(*i);
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
    Salida: (bool) si el grafo está conectado
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
    @Param:(int n) Cantidad de Vertices, (int m) Cantidad de Arcos, (vector <pair<int, int>> edges) lista de conexiones entre los nodos 
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V + E) 
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
        	        
        for (int i = 0; i < adjList.size() ;i++) {

            std::cout << i << " : ";

            for (int j : adjList[i]) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

        std::cout << "\n";
	    
    }

    /*
    Ordena nodos de manera topologica    
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void topologicalSort() {

        std::vector<int> in_degree(numVertex, 0);
    
        for (int u = 0; u < numVertex; u++) {

            std::vector<int>::iterator itr;
            for (itr = adjList[u].begin();itr != adjList[u].end(); itr++) {
                in_degree[*itr]++;
            }

        }
    
        std::queue<int> q;

        for (int i = 0; i < numVertex; i++) {

            if (in_degree[i] == 0) {
                q.push(i);
            }

        }

        int cnt = 0;
    
        std::vector<int> top_order;
    
        while (!q.empty()) {

            int u = q.front();
            q.pop();
            top_order.push_back(u);
    
            std::vector<int>::iterator itr;
            
            for (itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {

                if (--in_degree[*itr] == 0) {
                    q.push(*itr);
                }

            }

            cnt++;

        }

        if (cnt != numVertex) {
            std::cout << "Hay un ciclo en el grafo\n";
            return;
        }

        for (int i = 0; i < top_order.size(); i++) {
            std::cout << top_order[i] << " ";
        }

        std::cout << std::endl;
    
    }
    
    /*
    Verifica que el Grafo Dirigido (DAG) es un árbol utilizando ordenación topológica
    @Param: nada
    Salida: (bool) si el árbol está conectado
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    bool topologicalSortCheck() {

        std::vector<int> in_degree(numVertex, 0);
    
        for (int u = 0; u < numVertex; u++) {

            std::vector<int>::iterator itr;
            for (itr = adjList[u].begin();itr != adjList[u].end(); itr++) {
                in_degree[*itr]++;
            }

        }
    
        std::queue<int> q;
        for (int i = 0; i < numVertex; i++) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        int cnt = 0;
    
        std::vector<int> top_order;
    
        while (!q.empty()) {

            int u = q.front();
            q.pop();
            top_order.push_back(u);
    
            std::vector<int>::iterator itr;
            for (itr = adjList[u].begin(); itr != adjList[u].end(); itr++) {

                if (--in_degree[*itr] == 0) {
                    q.push(*itr);
                }

            }

            cnt++;

        }

        if (cnt != numVertex) {
            std::cout << "Hay un ciclo en el grafo\n";
            return false;
        }

        return true;
    
    }

    /*
    Verifica que el Grafo Dirigido (DAG) puede ser representado como Grafo bipartita.    
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    bool bipartiteGraph() { 

        std::vector<int> color(numVertex, -1);
    
        std::queue<std::pair<int, int> > q;
    
        for (int i = 0; i < numVertex; i++) {
        
            if (color[i] == -1) {
            
                q.push({ i, 0 });
                color[i] = 0;
            
                while (!q.empty()) {

                    std::pair<int, int> p = q.front();
                    q.pop();
                
                    int v = p.first;
                    int c = p.second;
                    
                    for (int j : adjList[v]) {
                    
                        if (color[j] == c) {
                            return 0;
                        }
                    
                        if (color[j] == -1) {
                            color[j] = (c) ? 0 : 1;
                            q.push({ j, color[j] });
                        }

                    }

                }

            }

        }

        return 1;

    }

    /*
    Ordena nodos de manera topologica   
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    void topologicalSort2() {

        clearVisited();

        for (int i = 0; i < numVertex; i++) {

            if (visited[i] == false) {
                _topologicalSort2(i);
            }

        }

        while (stack.empty() == false) {
            std::cout << stack.top() << " ";
            stack.pop();
        }

        std::cout << "\n";

    }

    /*
    Verifica que el Grafo Dirigido (DAG) es un árbol
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    bool isTree() {
        return isConnected() && (numEdges == numVertex - 1) && topologicalSortCheck();
    } 

    void getFanOut() {
        for (int i = 0; i < fanOut.size(); i++) {
            std::cout << "El nodo " << i << " tiene " << fanOut[i] << " nodos adyacentes.\n";
        } 
    }

    void getMaxFanOut() {

        int max = 0;

        for (int i = 0; i < fanOut.size(); i++) {
            if ( fanOut[i] > fanOut[max]) {
                max = i;
            }
        } 

        std::cout << "El nodo con mas nodos adyacentes es el: " << max << "\n";

    }

    /* Obtiene los el nodo mas lejano a partir de un nodo inicial */
    void farthestNode(int startNode) {
    // Required structures
    std::vector<bool> enqueued(numVertex, false);
    std::vector<int> levels(numVertex, -1);
    int infectedNodes = 0;

    // Initialize with start node
    levels[startNode] = 0;
    enqueued[startNode] = true;

    // BFS search 
    std::queue <int> q;
    q.push(startNode);

    while(!q.empty()) {

        int currentNode = q.front();
        q.pop();

        for(int neighbor : adjList[currentNode]) {
            // If we haven't enqueued the neighbor
            if(!enqueued[neighbor]) {
                // Get its level and store it
                int neighborLevel = levels[currentNode] + 1;
                levels[neighbor] = neighborLevel;

                // Otherwise we add it to the queue and mark it as enqueued
                q.push(neighbor);
                enqueued[neighbor] = true;

            }
        }
    }


    int farthest = 0;
    for (int i = 0; i < levels.size(); i++) {
        if ( levels[i] > levels[farthest]) {
            farthest = i;
        }
    }

    std::cout << "The farthest node from the node " << startNode << " is the node: " << farthest << "\n";

    }	

    void bfsSearch(int startNode, int nodeToSearch) {

        clearVisited();
        std::vector<int> time(numVertex, 0);

        // Initialize with start node
        time[startNode];
        visited[startNode] = true;

        // BFS search 
        std::queue <int> q;
        q.push(startNode);

        while(!q.empty()) {

            int currentNode = q.front();
            q.pop();

            for(int neighbor : adjList[currentNode]) {
                // If we haven't enqueued the neighbor
                if(!visited[neighbor]) {
                    // Get its level and store it
                    int neighborTime = time[currentNode] + 1;
                    time[neighbor] = neighborTime;

                    // Otherwise we add it to the queue and mark it as visited
                    q.push(neighbor);
                    visited[neighbor] = true;

                }

                if (neighbor == nodeToSearch) {
                    std::cout << "El nodo " << nodeToSearch << " a partir del nodo " << startNode << ", se encontró en el tiempo " << time[nodeToSearch] << "\n"; 
                    break;
                }

            }
        }

    }

    /* Recorrido en grafo desconectado */
    void bfsSearchDisconnected(int startNode, int color) {

        std::vector<int> conjunto;
        visited[startNode] = true;

        // BFS search 
        std::queue <int> q;
        q.push(startNode);
        conjunto.push_back(startNode);

        while(!q.empty()) {

            int currentNode = q.front();
            q.pop();

            for(int neighbor : adjList[currentNode]) {

                if(!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    conjunto.push_back(neighbor);
                }

            }
        }

        std::cout << "El conjunto " << color << " contiene los siguientes nodos: \n";
        for (auto i : conjunto) {
            std::cout << i << " ";
        }
        std::cout << "\n";

    }  

    void printVisited() {
        for (int j = 0; j < visited.size() ; j++) {
            std::cout << visited[j] << "\n";
        }
    }

    void disconnectedSearch(int startNode, int conjuntos) {

        clearVisited();

        int i = 1;
        while (i < conjuntos) {

            if (i == 1) {
                bfsSearchDisconnected(startNode, i);
            }

            i++;
            for (int j = 0; j < visited.size() ; j++) {
                if (!(visited[j])) {
                    bfsSearchDisconnected(j, i);
                }
            }

        }

    }

    void isIn(std::vector<int> nodes) {  // cuales si se encontraron?

        int count = nodes.size();
        std::vector<int> notFound;

        for (int i = 0; i < numVertex; i++) {

            for (int j = 0; j < nodes.size(); j++) {

                if (nodes[j] == i) {
                    count -= 1;
                }

            }

        }

        std::cout << count << "\n";

        if (count != 0) {
            std::cout << "No se encuentran todos los nodos\n";
        }

        std::cout << "Se encontraron todos los nodos\n";

    }

    void differentsPaths(int startNode, int nodeToSearch) {

        clearVisited();
        std::vector<int> time(numVertex, 0);

        // Initialize with start node
        time[startNode];
        visited[startNode] = true;

        // BFS search 
        std::queue <int> q;
        q.push(startNode);

        while(!q.empty()) {

            int currentNode = q.front();
            q.pop();

            for(int neighbor : adjList[currentNode]) {
                
                // If we haven't enqueued the neighbor
                if(!visited[neighbor]) {
                    // Get its level and store it
                    int neighborTime = time[currentNode] + 1;
                    time[neighbor] = neighborTime;

                    // Otherwise we add it to the queue and mark it as visited
                    q.push(neighbor);
                    visited[neighbor] = true;

                }

                if (neighbor == nodeToSearch) {
                    std::cout << "El nodo " << nodeToSearch << " a partir del nodo " << startNode << ", se encontró en el tiempo " << time[nodeToSearch] << "\n"; 
                    break;
                }

            }
        }

    }

};

int main()
{

    /*std::cout << "\n======================== Primer Grafo ========================\n";
    Graph *g1 = new Graph();
    std::vector <std::pair<int, int>> edges1 = {{5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}}; 
    g1->loadGraph(6, 6, edges1);
    g1->print();
    g1->getFanOut();
    g1->getMaxFanOut();
    std::cout << "\n";
    g1->farthestNode(5);
    g1->bfsSearch(5, 1);*/
    
    Graph *g2 = new Graph();
    std::vector <std::pair<int, int>> edges2 = {{0,1}, {1,2}, {2,3}, {4,5}}; 
    g2->loadGraph(6, 4, edges2); 
    g2->print();
    g2->disconnectedSearch(0, 2);
    std::vector<int> nodes = {1,5};
    g2->isIn(nodes);

}
