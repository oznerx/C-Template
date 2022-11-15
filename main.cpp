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

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <list>


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
	vector<bool> visited; 
	vector<int> levels;

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
				visited.push_back(false);
				levels.push_back(0);
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


    void clearVisited() {

        for (int i = 0; i < visited.size() ;i++) {
            visited[i] = false;
        }

    }

    void print() {

        std::cout << "\nLa lista de adyacencia se creó con la siguiente estructura:\n\n";
        
        for (int i = 0; i < adjacencyList.size() ;i++) {

            std::cout << i << " : ";

            for (auto j : adjacencyList[i]) {
                std::cout << j << " ";
            }

            std::cout << "\n";

        }

        std::cout << "\n";

    }

	void printLevels() {

		for (int i = 0; i < levels.size();i++) {
			cout << "El nodo " << i << " tiene un nivel de: " << levels[i] << "\n";
		}

	}

    void calculateLevels(int s) {
        queue <int> q;
        q.push(s);
        levels[s] = 0;
        visited[s] = true;

        while(!q.empty())
        {
            int p = q.front();
            //cout<<p<<endl;
            q.pop();

            vector <int>::iterator it;
            for(it=adjacencyList[p].begin();it!=adjacencyList[p].end();++it)
            {
                if(visited[*it] == false)
                {
                    levels[*it] = levels[p] + 1;
                    q.push(*it);
                    visited[*it] = true;
                }
            }
        }
    }

    /*
    Imprime el Recorrido de BFS de una lista de adjacencia a partir de un nodo inicial
    @Param: (int a) nodo inicial
    Salida: nada
    Complejidad de tiempo: O(V + E)
    Complejidad de espacio: O(V) 
    */
    int BFS(int a) {

		int infected = 0;
        clearVisited();
        std::list<int> queue;
        visited[a] = true;
        queue.push_back(a);
    
        while (!queue.empty()) {

            a = queue.front();
            //std::cout << a << " ";
            queue.pop_front();

            for (auto i: adjacencyList[a]) {

                if (!visited[i] && ( levels[i] <= t)) {
                    visited[i] = true;
                    queue.push_back(i);
					infected += 1;
                }

            }

        }

        //std::cout << "\n";
		return infected;

    }

	void getInfected() {
		
		for (int i = 0; i < adjacencyList.size(); i++) {
			cout << "El vértice " << i << " infectó a " << BFS(i) << " nodos\n";
		}

	}

	void getBest() {
		
		// usa la libreria de algorithm
		
		vector<int> infected(adjacencyList.size(), 0);
		int best;

		for (int i = 0; i < adjacencyList.size(); i++) {
			infected[i] = BFS(i);
		}

		for (auto i : infected) {
			if (infected[i] == *max_element(infected.begin(), infected.end())) {
				best = i;
			}
		}

		cout << "El nodo que mas infectó desde el con el tiempo " << t << " es el: " << best << "\n";

	}

};

int main() {
	cout << "Test #1" << "\n";
	
	// Nota: poner el caso de prueba de otro equipo

    Edge edges[] = {{0,2}, {0,5}, {0,6}, {0,7}, {2,5}, {5,3}, {3,8}, {8,7}, {6,1}, {6,4}, {4,9}};

    Graph graph(10, 11, 2, edges);
    graph.print();
	graph.calculateLevels(0);
	graph.printLevels();
	cout << "\n\n";
	graph.getInfected();
	graph.getBest();


}

/*
References:

    Moreno, P. (2022). Act 4.2 - Grafos: Algoritmos complementarios. Canvas. Retrieved from: https://experiencia21.tec.mx/courses/307981/assignments/9662675/submissions/166486

*/