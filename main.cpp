#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

class Graph {
private:

    bool** adjMatrix;
    std::map<int, std::list<int> > adjList;
    int numVertices;
    int numEdges;
    int currentEdges;

    std::map<int, bool> visited;

    void loadMatrix(int n) {

        adjMatrix = new bool*[numVertices];
        
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];

            for (int j = 0; j < numVertices; j++) {
                adjMatrix[i][j] = false;
            }

        }

    }

    void loadList(int n, int m ) {

        for (int i = 0; i < numVertices; i++) {
            std::list<int> temp;
            adjList.emplace(i, temp);
        }

        //std::cout << adjList.size() << "\n";

    } 

    void addEdgeToMatrix(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }

    void removeEdgeFromMatrix(int i, int j) {
        adjMatrix[i][j] = false;
        adjMatrix[j][i] = false;
    }

    void addEdgeToList(int a, int b) {
        adjList[a].push_back(b); // Add b to a’s list.
    }

    void removeEdgeFromList(int i, int j) {
        //adjMatrix[i][j] = false;    
        //adjMatrix[j][i] = false;
    }

    void printMatrix() {
            
        for (int i = 0; i < numVertices; i++) {
            std::cout << i << " : ";
            for (int j = 0; j < numVertices; j++) {
                std::cout << adjMatrix[i][j] << " " ;
            }
            std::cout << "\n";
        }

    }

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

    void clearVisited() {

        for (int i = 0; i < visited.size() ;i++) {
            visited[i] = false;
        }

    }
    
public:

    Graph() {
        bool** adjMatrix;
        int numVertices;
        std::vector<std::vector<int>> adjList;
        currentEdges = 0; 
    }

    ~Graph() {

        for (int i = 0; i < numVertices; i++) {
            delete[] adjMatrix[i];
            delete[] adjMatrix;
        }

    }

    void loadGraph(int n, int m ) {

        this->numVertices = n;
        this->numEdges = m;
        loadList(numVertices, numEdges);
        loadMatrix(numVertices);

    }

    void addEdge(int a, int b) {

        if (currentEdges < numEdges) {
            currentEdges++;
            addEdgeToMatrix(a, b);
            addEdgeToList(a, b);
        }

        else {
            std::cout << "Numero de conexiones maximo alcanzado\n";
            return;
        }
        
    }

    void print() {

        std::cout << "\nLa matriz se creo con la siguiente estructura:\n";
        printMatrix();
        std::cout << "\nLa lista se creo con la siguiente estructura:\n";
        printList();

    }

    /*Imprima el Recorrido de DFS (Profundidad) a partir de nodo inicial.*/
    void listDFS(int a) {

        // Mark the current node as visited and print it
        visited[a] = true;
        std::cout << a << " ";
    
        // Recur for all the vertices adjacent to this vertex
        std::list<int>::iterator i;
        for (i = adjList[a].begin(); i != adjList[a].end(); ++i) {

            if (!visited[*i]) {
                listDFS(*i);
            }
                
        }
            
    }

    /*Imprima el Recorrido de DFS (Profundidad) a partir de nodo inicial.*/
    void _DFS(int a) {

        visited[a] = true;
        std::cout << a << " ";

        for (int i = a; i < sizeof(adjMatrix[a]); ++i) {

            if (adjMatrix[a][i] == true && (!visited[i])) {
                _DFS(i);
            }

        }
            
    }

    void DFS(int a) {
        clearVisited();
        _DFS(a);
    }


    /*Imprima el Recorrido de BFS (Anchura) a partir de nodo inicial.o.*/
    void BFS(int a) {

        clearVisited();
        std::list<int> queue;
        visited[a] = true;
        queue.push_back(a);
    
        while(!queue.empty())
        {
            // Dequeue a vertex from queue and print it
            a = queue.front();
            std::cout << a << " ";
            queue.pop_front();
    
            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
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
    g->loadGraph(6, 8);

    g->addEdge(0, 1);
    g->addEdge(0, 3);
    
    g->addEdge(1, 2);
    
    g->addEdge(2, 5);
    
    g->addEdge(3, 1);
    g->addEdge(3, 5);
    g->addEdge(3, 4);
    
    g->addEdge(4, 5);

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