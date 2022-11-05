#include <iostream>
#include <fstream>
#include <vector>


class Graph {
private:

    bool** adjMatrix;
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> adjList;

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

        // Set the max num of edges
        this->numEdges = m;

        for(int i = 0; i < n; i++) {
            std::vector<int> node;
            adjList.push_back(node);
        }

        
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
        if (a < numVertices && b < numVertices) {
            adjList[a].push_back(b);
        }
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
        for (int i = 0; i < numVertices ;i++) {
            for(int j = 0; j < adjList[i].size() ;j++) {
                std::cout << adjList[i][j];
            }
        }
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
    g2->loadList(6, 3);
    g2->addEdgeToList(1, 3);
    g2->addEdgeToList(5, 2);
    g2->addEdgeToList(3, 4);
    g2->printList();

}