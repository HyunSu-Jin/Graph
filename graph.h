#include <iostream>
#include <list>
#include <string>
using namespace std;

class Edge {
private:
	int from;
	int to;
	int weight;
public:
	Edge(int from, int to) :from(from),to(to),weight(1){
	}
	Edge(int from, int to,int weight) :from(from), to(to), weight(weight) {
	}

	int getFrom() {
		return from;
	}
	int getTo() {
		return to;
	}
	int getWeight() {
		return weight;
	}
	string toString() {
		string str = "(" + to_string(from) + "," + to_string(to) + ") : " + to_string(weight);
		return str;
	}
};

class Graph {
	class AjacentNode {
	private:
		int vertex;
		int weight;
	public:
		AjacentNode(int vertex, int weight) {
			this->vertex = vertex;
			this->weight = weight;
		}
		int getVertex() {
			return vertex;
		}
		int getWeight() {
			return weight;
		}
	};

private:
	int* vertice;
	int vertexNum;
	Edge* edges;
	int edgeNum;
	list<AjacentNode>* ajacentList;

public:
	Graph(int* vertice, int vertexNum, Edge* edges, int edgeNum) {
		this->vertice = vertice;
		this->vertexNum = vertexNum;
		this->edges = edges;
		this->edgeNum = edgeNum;
		ajacentList = new list<AjacentNode>[vertexNum];
		for (int i = 0; i < edgeNum; i++) {
			Edge edge = edges[i];
			int from = edge.getFrom();
			int to = edge.getTo();
			int weight = edge.getWeight();
			ajacentList[from].push_back(AjacentNode(to, weight));
			ajacentList[to].push_back(AjacentNode(from, weight));
		}
	}

	void showVertice(){
		cout << "vertice : ";
		for (int i = 0; i < vertexNum; i++) {
			cout << vertice[i] << " ";
		}
		cout << endl;
	}

	void showEdges() {
		cout << "edges : ";
		for (int i = 0; i < edgeNum; i++) {
			cout << edges[i].toString() << " ";
		}
		cout << endl;
	}

	void printGraph() {
		showVertice();
		showEdges();
	}

	void showAjacentList() {
		for (int i = 0; i < vertexNum; i++) {
			list<AjacentNode> items  = ajacentList[i];
			cout << "from vertex , " << i << " : ";
			for (AjacentNode item : items) {
				cout << "(" << item.getVertex() << "," << item.getWeight() << ") ";
			}
			cout << endl;
		}
	}

	/*It costs Big O of vertexNum <=> O(V)*/
	bool hasEdge(int from, int to) {
		list<AjacentNode> items = ajacentList[from];
		for (AjacentNode item : items) {
			if (item.getVertex() == to) {
				return true;
			}
		}
		return false;
	}
};