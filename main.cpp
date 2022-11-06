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

    std::map<int, bool> visited;
    

public:

    Graph() {
        bool** adjMatrix;
        int numVertices;
        std::vector<std::vector<int>> adjList;
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            delete[] adjMatrix[i];
            delete[] adjMatrix;
        }
    }

    void loadMatrix(int n) {

        // Set the max num of vertices
        this->numVertices = n;
        adjMatrix = new bool*[n];
        
        for (int i = 0; i < n; i++) {
            adjMatrix[i] = new bool[n];
            for (int j = 0; j < n; j++)
            adjMatrix[i][j] = false;
        }

    }

    void loadList(int n, int m ) {

        this->numVertices = n;
        this->numEdges = m;

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

    void DFSUtil(int a)
    {

        // Mark the current node as visited and print it
        visited[a] = true;
        std::cout << a << " ";
    
        // Recur for all the vertices adjacent to this vertex
        std::list<int>::iterator i;
        for (i = adjList[a].begin(); i != adjList[a].end(); ++i) {

            if (!visited[*i]) {
                DFSUtil(*i);
            }
                
        }

    }

    /*Imprima el Recorrido de DFS (Profundidad) a partir de nodo inicial.*/
    void DFS(int a, int b) {

        /*Hacer DFS con la matriz*/
        
        // Call the recursive helper function to print DFS
        // traversal starting from all vertices one by one
        for (auto i : adjList) {

            if (visited[i.first] == false) {
                DFSUtil(i.first);
            }

        }

        std::cout << "\n";
 
                
    }

    /*Imprima el Recorrido de BFS (Anchura) a partir de nodo inicial.o.*/
    void BFS(int a, int b) {
        /*Hacer BFS con la lista*/
    }



};






int main()
{
    /*
    Graph *g = new Graph();
    g->loadMatrix(6);
    g->addEdgeToMatrix(1, 3);
    g->addEdgeToMatrix(5, 2);
    g->addEdgeToMatrix(3, 4);
    g->addEdgeToMatrix(0, 4);
    g->printMatrix();
    */


    Graph *g2 = new Graph();
    g2->loadList(6, 3); // 6 nodos/vertices y 3 aristas 

    g2->addEdgeToList(0, 3);
    g2->addEdgeToList(5, 2);
    g2->addEdgeToList(3, 4);
    g2->addEdgeToList(3, 5);
    
    g2->printList();
    g2->DFS(0,6);

}