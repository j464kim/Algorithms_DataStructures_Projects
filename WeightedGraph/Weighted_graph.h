#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

struct edge_weight{		// struct that contains two nodes and its weight
	double weight;
	int node_u;
	int node_v;
};

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n) { // Constructor , n vertices , no connection initially
	graph = new double*[n];				// create an array of pointers

	if (n < 0) {
		throw illegal_argument();
	}

	for (int i = 0; i < n; i++) {		
		graph[i] = new double[n];		// create two dimensional matrix
		for (int j = 0; j < n; j++) {
			if (i == j) {
				graph[i][j] = INF;	// node to itself has edge weight INF 
			} else {
				graph[i][j] = INF; // other nodes initial weight = INF
			}
		}
	}
	num_nodes = n;
	num_edges = 0;
}

Weighted_graph::~Weighted_graph() { // Destructor 
	for (int i = 0; i < num_nodes; i++) {	// delete an array of nodes attached to the node
		delete[] graph[i];
	}
	delete[] graph;					// delete an array of pointers
}

int Weighted_graph::degree(int u) const { // Returns the degree of the vertex n.
	int degreeCount = 0;
	if (u > num_nodes || u < 0) { // Throw an illegal_argument exception
							      // if the argument does not correspond to an existing vertex.
		throw illegal_argument();
	}
	else {
		for (int i = 0; i < num_nodes; i++) {
		if (graph[u][i] != INF) {
			degreeCount++;		// increment whenever an edge is found
		}
	}	
	return degreeCount;	
	}
}

int Weighted_graph::edge_count() const { // return the number of edges
	return num_edges; 
}

bool Weighted_graph::erase_edge(int i, int j) {
	if (i >= num_nodes || i < 0 || j >= num_nodes || j < 0) {
		throw illegal_argument();
	} else if (i == j) {				// node to itself
		return true;
	} else if (graph[i][j] == INF) {	// if no edge, return false
		return false;
	} else {	// edge exists and not node to itself, remove the edge and return true
		graph[i][j] = INF;
		graph[j][i] = INF;
		num_edges--;			// decrement num_edges

		return true;
	}
}

void Weighted_graph::clear_edges() {	// Removes all the edges from the graph.
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
			graph[i][j] = INF;
		}
	}
	num_edges = 0;		// set number of edge to zero
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	// If i or j are outside the range of [0..n-1] or 
	// if the weight d is less than or equal to zero, throw illegal_argument
	if (i >= num_nodes || i < 0 || j >= num_nodes || j < 0 || d <= 0) {
		throw illegal_argument();
	}
	else {					
		if (i == j) { 		// If i equals j and are in the graph, return false
			return false;
		} else if (graph[i][j] != INF) {// if already exists
			graph[i][j] = d;	//update the weight and return true
			graph[j][i] = d;
			return true;
		}
		else {					// if not exist
			graph[i][j] = d;	//update the weight and return true
			graph[j][i] = d;
			num_edges++;
			return true;		// Otherwise, add a new edge from vertex i to vertex j 
		}
	}
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {

	edge_weight struct_array[num_edges]; 	// create an array of the structs
	double total_weight = 0.0;
	int edges_tested = 0;

	int index = 0;
	for (int i = 0; i < num_nodes; i++) {
		for (int j = 0; j < num_nodes; j++) {
		
			if (i > j) {	 // loop through upper triangular matrix
				if (graph[i][j] != INF) { 	// Assign u,v and w from matrix to array of structs
					struct_array[index].weight = graph[i][j];
					struct_array[index].node_u = i; 
					struct_array[index].node_v = j;
					index++;
				}
			} 
		}
	}


	edge_weight tmp; // temporary struct needed to swap		
	// Bubble Sort algorithm | increasing order of weight
	for (int i = 1; i < num_edges; i++) { 
		for (int j = 0; j < num_edges-1; j++) {
			if (struct_array[j].weight > struct_array[j+1].weight) {
	        	tmp = struct_array[j];
	        	struct_array[j] = struct_array[j+1];
	        	struct_array[j+1] = tmp;
			}
		}	
	}

	Disjoint_set sets(num_nodes);

	for (int i = 0; i < num_edges; i++) {
		if (sets.find_set(struct_array[i].node_u) != sets.find_set(struct_array[i].node_v)) { // if the two vertext don't belong to the same set
			sets.union_sets(struct_array[i].node_u, struct_array[i].node_v);	// call union in Disjoint_sets
			total_weight += struct_array[i].weight; // increase the weight of unioned edge
		} 
		edges_tested++;	// add one edge tested
		if (sets.num_sets() == 1) { // if there is only one set left, return
			return std::pair<double, int>( total_weight, edges_tested );
		}
	} 

	return std::pair<double, int>( total_weight, edges_tested );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

#endif
