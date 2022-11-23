/*
Ozner Axel Leyva Mariscal
A01742377
Mini Reto 2
*/


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
    void print() {

        cout << "La lista de adyacencia se creó con la siguiente estructura:\n";

        for (auto i : adjacencyList) {

            std::cout << i.first << " -> ";

            for (auto j : i.second) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }
        
        std::cout << "\n";

    }


};

void read(string inputFilePath, vector<Edge> &edges, unordered_map<string, string> &inputs, int &numVertex, int &numEdges) {
    
    ifstream inputFile(inputFilePath);
    int e = 0;
    string x , y, amige, de, n, publico;   
    unordered_map<string, bool> names;

    while(inputFile >> x >> amige >> de >> y) {

        names[x] = true;
        names[y] = true; 

        if (amige == "publico") {
            inputs[x] = de.substr(2,1);
            break;
        }

        //cout << x << "->" << y << "\n";
        Edge *edge = new Edge(x,y);
        edges.push_back(*edge);
        e++;

    }

    numEdges = e;

    inputFile >> x >> n;
    inputs[y] = n.substr(2,1);
    

    int j = 0;
    for (auto i : names) {
        j++;
    }

    numVertex = j;
    inputFile.close();
    
}

int main() {
  
    cout << "============================ Test de canvas ============================\n";
    vector<Edge> edges;
    unordered_map<string, string> inputs;
    int numVertex, numEdges;
    read("metabook.txt", edges, inputs, numVertex, numEdges);  
    Graph graph(numVertex, numEdges, edges);
    graph.print();
    for (auto k : inputs) {
        graph.post(k.first, stoi(k.second));
    }
    std::cout << "\n";


}