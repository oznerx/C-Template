/* 
========================================================================================================
								Pedro Alonso Moreno Salcedo, A01741437
								Juan Carlos Hernández Ríos, A01740821
								Ozner Axel Leyva Mariscal, A01742377

This program tests different implementations of a binary search tree and a splay tree, and 
compares their speed using an unsorted, sorted and reverse-sorted log file.

									Made on November 2nd 2022
========================================================================================================
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string>
#include <stack>
#include <queue>
#include <cstdio>
#include <ctime>

using namespace std;

template <class T>
class BSTNode { 
	public:
		T data;
		BSTNode *left;
		BSTNode *right;

		BSTNode() {
			data = NULL;
			left = NULL;
			right= NULL; 
		}

		BSTNode(T value) {
			data = value;
			left = NULL;
			right= NULL; 
		}
};

template <class T>
class BST {
	private:
		BSTNode<T> *root;
    	int amount = 0;

		/*
    		Gets the height of a tree
		    @Param: (BSTNode<T>* root) tree root    
		    Return: no return
		    Time complexity: O(n)
		    Space complexity: O(h) where h is the height of the tree, max complexity is O(n)
	    */

		int _height(BSTNode<T>* root) {
			if(root == NULL) {
				return -1;
			}
			
			int leftHeight = _height(root->left);
			int rightHeight = _height(root->right);

			return std::max(leftHeight, rightHeight) + 1;
		}

	public:
		BST() {
			root = NULL;
		}

		/*
    		Adds data to the tree
		    @Param: (T value) data to add   
		    Salida: nada
		    Time complexity: O(n)
		    Space complexity: O(1)
	    */

		void create(T value) {
			BSTNode<T>* newBSTNode = new BSTNode<T>(value);
			BSTNode<T>* current = root;
			BSTNode<T>* father = NULL;
      		amount++;
			
			if(root == NULL) {
				root = newBSTNode;
			} else {
				while(current != NULL) {
					father = current;
					
					if(value < current->data) {
						current = current->left;
					} else {
						current = current->right;
					}
				}
				
				if(value < father->data) {
					father->left = newBSTNode;
				} else {
					father->right = newBSTNode;
				}
			}
		}

		/*
    		Prints the data in pre order  
		    @Param: (BSTNode<T>* root) tree root    
		    Return: no return
		    Time complexity: O(n)
		    Space complexity: O(n)
	    */

		void preOrder(BSTNode<T>* root) {
			if (root != NULL) {
				cout << root->data << " ";
				preOrder(root->left);
				preOrder(root->right);
			}
		}

		/*
    		Prints the data in order  
		    @Param: (BSTNode<T>* root) tree root    
		    Return: no return
		    Time complexity: O(n)
		    Space complexity: O(n)
	    */

		void inOrder(BSTNode<T>* root) { 
			if (root != NULL) { 
			  inOrder (root->left);
			  cout << root->data << " ";
			  inOrder (root->right);
			}
		}

		/*
    		Prints the data in post order  
		    @Param: (BSTNode<T>* root) tree root    
		    Return: no return
		    Time complexity: O(n)
		    Space complexity: O(n)
	    */

		void postOrder(BSTNode<T>* root) { 
			if (root != NULL) {
			  postOrder (root->left);
			  postOrder (root->right);
			  cout << root->data << " ";
			}
		}

		/*
    		Prints the data level by level  
		    @Param: (BSTNode<T>* root) tree root    
		    Return: no return
		    Time complexity: O(n)
		    Space complexity: O(n)
	    */

		void levelByLevel(BSTNode<T>* root) {
			if(root == NULL) {
				return;
			}
			
			queue<BSTNode<T>*> queue;
			queue.push(root);
			
			while(!queue.empty()) {
				root = queue.front();
				queue.pop();
				cout << root->data << " ";
				
				if(root->left != NULL) {
					queue.push(root->left);
				}
				
				if(root->right != NULL) {
					queue.push(root->right);
				}
			}
		}
		
		void search(int opc) {
			if(root == NULL) {
			  cout << "El árbol no existe\n";
			} else {
				if(opc == 1) {
					preOrder(root);
					cout << "\n";
				} else if(opc == 2) {
					inOrder(root);
					cout << "\n";
				} else if (opc == 3) {
					postOrder(root);
					cout << "\n";
				} else if (opc == 4) {
					levelByLevel(root);
					cout << "\n";
				} else {
					cout << "Opción invalida\n";
				}
			}
		}

		/* 
			Searches a node with a specific target data into the tree
	
			Time complexity: O(h) where h is the height of the tree
			Space complexity: O(h) where h is the height of the tree
			
			Param: target data of type T to be searched
			Return: returns true if found in the tree, or false otherwise
		*/
		
		bool find(T targetData) {
			BSTNode<T>* current = root;
		
			// Do a standard BST search
			while(current != NULL && current->data != targetData) {
				if(targetData < current->data) {
					current = current->left;
				} else {
					current = current->right;
				}
			}
			
			// If we haven't reached the bottom of the tree, then we found it
			if(current != NULL) {
				return true;
			}
			
			return false;
		}

		int size() {
		  return amount;
		}

		int height() {
			return _height(this->root);
		}
};

// ###.##.###.###
const int TOTAL = 4;
const int DIGITS[TOTAL] = {3, 2, 3, 3};
const int DIGITS_SUM = 11;

/* 
	This class contains all the methods we are gonna use with IPs to sort the data 
*/
class Ip {
	string text;
	long long int number;

	public:
		Ip() {
			this->text = "";
			this->number = 0;
		}

		Ip(string text) {
			this->text = text;
			this->number = 0;

			stringstream word;
			int count = 0;
			int digitsSum = DIGITS_SUM;
			
      		/*
		    	Here we convert the IP to a long int number, so we can sort it. 
				Time complexity: O(n)
			    Space complexity: O(1)
		    */
			for(int i = 0; i <= text.size(); i++) {
				if(i == text.size() || text[i] == '.') {
					int digit = stoi(word.str());
					
					digitsSum -= DIGITS[count++];
					this->number += digit * pow(10, digitsSum);

					word.str("");
				} else {
					word << text[i];
				}
			}
		}

		long long int getNumber() {
			return this->number;
		}

		bool operator < (Ip anotherIp) {
			return this->getNumber() < anotherIp.getNumber();
		}

		bool operator > (Ip anotherIp) {
			return this->getNumber() > anotherIp.getNumber();
		}

		bool operator == (Ip anotherIp) {
			return this->getNumber() == anotherIp.getNumber();
		}

		bool operator >= (Ip anotherIp) {
			return this->getNumber() >= anotherIp.getNumber();
		}

		bool operator <= (Ip anotherIp) {
			return this->getNumber() <= anotherIp.getNumber();
		}

    bool operator != (Ip anotherIp) {
			return this->getNumber() != anotherIp.getNumber();
		}

	friend ostream &operator << (ostream &output, Ip ip) {
		output << ip.text;
		return output;
	}
};

/* 
	This class is the base of each of the messages
*/
class LogMessage {
	string month;
	string day;
	string time;
	Ip ip;
	string info;

	public:
		LogMessage(string month, string day, string time, string ip, string info) : ip(ip) {
			this->month = month;
			this->day = day;
			this->time = time;
			this->info = info;
		}

    Ip getIp(){
      return this->ip;
    }

    friend ostream &operator << (ostream &output, LogMessage logMessage) {
    	output << logMessage.month << " ";
		output << logMessage.day << " ";
  		output << logMessage.time << " ";
  		output << logMessage.ip << " ";
  		output << logMessage.info;
		
    	return output;
    }
};

/* 
	This class reads the unordered log file. 
	Arranges it using the comparison operators of the IP class. 
	Then prints the ordered data in a new file called ordered_logs.
*/
class LogMessagesManager {
  /* 
		Helper function for QuickSort, it partitions a vector using a pivot.
		Leaving smaller numbers at left, and biggers or equals at right
	    
		Time complexity: O(n)
	 	Space complexity: O(1)
	     
		Param: start and end vector indexes delimiters
		Return: index of the partition
	*/
	int partition(int start, int end) {
		// Choose the pivot to be at the end
		LogMessage pivot = logMessages[end];
		// The partition starts at the first index
		int partitionIndex = start;
		
		// Iterate from [start, end-1]
		for(int i=start; i<end; i++) {
			// We are seeing a smaller number, so we swap it. Then, increase the partition index
			if(logMessages[i].getIp() < pivot.getIp()) {
				swap(logMessages[i], logMessages[partitionIndex++]);
			}
		}

		// Swap the pivot at the end
		swap(logMessages[partitionIndex], logMessages[end]);
		return partitionIndex;
	}

	/* 
		Data sorting method: Quick Sort
	    
		(Worst case)
		Time complexity: O(n^2)
	 	Space complexity: O(n)
	     
		(Average case)
		Time complexity: O(nlogn)
		Space complexity: O(logn)
	
		Param: start and end vector indexes delimiters
		Return: nothing
	*/
	void quickSort(int start, int end) {
		if(start < end) {
			int partitionIndex = partition(start, end);
			quickSort(start, partitionIndex - 1);
			quickSort(partitionIndex + 1, end);
		}
	}

  	/* 
		Get the first index where the given Ip first appears (if it exists).
		If it does not exist, then return the index where it should be located.
	    
		Time complexity: O(log(n))
	  	Space complexity: O(1)
	     
		Param: Ip to search
		Return: the index where it first appears or where it would be located
	*/
	int getFirstIndexOfIp(Ip ip) {
		int start = 0;
		int end = logMessages.size();

		while(start < end) {
			int mid = (start + end) / 2;

			if(logMessages[mid].getIp() < ip) {
				start = mid + 1;
			}

			if(logMessages[mid].getIp() >= ip) {
				end = mid;
			}
		}

		return start;
	}

	public:
		vector<LogMessage> logMessages;
		
		LogMessagesManager() {
			
		}

		/* 
		  	Read the file given by the path and put it into a vector.
		
			Time complexity: O(n)
			Space complexity: O(1)
		    
			Param: inputFilePath to read.
			Return: nothing
		*/
		void read(string inputFilePath) {
			ifstream inputFile(inputFilePath);
			string month, day, time, ip, info;
			
			while(inputFile >> month >> day >> time >> ip) {
				inputFile.get();
				getline(inputFile, info);
	
				LogMessage logMessage(month, day, time, ip, info);
				logMessages.push_back(logMessage);
			}
	
			inputFile.close();
		}

    	void sort() {
			quickSort(0, logMessages.size() - 1);
		}

   		/* 
			Save the messages into an output file.  
	
			Time complexity: O(n)
			Space complexity: O(1)
				
			Param: inputFilePath to read.
			Return: nothing
		*/
		void save(string outputFilePath) {
			ofstream outputFile(outputFilePath);

			for(LogMessage logMessage : logMessages) {
				outputFile << logMessage << "\n";
			}

			outputFile.close();
		}

    /*
			Comparison of the IP's of each of the messages in the log.
			Putting the data in a vector called results and returning it full of data.

			Time complexity: O(n)
			Space complexity: O(n)
		    
			Param: startIp and endIp delimiters.
			Return: a vector "results" containing the IP's which are between the given range
		*/
		vector<LogMessage> getLogMessagesBetweenIp(Ip startIp, Ip endIp) {
			vector<LogMessage> results;

			int start = getFirstIndexOfIp(startIp);

			for(int i=start; i < logMessages.size() && logMessages[i].getIp() <= endIp; i++) {
				results.push_back(logMessages[i]);
			}
			
			return results;
		}
};

template <class T>
class SplayBSTNode {
public:
	T data;
	int readCount;
	SplayBSTNode<T>* left;
	SplayBSTNode<T>* right;
	SplayBSTNode<T>* parent;

    SplayBSTNode(T data) {
        this->data = data;
		this->readCount = 0;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }

	friend ostream &operator << (ostream &output, SplayBSTNode node) {
		output << node.data << "," << node.readCount;
		return output;
	}
};

template <class T>
class SplayTree {
	SplayBSTNode<T>* root;

	/* 
		Do a left rotation on a given node pointer 'p', such that 
		p's right child (x) takes p's place.
		For detailed visuals see: https://algorithmtutor.com/Data-Structures/Tree/Splay-Trees/
		
		Time complexity: O(1)
		Space complexity: O(1)
		
		Param: pointer to a node 'p' to perform the rotation 
		Return: no return
	*/
	
	void leftRotate(SplayBSTNode<T>* p) {
		SplayBSTNode<T>* x = p->right;
		
		// Move x's left to p's right
		p->right = x->left;
		// Then preserve the parent link
		if (x->left != NULL) {
			x->left->parent = p;
		}
	
		// Move x to the spot of p
		x->parent = p->parent;
		// Then preserve the parent link
		if (p->parent == NULL) {
			// If p has no parent then p was our previous root, so we update our root, affected by rotation
			this->root = x;
		} else if (p == p->parent->left) {
			// If p was a left child, we update its parent link
			p->parent->left = x;
		} else {
			// Do the same if it was a right child
			p->parent->right = x;
		}
	
		// Join p with x as a child, preserving parent link
		x->left = p;
		p->parent = x;
	}

	/* 
		Do a right rotation on a given node pointer 'p', such that 
		p's left child (x) takes p's place.
		For detailed visuals see: https://algorithmtutor.com/Data-Structures/Tree/Splay-Trees/
		
		Time complexity: O(1)
		Space complexity: O(1)
		
		Param: pointer to a node 'p' to perform the rotation 
		Return: no return
	*/
	
	void rightRotate(SplayBSTNode<T>* p) {
		SplayBSTNode<T>* x = p->left;
	
		// Move x's right to p's left
		p->left = x->right;
		// Then preserve the parent link
		if (x->right != NULL) {
			x->right->parent = p;
		}
		
		// Move x to the spot of p
		x->parent = p->parent;
		// Then preserve the parent link
		if (p->parent == NULL) {
			// If p has no parent then p was our previous root, so we update our root, affected by rotation
			this->root = x;
		} else if (p == p->parent->left) {
			// If p was a left child, we update its parent link
			p->parent->left = x;
		} else {
			// Do the same if it was a right child
			p->parent->right = x;
		}
		
		// Join p with x as a child, preserving parent link
		x->right = p;
		p->parent = x;
	}

	/* 
		Moves a given node to the top of its tree
	
		Time complexity: O(h) where h is the height of the tree.
		Time complexity - average: O(log(n)) where n is the number of nodes.
		Space complexity: O(1)
		
		Param: pointer to a node we want to move to the top 
		Return: no return
	*/
	
	void splay(SplayBSTNode<T>* node) {
		// If no parent, then we know it is already in the root, so we exit
		while (node->parent != NULL) {
			// If no grandparent, we know is a simple case
			if (node->parent->parent == NULL) {
				if (node == node->parent->left) {
					// Is a left child | zig
					rightRotate(node->parent);
				} else {
					// Is a right child | zag
					leftRotate(node->parent);
				}
			// It has grandparent, we know is a double case
			} else if (node == node->parent->left && node->parent == node->parent->parent->left) {
				// Is a left child, and parent is also a left child | zig-zig
				rightRotate(node->parent->parent);
				rightRotate(node->parent);
			} else if (node == node->parent->right && node->parent == node->parent->parent->right) {
				// Is a right child, and parent is also a right child | zag-zag
				leftRotate(node->parent->parent);
				leftRotate(node->parent);
			} else if (node == node->parent->right && node->parent == node->parent->parent->left) {
				// Is a right child, but parent is a left child | zag-zig
				leftRotate(node->parent);
				rightRotate(node->parent);
			} else {
				// Is a left child, but parent is a right child | zig-zag 
				rightRotate(node->parent);
				leftRotate(node->parent);
			}
		}
	}

	/* 
		Get the maximum node a given tree
	
		Time complexity: O(h) where h is the height of the given tree
		Space complexity: O(1)
		
		Param: no param
		Return: a pointer to our maximum node in the tree, or NULL if doesn't exists
	*/
	
	SplayBSTNode<T>* max(SplayBSTNode<T>* node) {
		SplayBSTNode<T>* current = node;
		
		while (current != NULL && current->right != NULL) {
			current = current->right;
		}
		
		return current;
	}

	/* 
		Joins two given trees into a single one
	
		Time complexity: O(h) where h is the height of the small tree.
		Space complexity: O(1)
		
		Param: a small tree pointer, and a big tree pointer, such that all elements
		in the small tree are less than or equal than the elements in the big tree
		Return: a node pointer to our joined tree
	*/
	
	SplayBSTNode<T>* join(SplayBSTNode<T>* smallTree, SplayBSTNode<T>* bigTree) {
		if (smallTree == NULL) {
			return bigTree;
		}
	
		if (bigTree == NULL) {
			return smallTree;
		}
	
		// Get the maximum node of the tree with the smaller values
		SplayBSTNode<T>* smallMax = this->max(smallTree);
		// Put that node at the top of its tree (the small tree)
		this->splay(smallMax);
		
		// Link the big tree to the right of the small tree, so we preserve BST property
		smallMax->right = bigTree;
		bigTree->parent = smallMax;
		
		return smallMax;
	}

	/* 
		Given a target node, this function splits target's node tree into
		two trees, one that has all elements less than or equal than our
		target node (small tree), and other that has all elements greater 
		than our target node (big tree). The root of our small tree will 
		be always NULL (i.e. without the target node).
	
		Time complexity: O(h) where h is the height of the tree that contains the target node.
		Space complexity: O(1)
		
		Param: a target node pointer reference, a small tree pointer reference 
		to store one tree, and a big tree pointer reference to store the other tree
		Return: no return
	*/
	
	void split(SplayBSTNode<T>*& target, SplayBSTNode<T>*& smallTree, SplayBSTNode<T>*& bigTree) {
		// Put our target node at the top of its tree
		this->splay(target);

		if (target->right != NULL) {
			// Separate the right part and put it into the big tree,
			// because all of the elements are greater than our target
			// (by BST definition)
			bigTree = target->right;
			bigTree->parent = NULL;
		} else {
			// If we don't have right part, then we don't have big tree either
			bigTree = NULL;
		}
	
		// Our small tree is going to be the part that remains after removing the right piece
		smallTree = target;
		smallTree->right = NULL;
	
		// Make it so that we cannot use target anymore
		target = NULL;
	}

	/* 
		Traverses the contents of our splay tree in a in-order fashion (ascending),
		and prints them when visiting.

		Time complexity: O(n) where n is the number of nodes below the given node pointer
		Space complexity: O(h) where h is the height of the tree starting from the given node pointer
		
		Param: node pointer to start traversing
		Return: no return
	*/

	void inOrder(SplayBSTNode<T>* node) {
		if(node == NULL) {
			return;
		}

		inOrder(node->left);
		cout << *node << " ";
		inOrder(node->right);
	}

	/* 
		Returns the size of the tree from a given node.

		Time complexity: O(n) where n is the number of nodes below the node pointer
		Space complexity: O(h) where h is the height of splay tree starting from the node pointer
		
		Param: pointer to a node
		Return: a integer with the size of the tree starting from that node
	*/

	int _size(SplayBSTNode<T>* node) {
		 if(node == NULL) {
			 return 0;
		 }
		
		 return 1 + this->_size(node->left) + this->_size(node->right);
	}

	/*
		Gets the height of a tree
		@Param: (SplayBSTNode<T>* root) tree root    
		Return: no return
		Time complexity: O(n)
		Space complexity: O(h) where h is the height of the tree, max complexity is O(n)
	*/

	int _height(SplayBSTNode<T>* root) {
		if(root == NULL) {
			return -1;
		}
		
		int leftHeight = _height(root->left);
		int rightHeight = _height(root->right);

		return std::max(leftHeight, rightHeight) + 1;
	}

public:
	SplayTree() {
		this->root = NULL;
	}



	/* 
		Searches a node with a specific target data into the tree, and then puts it
		at the top (using splay)

		Time complexity: O(h) where h is the height of the splay tree
		Space complexity: O(1)
		
		Param: target data of type T to be searched
		Return: returns true if found in the tree, or false otherwise
	*/

	SplayBSTNode<T>* find(SplayBSTNode<T>* nodo, T targetData) {

        if (nodo == nullptr || targetData == nodo->data) {
            return nodo;
        }

        if (targetData < nodo->data) {
            return find(nodo->left, targetData);
        }

        return find(nodo->right, targetData);

    }

    bool find(T targetData) {

        if (!this->root) {
            cout << "El árbol está vacío\n\n";
        }

        SplayBSTNode<T>* x = find(this->root, targetData);

        if (x) {
            splay(x);
            return true;
        }

        return false; 
        
    }

	/* 
		Inserts a node with a specific data into the tree, and then puts it
		at the top (using splay)

		Time complexity: O(h) where h is the height of the splay tree
		Space complexity: O(1)
		
		Param: new data of type T to be inserted
		Return: no return
	*/
	
	void insert(T newData) {
		SplayBSTNode<T>* current = this->root;
		SplayBSTNode<T>* parent = NULL;
	
		// Standard BST search
		while(current != NULL) {
			parent = current;
			
			if(newData <= current->data) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
	
		// Create node
		SplayBSTNode<T>* newSplayBSTNode = new SplayBSTNode<T>(newData);
	
		// Use parent to insert the new node
		if (parent == NULL) {
			this->root = newSplayBSTNode;
		} else if(newSplayBSTNode->data <= parent->data) {
			parent->left = newSplayBSTNode;
		} else {
			parent->right = newSplayBSTNode;
		}

		// Preserve parent link
		newSplayBSTNode->parent = parent;
		
		// Move new node to the top
		this->splay(newSplayBSTNode);
	}

	/* 
		Delete a node with a specific data into the tree.

		Time complexity: O(h) where h is the height of the splay tree
		Space complexity: O(1)
		
		Param: target data of type T to be deleted
		Return: no return
	*/

	void del(T targetData) {
		// Search for the node that points to that data
		SplayBSTNode<T>* current = this->root;
	
		// Do a standard BST search
		while(current != NULL && current->data != targetData) {
			if(targetData < current->data) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		 
		// We can't delete it if not found
		if (current == NULL) {
			return;
		}
		 
		SplayBSTNode<T>* smallTree;
		SplayBSTNode<T>* bigTree;
	
		// Split the tree in which we found our node into two parts
		split(current, smallTree, bigTree);
	
		// Remove the small tree's top link
		if (smallTree->left != NULL) {
			smallTree->left->parent = NULL;
		}
		 
		// After the removal join the trees again
		this->root = this->join(smallTree->left, bigTree);
		
		// Free memory
		delete(smallTree);
		smallTree = NULL;
	}

	/* 
		Prints the contents of splay tree in ascending order.

		Time complexity: O(n) where n is the number of nodes in splay tree
		Space complexity: O(h) where h is the height of splay tree
		
		Param: no param
		Return: no return
	*/

	void print() {
		this->inOrder(this->root);
		
		cout << "\n";
	}

	/* 
		Prints the contents of splay tree level by level in a single line.

		Time complexity: O(n) where n is the number of nodes in splay tree
		Space complexity: O(n) where n is the number of nodes in splay tree
		
		Param: no param
		Return: no return
	*/

	void levelByLevel() {
		queue<SplayBSTNode<T>*> queue;

		SplayBSTNode<T>* current = this->root;
		queue.push(current);

		while(!queue.empty() && current != NULL) {
			current = queue.front();
			cout << *current << " ";
			queue.pop();

			if(current->left != NULL) {
				queue.push(current->left);
			}

			if(current->right != NULL) {
				queue.push(current->right);
			}
		}

		cout << "\n";
	}

	/* 
		Returns the size of the splay tree

		Time complexity: O(n) where n is the number of nodes in splay tree
		Space complexity: O(h) where h is the height of splay tree
		
		Param: pointer to a node
		Return: a integer with the size of the tree starting from that node
	*/

	int size() {
		return _size(this->root);
	}

	int height() {
		return _height(this->root);
	}

};

double getDuration(clock_t start) {
	clock_t end = clock();
	return (end - start) / (double) CLOCKS_PER_SEC;
}

void printTreesInfo(BST<Ip> &bst, SplayTree<Ip> &splayTree) {
	cout << "BST Size: " << bst.size() << " ";
	cout << "BST Height: " << bst.height() << "\n";

	cout << "Splay Tree Size: " << splayTree.size() << " ";
	cout << "Splay Tree Height: " << splayTree.height() << "\n";

	cout << "\n";
}



int main() {
clock_t start;
	LogMessagesManager logMessagesManager1;
  	LogMessagesManager logMessagesManager2;
  	LogMessagesManager logMessagesManager3;
	LogMessagesManager logMessagesManager4;
  	LogMessagesManager logMessagesManager5;
	LogMessagesManager logMessagesManager6;


	// Read all files
	logMessagesManager1.read("unordered_logs.txt");
	vector<LogMessage> unorderedLogs = logMessagesManager1.logMessages;

	logMessagesManager2.read("ordered_logs_asc.txt");
	vector<LogMessage> orderedLogsAsc = logMessagesManager2.logMessages;

	logMessagesManager3.read("ordered_logs_desc.txt");
	vector<LogMessage> orderedLogsDesc = logMessagesManager3.logMessages;

	logMessagesManager4.read("repeated_logs.txt");
	vector<LogMessage> repeatedLogs = logMessagesManager4.logMessages;
  
  	logMessagesManager5.read("inversed_unordered_logs.txt");
	vector<LogMessage> inversedUnorderedLogs = logMessagesManager5.logMessages;

  	logMessagesManager6.read("one_repeated_log.txt");
	vector<LogMessage> oneRepeatedLogs = logMessagesManager6.logMessages;
  
  	BST<Ip> bst;
  	SplayTree<Ip> splayTree1;
  	SplayTree<Ip> splayTree2;
  	SplayTree<Ip> splayTree3;
    SplayTree<Ip> splayTree4;
  	SplayTree<Ip> splayTree5;
    SplayTree<Ip> splayTree6;

	cout << "===============Creating BST/SPT====================" << "\n\n";

	start = clock();
	for(LogMessage logMessage : unorderedLogs) {
		bst.create(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n";

  	start = clock();
	for(LogMessage logMessage : unorderedLogs) {
		splayTree1.insert(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n\n";

	// Creating more copies
	for(LogMessage logMessage : unorderedLogs) {
		splayTree2.insert(logMessage.getIp());
		splayTree3.insert(logMessage.getIp());
		splayTree4.insert(logMessage.getIp());
		splayTree5.insert(logMessage.getIp());
    	splayTree6.insert(logMessage.getIp());
	}



	cout << "===============1-Unordered Logs BST/SPT==============" << "\n\n";
	
	printTreesInfo(bst, splayTree1);
	
    start = clock();
	for(LogMessage logMessage : unorderedLogs) {
		bst.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n";

    start = clock();
	for(LogMessage logMessage : unorderedLogs) {
		splayTree1.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n\n";
	
	printTreesInfo(bst, splayTree1);

	cout << "=============2-Ordered Logs Asc BST/SPT=============" << "\n\n";

	printTreesInfo(bst, splayTree2);
	
    start = clock();
	for(LogMessage logMessage : orderedLogsAsc) {
		bst.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n";

    start = clock();
	for(LogMessage logMessage : orderedLogsAsc) {
		splayTree2.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n\n";

	printTreesInfo(bst, splayTree2);
	
	cout << "=============3-Ordered Logs Desc BST/SPT=============" << "\n\n";
	
	printTreesInfo(bst, splayTree3);
	
    start = clock();
	for(LogMessage logMessage : orderedLogsDesc) {
		bst.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n";

    start = clock();
	for(LogMessage logMessage : orderedLogsDesc) {
		splayTree3.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n\n";

	printTreesInfo(bst, splayTree3);
	
	cout << "===============4-Repeated Logs BST/SPT===============" << "\n\n";
	
	printTreesInfo(bst, splayTree4);
    
	start = clock();
	for(LogMessage logMessage : repeatedLogs) {
		bst.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n";

    start = clock();
	for(LogMessage logMessage : repeatedLogs) {
		splayTree4.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n\n";

	printTreesInfo(bst, splayTree4);
	
	cout << "==========5-Inversed Unordered Logs BST/SPT==========" << "\n\n";
	
	printTreesInfo(bst, splayTree5);
    
	start = clock();
  	for(LogMessage logMessage : inversedUnorderedLogs) {
		bst.find(logMessage.getIp());
	}
  	cout << getDuration(start) << "\n";
  
    start = clock();
	for(LogMessage logMessage : inversedUnorderedLogs) {
		splayTree5.find(logMessage.getIp());
	} 
  	cout << getDuration(start) << "\n\n";
  
	printTreesInfo(bst, splayTree5);
	
	cout << "=============6-One Repeated Log BST/SPT==============" << "\n\n";

	printTreesInfo(bst, splayTree6);
    
	int bstCount = 0;
	int splayCount = 0;

	start = clock();
	
  	for(LogMessage logMessage : oneRepeatedLogs) {
		if (bst.find(logMessage.getIp())) {
			bstCount++;
		}
	}




	cout << "Bst len:" <<bstCount << "\n";
  	cout << getDuration(start) << "\n";
  
    start = clock();
	
	for(LogMessage logMessage : oneRepeatedLogs) {
		if (splayTree6.find(logMessage.getIp())) {
			splayCount++;
		}
	} 
	

	cout <<  "Splay tree len:"<<splayCount << "\n";
  	cout << getDuration(start) << "\n\n";
  
	printTreesInfo(bst, splayTree6);
	
	return 0;
}


/*
References:
Moreno, P., Hernández, J. & Leyva, O. (2022). Act 2.3 - Actividad Integral estructura de datos lineales (Evidencia Competencia). Canvas. Retrieved from: https://experiencia21.tec.mx/courses/307981/assignments/9662644/submissions/166486

Leyva, O. (2022). Act 3.1 - Operaciones avanzadas en un BST. Retrieved from: https://experiencia21.tec.mx/courses/307981/assignments/9662649/submissions/228944

Moreno, P. (2022). Act 3.3 - Árbol Desplegado: Implementando un Splay Tree. Canvas. Retrieved from: https://experiencia21.tec.mx/courses/307981/assignments/9662658/submissions/166486

Greene, R. (2015). Explicitly initialize member which does not have a default constructor. Stack Overflow. Retrieved from: https://stackoverflow.com/questions/31488756/explicitly-initialize-member-which-does-not-have-a-default-constructor

Rooster, H. (2018). C++ copy object. Stack Overflow. Retrieved from: https://stackoverflow.com/questions/51896797/c-copy-object

Kostov, B. (2010). How to use clock() in C++. Stack Overflow. https://stackoverflow.com/questions/3220477/how-to-use-clock-in-c

Data structures: Binary Tree. (2014) mycodeschool. Youtube. Retrieved from: https://www.youtube.com/watch?v=H5JubkIy_p8

Ways to copy a vector in C++ (2022). GeeksForGeeks. Retrieved from: https://www.geeksforgeeks.org/ways-copy-vector-c/
*/