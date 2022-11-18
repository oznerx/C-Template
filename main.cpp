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

using namespace std;

class Edge {
	int from;
	int to;

	public:
		Edge(int from, int to) {
			this->from = from;
			this->to = to;
		}

		int getFrom() {
			return from;
		}

		int getTo() {
			return to;
		}
};

class Graph {
	vector<vector<int>> adjacencyList; // Graph representation
	int t; // Time units available

	public:

		/* 
			Load the graph contents into an adjacency list.
			This function should only be executed once per graph.
	
			Time complexity: O(n + e) where n is the number of nodes in the graph,
			and e is the number of edges in the graph
			Space complexity: O(n + e) (assuming the adjacency list could be empty)
			
			Param: integers n, e for number of nodes and edges, and array of edges of size e.
			integer t for the propagation time units available.
			The values of the edges must be from 0 until n-1 (inclusive). There should not be
			edge duplicates.
			Return: no return
		*/
	
		Graph(int n, int e, int t, vector<Edge> edges) {
			// Setting t
			this->t = t;
			
			// Ensure capacity
			adjacencyList.resize(n);
			
			for(int i = 0; i < e; i++) {
				Edge edge = edges[i];
				
				int from = edge.getFrom();
				int to = edge.getTo();
        
				
				// Add edge to adjacency list
				adjacencyList[from].push_back(to);
			}
		}

		/* 
			Gets the levels and how many nodes infected, given a startNode.
	
			Time complexity: O (n + e) where n is the number of nodes and e the number of edges
			Space complexity: (n)
			
			Param: integer start node for getting amount infected
			Return: integer of the amount of infected nodes by start node 
		*/
	
	    int getAmountInfected(int startNode) {
			// Required structures
			int n = adjacencyList.size();
			vector<bool> enqueued(n, false);
			vector<int> levels(n, -1);
			int infectedNodes = 0;

			// Initialize with start node
			levels[startNode] = 0;
	        enqueued[startNode] = true;

			// BFS search 
			queue <int> q;
	        q.push(startNode);

	        while(!q.empty()) {
	            int currentNode = q.front();
	            q.pop();
	
	            for(int neighbor : adjacencyList[currentNode]) {
					// If we haven't enqueued the neighbor
	                if(!enqueued[neighbor]) {
						// Get its level and store it
						int neighborLevel = levels[currentNode] + 1;
	                    levels[neighbor] = neighborLevel;

						// If neighbor level is not in [0, t] (inclusive) we exit
						if(neighborLevel > t) {
							break;
						}

						// Otherwise we add it to the queue and mark it as enqueued
	                    q.push(neighbor);
	                    enqueued[neighbor] = true;

						// Increase the number of infected nodes
						infectedNodes++;
	                }
	            }
	        }
	
			return infectedNodes;
	    }	
	
		/* 
			Get the node with the greatest propagation within the given time.
	
			Time complexity: O (n*(n + e)) where n is the number of nodes and e the number of edges
			Space complexity: O(n)
			
			Param: no parameters
			Return: integer representing the node that infected the most nodes within the time
		*/
	
		int getGreatestPropagationNode() {
			int n = adjacencyList.size();
				
			// Initialize as negative values
			int greatestAmountInfected = -1;
			int greatestPropagationNode = -1;
	
			for(int i = 0; i < n; i++) {
				int amountInfected = getAmountInfected(i);
				cout << "Node #" << i << " infected " << amountInfected << " nodes\n";
				
				// Keep track of the node with the greatest propagation
				if(amountInfected > greatestAmountInfected) {
					greatestAmountInfected = amountInfected;
					greatestPropagationNode = i;
				}
			}
			cout << endl;
			return greatestPropagationNode;
		}
	
		/* 
			Print the graph (adjacency list)
	
			Time complexity: O (n + e) where n is the number of nodes and e the number of edges
			Space complexity: O(1)
			
			Param: no parameters
			Return: no return
		*/
	
	    void print() {
	        cout << "The adjacency list was created with the following structure:\n\n";
	        
	        for (int i = 0; i < adjacencyList.size() ;i++) {
	            cout << i << " : ";
	            for (int j : adjacencyList[i]) {
	                cout << j << " ";
	            }
	            cout << "\n";
	        }
	        cout << "\n";
	    }
};
// n e t 
// from - to
void read(string inputFilePath, int &n, int &e, int &t, vector<Edge> &edges) {
    ifstream inputFile(inputFilePath);
    string vertex, edge, time, from, to;   
    inputFile >> vertex >> edge >> time;
    n = stoi(vertex);
    e = stoi(edge);
    t = stoi(time);

    for(int i = 0; i < e; i++) {
        getline(inputFile, to);
        inputFile >> from >> to;
        Edge *ed = new Edge(stoi(from),stoi(to));
        //cout << from << " " << to << endl;
        edges.push_back(*ed);       
    }
    
    inputFile.close();
    

}
int main() {
  int n, e, t;
  
  cout << "============================ Test 1 ============================\n";
  vector<Edge> edges;
  read("Grafo1.txt", n, e, t, edges);
  Graph graph(n, e, t, edges);
  graph.print();
  int greatestNode = graph.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t="<< t << ", allows the greatest infection propagation." << "\n\n";

  vector<Edge> edges2;
  read("grafo2.txt", n, e, t, edges2);
  Graph graph2(n, e, t, edges2);
  graph2.print();
  greatestNode = graph2.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t="<< t << ", allows the greatest infection propagation." << "\n\n";

  vector<Edge> edges3;
  read("grafo3.txt", n, e, t, edges3);
  Graph graph3(n, e, t, edges3); 
  graph3.print(); 
  greatestNode = graph3.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t="<< t << ", allows the greatest infection propagation." << "\n\n";

  
  vector<Edge> edges4;
  read("grafo4.txt", n, e, t, edges4);
  Graph graph4(n, e, t, edges4);
  graph4.print();
  greatestNode = graph4.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t="<< t << ", allows the greatest infection propagation." << "\n\n";
  /*
    vector<Edge> edges1 = {{0,2}, {0,5}, {0,6}, {0,7}, {2,5}, {5,3}, {3,8}, {8,7}, {6,1}, {6,4}, {4,9}};
    
    Graph graph1(10, 11, 2, edges1);
    graph1.print();
    greatestNode = graph1.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t=2, allows the greatest infection propagation." << "\n";

  	cout << "\n\nTest #2" << "\n";
	
    vector<Edge> _edges2 = {{0,6}, {6,0}, {1,6}, {6,1}, {6,2}, {2,6}, {6,3}, {3,6}, {3,4}, {4,3}, {2,5}, {5,2}};

    Graph _graph2(7, 12, 2, _edges2);
    _graph2.print();
    greatestNode = _graph2.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t=2, allows the greatest infection propagation." << "\n";
  
  	cout << "\n\nTest #3" << "\n";
	
    vector<Edge> _edges3 = {{0,1}, {0,2}, {1,0}, {2,0}, {1,12}, {12,1}, {2,12}, {12,2}, {12,4}, {4,12}, 
	{4,5}, {5,4},{5,11}, {11,5}, {5,6}, {6,5}, {4,3}, {3,4}, {3,10}, {10,3}, {4,9},
	{9,4}, {9,7}, {7,9}, {7,8}, {8,7}, {8,14}, {14,8}, {9,13}, {13,9}, {13,15}, {15,13},
	{13,16}, {16,13}};

    Graph _graph3(17, 34, 2, _edges3);
    _graph3.print();
    greatestNode = _graph3.getGreatestPropagationNode();
	cout << "Node #" << greatestNode << ", within t=2, allows the greatest infection propagation." << "\n";

*/

	// Nota: poner el caso de prueba de otro equipo
}

/*
References:

Moreno, P. (2022). Act 4.2 - Grafos: Algoritmos complementarios. Canvas. Retrieved from:   https://experiencia21.tec.mx/courses/307981/assignments/9662675/submissions/166486

GeeksforGeeks. (2019, March 19). How to find the maximum element of a Vector using STL in C++?. https://www.geeksforgeeks.org/how-to-find-the-maximum-element-of-a-vector-using-stl-in-c

C++ List Library - resize() Function. (s.f.) TutorialsPoint. Retrieved from: https://www.tutorialspoint.com/cpp_standard_library/cpp_list_resize.htm

Chaudhary, M. (2016). Breadth First Search time complexity analysis. Retrieved from: https://stackoverflow.com/questions/26549140/breadth-first-search-time-complexity-analysis
*/