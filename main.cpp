/* 
========================================================================================================
								Pedro Alonso Moreno Salcedo, A01741437
								Juan Carlos Hernández Ríos, A01740821
								Ozner Axel Leyva Mariscal, A01742377

This program simulates the propagation of a virus using graphs, and it determines the node that infects
the most people given a period of time. Then it tests this algorithm using varios test cases. 

									Made on November 17th 2022
========================================================================================================
*/

// To compile use: g++ -std=c++17 main.cpp -o main

#include <iostream>
#include <vector>
#include <queue>

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
	
		Graph(int n, int e, int t, Edge edges[]) {
			// Setting t
			this->t = t;
			
			// Ensure capacity
			while(adjacencyList.size() < n) {
				vector<int> row;
				adjacencyList.push_back(row);
			}
			
			for(int i = 0; i < e; i++) {
				Edge edge = edges[i];
				
				int from = edge.getFrom();
				int to = edge.getTo();
				
				// Add edge to adjacency list
				adjacencyList[from].push_back(to);
			}
		}

		/* 
			?
	
			Time complexity: ?
			Space complexity: ?
			
			Param: ?
			Return: ?
		*/

		int getInfectedNodes(int startNode) {
			// Keep track of the infected nodes
			int n = adjacencyList.size();
			vector<bool> infected(n, false);
			int infectedCount = 0;

			// Prepare the bfs search
			queue<int> queue;
			queue.push(startNode);
			infected[startNode] = true;

			// Keep track of the level we are in bfs
			int level = 0;

			while(!queue.empty()) {
				int currentNode = queue.front();
				queue.pop();

				for(int neighbor : adjacencyList[currentNode]) {
					// If we haven't infected it, then we add it to the queue
					if(!infected[startNode]) {
						queue.push(neighbor);
						// Mark as infected so we don't infect it twice
						infected[startNode] = true;
						// Increase counter
						infectedCount++;
					}
				}
			}

			// Return the number of infected nodes
			return infectedCount;
		}

		/* 
			Get the start node that would infect the most amount of distinct nodes.
	
			Time complexity: ?
			Space complexity: ?
			
			Param: ?
			Return: an integer representing the node, or -1 if not found
		*/

		int greatestPropagationNode() {
			int n = adjacencyList.size();
			
			// Initialize as negative values
			int greatestAmountInfected = -1;
			int greatestPropagationNode = -1;

			for(int i = 0; i < n; i++) {
				int amountInfected = getInfectedNodes(i);
				
				// Keep track of the node with the greatest propagation
				if(amountInfected > greatestAmountInfected) {
					greatestAmountInfected = amountInfected;
					greatestPropagationNode = i;
				}
			}
			
			return greatestPropagationNode;
		}
};

int main() {
	cout << "Test #1" << "\n";
	Edge edges[] = {
		{0, 1},
	};
	
	/*
		0-1
	*/
	Graph graph(1,1,1,edges);
	
	// Nota: poner el caso de prueba de otro equipo
}

/*
References:

    Moreno, P. (2022). Act 4.2 - Grafos: Algoritmos complementarios. Canvas. Retrieved from: https://experiencia21.tec.mx/courses/307981/assignments/9662675/submissions/166486

*/