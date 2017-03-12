#include <iostream>
#include <list>
#include <string>
#include <queue>

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

	void BFS(int root) {
		enum COLOR{
			WHITE, // It is not discovered
			GRAY, // It is discovered
			BLACK // It is ended
		};

		class Vertex {
		public:
			int idx;
			COLOR color;
			int distance;
			Vertex * predecessor;
		public:
			Vertex() {
			}
			Vertex(const Vertex & copy) {
				this->idx = copy.idx;
				this->color = copy.color;
				this->distance = copy.distance;
				this->predecessor = copy.predecessor;
			}
			Vertex(int idx, COLOR color) {
				this->idx = idx;
				this->color = color;
				distance = 9999;
				predecessor = NULL;
			}
		};

		Vertex * verticeArr = new Vertex[vertexNum];
		//initialize
		for (int i = 0; i < vertexNum; i++) {
			verticeArr[i].idx = i;
			verticeArr[i].color = WHITE;
			verticeArr[i].distance = 9999;
			verticeArr[i].predecessor = NULL;
		}
		verticeArr[root].color = GRAY;
		verticeArr[root].distance = 0;
		verticeArr[root].predecessor = NULL;
		
		queue<Vertex>  myQueue= queue<Vertex>();
		myQueue.push(verticeArr[root]);
		while (!myQueue.empty()) {
			Vertex * itemPtr = new Vertex(myQueue.front());
			cout << "poped" << (*itemPtr).idx << endl;
			myQueue.pop();
			list<AjacentNode> items = ajacentList[(*itemPtr).idx];
			for (AjacentNode ele : items) {
				Vertex &connectedItem = verticeArr[ele.getVertex()];
				if (connectedItem.color == WHITE) {
					connectedItem.color = GRAY;
					connectedItem.distance = (*itemPtr).distance + 1;
					connectedItem.predecessor = itemPtr;
					myQueue.push(connectedItem);
				}
			}
			(*itemPtr).color = BLACK;
		}
		for (int i = 0; i < vertexNum; i++) {
			if (verticeArr[i].predecessor != NULL) {
				cout << "edge : (" << verticeArr[i].idx << "," << (*(verticeArr[i].predecessor)).idx << ")" << endl;
			}
		}

	}
};