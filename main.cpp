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

    void listDFS(int a){

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

    void _DFS(int a){

        // Mark the current node as visited and print it
        visited[a] = true;
        std::cout << a << " ";
    
        // Recur for all the vertices adjacent to this vertex

        for (int i = 0; i < sizeof(adjMatrix[a]); ++i) {

            if (adjMatrix[a][i] == true) {

                if (!visited[i]) {
                    _DFS(i);
                }

            }

                
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
    void listDFSH(int a) {

        /*Hacer DFS con la matriz*/
        
        // Call the recursive helper function to print DFS
        // traversal starting from all vertices one by one
        for (auto i : adjList) {

            if (i.first < a) {
                std::cout << "a\n";
            }

            else {

                if (visited[i.first] == false) {
                    listDFS(i.first);
                }

            }

        }

        std::cout << "\n";
            
    }

    /*Imprima el Recorrido de DFS (Profundidad) a partir de nodo inicial.*/
    void DFS(int a) {
        /*Hacer DFS con la matriz*/

        for (int i = a; i < sizeof(adjMatrix)-1 ;i++) {
            
            if (visited[i] == false) {
                _DFS(i);
            }

        }
        
        std::cout << "\n";
            
    }


    /*Imprima el Recorrido de BFS (Anchura) a partir de nodo inicial.o.*/
    void BFS(int a) {
        /*Hacer BFS con la lista*/
    }



};






int main()
{

    Graph *g = new Graph();
    g->loadGraph(7, 7);

    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 3);
    g->addEdge(2, 3);
    g->addEdge(2, 4);
    g->addEdge(3, 5);
    g->addEdge(5, 6);

    g->print();
    g->DFS(0);
    

}