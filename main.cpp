#include <iostream>
#include "graph.h"

int main() {
	int vertices[] = { 0,1,2,3,4};
	Edge edges[] = { Edge(0,1),Edge(0,2),Edge(1,2),Edge(2,3),Edge(1,3),Edge(1,4) };
	Graph graph = Graph(vertices,sizeof(vertices)/sizeof(int),edges,sizeof(edges)/sizeof(Edge));
	//graph.printGraph();
	graph.showAjacentList();
	cout << "from 0 to 3 edge exist?" << endl;
	if (graph.hasEdge(0, 3)) {
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;
	}
	graph.BFS(0);
}