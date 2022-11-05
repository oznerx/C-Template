#include <iostream>
#include <fstream>
#include <vector>


class Graph {
private:

    bool** adjMatrix;
    int numVertices;
    std::vector<std::vector<int>> adjList;

public:

    Graph(){
        bool** adjMatrix;
        int numVertices;
        std::vector<std::vector<int>> adjList;
    }

    void loadMatrix(int numVertices) {

        this->numVertices = numVertices;
        adjMatrix = new bool*[numVertices];
        
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
            adjMatrix[i][j] = false;
        }

    }

    void addEdge(int i, int j) {
        adjMatrix[i][j] = true;
        adjMatrix[j][i] = true;
    }

    void removeEdge(int i, int j) {
    adjMatrix[i][j] = false;
    adjMatrix[j][i] = false;
    }

    void print() {

        for (int i = 0; i < numVertices; i++) {
            std::cout << i << " : ";
            for (int j = 0; j < numVertices; j++) {
            std::cout << adjMatrix[i][j] << " " << "\n";
            }
        }

    }

    ~Graph() {

        for (int i = 0; i < numVertices; i++) {
            delete[] adjMatrix[i];
            delete[] adjMatrix;
        }

    }

    void loadGraph(int n, int m) {

    }

};






int main()
{






}