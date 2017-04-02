/*
 * Graph.h
 *
 *  Created on: 01/04/2017
 *      Author: bibib
 */

#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <cmath>
#include <cstdint>
using namespace std;

class Edge;
class Graph;

#define NULL 0

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;


/*
 * CLASS VERTEX
 */
class Vertex {
	int id;
	double longitude, latitude;
	vector<Edge *> adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	bool inQueue;
public:

	Vertex(int id, double lon, double lat);
	friend class Graph;

	void addEdge(Vertex *dest, double w);
	bool removeEdgeTo(Vertex *d);

	int getID() const;
	double getLongitude() const;
	double getLatitude() const;
	void setLongitude(double lon);
	void setLatitude(double lat);
	void setID(int id);

	int getDist() const;
	int getIndegree() const;
	bool isInQueue() const {return inQueue;}
	Vertex* path;//vertice antecedente
};

/*
 * CLASS EDGE
 */
class Edge {
private:
	Vertex * dest;
	double weight;
public:
	Edge(Vertex *d, double w);
	double getWeight();
	friend class Graph;
	friend class Vertex;
};
/*
 * CLASS GRAPH
 */
class Graph {
private:
	vector<Vertex *> vertexSet;
	int numCycles;

public:
	bool addVertex(Vertex * v);
	bool addEdge(Vertex * sourc, Vertex * dest, double w);
	bool removeVertex(Vertex * v);
	bool removeEdge(Vertex * sourc, Vertex * dest);
	vector<Vertex * > getVertexSet() const;
	int getNumVertex() const;

	vector<Vertex*> dfs() const; //algoritmo que percorre grafo em perfundidade; retorna um vetor so com os vertices que sao alcan�aveis
	void dfs(Vertex *v,vector<Vertex*> &res) const;//auxiliar de dfs() que altera o atributo "visited" dos vertices quando estes sao atingidos
	Vertex* getVertex(double lon, double lat) const;
	void resetIndegrees();
	vector<Vertex*> getSources() const;//retorna vetor com possiveis vertices origem usados como ponto de come�o em algoritmos de ordenacao, ou seja, vertices com indegree 0
	vector<Vertex*> getPath(Vertex* origin, Vertex* dest);
	void dijkstraShortestPath(Vertex * v);
};



#endif /* SRC_GRAPH_H_ */
