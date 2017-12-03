Project Descriptions

1. Dynamic Stack 

The goal of this project is to design and implement a dynamic stack data structure. 
A stack is a data structure that stores elements in an ordered list and allows insertions and deletions at one end only (the top of stack) in O(1) time. A dynamic stack is able to increase its size if necessary in O(n).

2. Dynamic Double-ended Queue

The goal of this project is to design and implement a dynamic deque data structure. 
A deque is a queue that stores elements in an ordered list and allows insertions and deletions at both ends in O(1) time and is able to increase its size if necessary in O(n).

3. Open Addressing - Linear Hashing

The goal of this project is to design and implement a hash table data structure. 
A hash table is a data structure where values are mapped to an entry of a table using a hash function. 
For this project, linear probing is used to resolve collision. 
The advantage of the hash table data structure is that it can achieve constant expected time for insert and remove operations (O(1)).

4. Open Addressing - Double Hashing

The goal of this project is to design and implement a hash table data structure.
A hash table is a data structure where values are mapped to a position in a table using a hash function. 
For this project, you will implement a double hash table in which collisions are resolved using double hashing. 
We will use hash functions sufficiently even so as to allow all expected constant-time operations to be O(1).

5. Leftist Node

Essentially, a leftist heap is very similar to an AVL tree but rather than height it uses the null-path length of a node; that is, the minimum path length from the node to a descendent that is not a full node. 
The name leftist comes from the fact that, in leftist heap, the left subtree of each node is usually taller than the right subtree.
 
 
6. Trie Tree

In this project we implement a trie data structure using recursive programming. 
A trie is a 26-ary tree where the root node represents an empty string “” and if the kth (k going from 0 to 25) sub-tree is not a null sub-tree, it represents a string that is the concatenation of string represented by the parent and the kth letter of the alphabet (where a is the 0th letter, b is the 1st letter, and so on). 
Each node may or may not indicate that it is a terminal entry for a word. 
While a trie could be used to store hyphenated and capitalized words together with those with apostrophes, I restricted it to words made up of the twenty-six letters of the English alphabet.

7. Minimum Spanning Tree (MST) - Kruskal's Algorithm

In this project, we implement the Minimum Spanning Tree (MST) of a weighted undirected graph, using the Kruskal’s algorithm. 
We consider the nodes in the graph to be numbered from 0 to n – 1. 
This means a graph with 4 nodes, has nodes named 0, 1, 2 and 3. 
Each edge has a weight (a positive number and of double type) associated with it.
To build the minimum spanning tree T, the Kruskal’s algorithm adds one edge to the T (initialized with an empty graph) in each step. To make sure that this procedure does not form loops in the tree, I need to keep track of the connected components of T. Disjoint sets is a well-known data structure for grouping n elements (nodes) into a collection of disjoint sets (connected components). In this project, the goal is to implement the disjoint sets data structure using linked lists.