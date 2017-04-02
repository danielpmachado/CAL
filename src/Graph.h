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
#include "Road.h"
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
	double x, y;
	vector<Edge *> adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	bool inQueue;
public:

	Vertex(int id, double lon, double lat, double x, double y);
	friend class Graph;

	void addEdge(Vertex *dest, Road * road, double w);
	bool removeEdgeTo(Vertex *d);

	int getID() const;
	double getLongitude() const;
	double getLatitude() const;
	double getX() const;
	double getY() const;
	void setLongitude(double lon);
	void setLatitude(double lat);
	void setX(double x);
	void setY(double y);
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
	static int edgesID;
	int id;
	Vertex * dest;
	double weight;
	Road * road;
public:
	Edge(Vertex *d, Road * road, double w);
	double getWeight();
	int getID();
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
	Graph() {}
	bool addVertex(Vertex * v);
	bool addEdge(int sourcID, int destID, double w, Road * road);
	bool removeVertex(Vertex * v);
	bool removeEdge(Vertex * sourc, Vertex * dest);
	vector<Vertex * > getVertexSet() const;
	int getNumVertex() const;

	vector<Vertex*> dfs() const; //algoritmo que percorre grafo em perfundidade; retorna um vetor so com os vertices que sao alcançaveis
	void dfs(Vertex *v,vector<Vertex*> &res) const;//auxiliar de dfs() que altera o atributo "visited" dos vertices quando estes sao atingidos
	Vertex* getVertex(double lon, double lat) const;
	void resetIndegrees();
	vector<Vertex*> getSources() const;//retorna vetor com possiveis vertices origem usados como ponto de começo em algoritmos de ordenacao, ou seja, vertices com indegree 0
	vector<Vertex*> getPath(Vertex* origin, Vertex* dest);
	void dijkstraShortestPath(Vertex * v);
};



#endif /* SRC_GRAPH_H_ */
