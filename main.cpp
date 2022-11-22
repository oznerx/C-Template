/* 
========================================================================================================
								Pedro Alonso Moreno Salcedo, A01741437
								Juan Carlos Hernández Ríos, A01740821
								Ozner Axel Leyva Mariscal, A01742377
This program simulates the propagation of a virus using graphs, and it determines the node that infects
the most people given a period of time. Then it tests this algorithm using various test cases. 
									Made on November 17th 2022
========================================================================================================
*/

// To compile use: g++ -std=c++17 main.cpp -o main

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>


using namespace std;

class Edge {

	string from;
	string to;

public:

    Edge(string from, string to) {
        this->from = from;
        this->to = to;
    }

    string getFrom() {
        return from;
    }

    string getTo() {
        return to;
    }

};

class Graph {

    unordered_map <string, vector<string>> adjacencyList; // Graph representation

    int numVertex;
    int numEdges;

	public:

    Graph(int numVertex, int numEdges, vector<Edge> edges) {

        this->numEdges = numEdges;
        this->numVertex = numVertex;
            
        for(int i = 0; i < numEdges; i++) {

            Edge edge = edges[i];
            
            string from = edge.getFrom();
            string to = edge.getTo();
    
            // Add edge to adjacency list
            adjacencyList[from].push_back(to);
            adjacencyList[to].push_back(from);
            
        }

    }

    /* 
        Gets the levels and how many nodes infected, given a startNode.

        Time complexity: O (n + e) where n is the number of nodes and e the number of edges
        Space complexity: (n)
        
        Param: integer start node for getting amount infected
        Return: integer of the amount of infected nodes by start node 
    */
    void post(string startNode, int n) {

        unordered_map<string, bool> visited;
        unordered_map<string, int> levels;

        levels[startNode] = 0;
        visited[startNode] = true;

        // BFS search 
        queue <string> q;
        q.push(startNode);

        while(!q.empty()) {

            string currentNode = q.front();
            q.pop();

            for(auto neighbor : adjacencyList[currentNode]) {

                // If we haven't visited the neighbor
                if(!visited[neighbor]) {
                    // Get its level and store it
                    int neighborLevel = levels[currentNode] + 1;
                    levels[neighbor] = neighborLevel;

                    q.push(neighbor);
                    visited[neighbor] = true;

                }

            }
        }

        // get the friends to share with
        vector<string> friends;
        for (auto i : adjacencyList) {
            if ( (levels[i.first] <= n) && (levels[i.first] != 0)) {
                friends.push_back(i.first);
            }
        }

        std::cout << "La publicación de " << startNode << " puede ser vista por ";
        for (auto j : friends) {
            std::cout << j << ", ";
        }
        std::cout << "\n";
        
    }

    /*
    Imprime una idea general de la lista de adjacencia del grafo creado
    @Param: nada
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(1) 
    */
    void printList() {

        cout << "The adjacency list was created with the following structure:\n\n";

        for (auto i : adjacencyList) {

            std::cout << i.first << " -> ";

            for (auto j : i.second) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

    }

};

void read(string inputFilePath, vector<Edge> &edges, unordered_map<string, int> &inputs) {
    
    ifstream inputFile(inputFilePath);
    vector<int> numUsers, numFriends;

    string x , y, amige, de;   

    while(inputFile >> x >> amige >> de >> y) {

        if (amige == "publico") {
            inputs[x] = stoi(de.substr(2,1));
            //break;
        }

        cout << x << "->" << y << "\n";
        Edge *edge = new Edge(x,y);
        edges.push_back(*edge);

    }

    inputFile.close();
    

}
int main() {
  
    cout << "============================ Test 1 ============================\n";
    Edge *ed = new Edge("Ana", "Juan");
    Edge *ed2 = new Edge("Juan", "Pedro");
    Edge *ed3 = new Edge("Pedro", "Luis");
    Edge *ed4 = new Edge("Luis", "Sebastian");
    Edge *ed5 = new Edge("Pedro", "Gustavo");
    Edge *ed6 = new Edge("Gustavo", "Adrian");
    Edge *ed7 = new Edge("Adrian", "Saul");

    // Terminado, pero estoy leyendo el archivo todavia, en el avance lo subo bien (con la lectura)

    vector<Edge> edges;/*
    edges.push_back(*ed);
    edges.push_back(*ed2);
    edges.push_back(*ed3);
    edges.push_back(*ed4);
    edges.push_back(*ed5);
    edges.push_back(*ed6);
    edges.push_back(*ed7);*/
    
    /*Graph graph(8, 7, edges);
    graph.printList();
    graph.post("Ana", 3);*/
    unordered_map<string, int> inputs;
    read("metabook.txt", edges, inputs);
    // La publicación de Ana puede ser vista por Juan, Pedro, Luis, Gustavo



    /*read("Grafo1.txt", n, e, t, edges);
    Graph graph(n, e, t, edges);
    graph.print();
    int greatestNode = graph.getGreatestPropagationNode();
    cout << "Node #" << greatestNode << ", within t="<< t << ", allows the greatest infection propagation." << "\n\n";*/
}