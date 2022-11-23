/*
    Ozner Axel Leyva Mariscal
    A01742377
    Mini Reto 2
    22 de Noviembre del 2022
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

    unordered_map <string, vector<string>> adjacencyList;
    int numVertex;
    int numEdges;

	public:

    /* Constructor de grafo */
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
    Imprime que amigos pueden ver una publicación a partir de un nombre (nodo inicial) y la profundidad
    @Param: (string startNode) nodo del cual empezar la búsqueda de la publicación , (int n) número de la profundidad
    Salida: nada
    Complejidad de tiempo: O(V + E) siendo V el número de vértices y E el número de aristas
    Complejidad de espacio: O(V) siendo V el número de vértices
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
    vector<Edge> edges1;
    unordered_map<string, string> inputs1;
    int numVertex1, numEdges1;
    read("metabook.txt", edges1, inputs1, numVertex1, numEdges1);  
    Graph graph1(numVertex1, numEdges1, edges1);
    graph1.print();
    for (auto k : inputs1) {
        graph1.post(k.first, stoi(k.second));
    }
    std::cout << "\n";

    
    cout << "============================ Test 2 ============================\n";
    vector<Edge> edges2;
    unordered_map<string, string> inputs2;
    int numVertex2, numEdges2;
    read("metabook2.txt", edges2, inputs2, numVertex2, numEdges2);  
    Graph graph2(numVertex2, numEdges2, edges2);
    graph2.print();
    for (auto k : inputs2) {
        graph2.post(k.first, stoi(k.second));
    }
    std::cout << "\n";
    
    cout << "============================ Test 3 ============================\n";
    vector<Edge> edges3;
    unordered_map<string, string> inputs3;
    int numVertex3, numEdges3;
    read("metabook3.txt", edges3, inputs3, numVertex3, numEdges3);  
    Graph graph3(numVertex3, numEdges3, edges3);
    graph3.print();
    for (auto k : inputs3) {
        graph3.post(k.first, stoi(k.second));
    }
    std::cout << "\n";

    cout << "============================ Test 4 ============================\n";
    vector<Edge> edges4;
    unordered_map<string, string> inputs4;
    int numVertex4, numEdges4;
    read("metabook4.txt", edges4, inputs4, numVertex4, numEdges4);  
    Graph graph4(numVertex4, numEdges4, edges4);
    graph4.print();
    for (auto k : inputs4) {
        graph4.post(k.first, stoi(k.second));
    }
    std::cout << "\n";

}

/*
Referencias:

    GeeksforGeeks. (2022). Substring in C++. https://www.geeksforgeeks.org/substring-in-cpp.

*/