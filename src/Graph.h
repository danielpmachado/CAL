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
#include "graphviewer.h"

using namespace std;

class Edge;
class Graph;

#define NULL 0

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;
const long LONG_INFINITY = LONG_MAX;


/*
 * CLASS VERTEX
 */
class Vertex {
	long id;
	double longitude, latitude;
	vector<Edge *> adj;
	bool visited;
	bool processing;
	int indegree;
	long dist; //em centimetros
	bool inQueue;
public:

	Vertex(long id, double lon, double lat);
	friend class Graph;

	void addEdge(Vertex *dest, Road * road, double w, bool real);
	bool removeEdgeTo(Vertex *d);
	vector<Edge *> getAdj();
	long getID() const;
	double getLongitude() const;
	double getLatitude() const;
	void setLongitude(long lon);
	void setLatitude(long lat);
	void setID(long id);
	bool isAccessible();
	long getDist() const;
	int getIndegree() const;
	bool isInQueue() const {return inQueue;}
	Edge * getEdgeToVertex(Vertex * dets);
	Vertex* path;//vertice antecedente
};

/*
 * CLASS EDGE
 */
class Edge {
private:
	static int edgesID;
	long id;
	Vertex * dest;
	double weight;
	Road * road;
	bool inGraphViewer; //true se ja foi inserido no GraphViewer
	bool real; //true se estiver no vetor adj de um vertice e fosse mesmo suposto estar lá. se estiver a false e uma aresta virtual pois a aresta e unidirecional, mas uma pessoa pode andar na rua no sentido que quiser
public:
	Edge(Vertex *d, Road * road, double w, bool real);
	Road * getRoad () const;
	Vertex * getDest();
	double getWeight();
	int getID();
	bool isInGraphViewer();
	void setInGraphViewer();
	bool isReal();
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
	bool addEdge(int sourcID, int destID, double w, Road * road, bool real);
	bool removeVertex(Vertex * v);
	bool removeEdge(Vertex * sourc, Vertex * dest);
	vector<Vertex * > getVertexSet();
	int getNumVertex() const;

	void dfs(Vertex * origin); //algoritmo que percorre grafo em profundidade; retorna um vetor so com os vertices que sao alcançaveis
	void dfsAux(Vertex *v);//auxiliar de dfs() que altera o atributo "visited" dos vertices quando estes sao atingidos
	Vertex* getVertex(long lon, long lat) const;
	Vertex * getVertex(long id);
	void resetIndegrees();
	vector<Vertex*> getSources();//retorna vetor com possiveis vertices origem usados como ponto de começo em algoritmos de ordenacao, ou seja, vertices com indegree 0
	vector<Vertex*> getPath(Vertex* origin, Vertex* dest);
	void dijkstraShortestPathByFoot(Vertex * v);
	void dijkstraShortestPathByCar(Vertex * v);
	vector<long> searchStreetNodes(string street);
	void searchStreetNodes(Vertex * v, string street, vector<long>& streetVertex)const;
};

struct vertex_greater_than {
    bool operator()(Vertex * a, Vertex * b) const {
        return a->getDist() > b->getDist();
    }
};

class ptrVertex {
private:
	Vertex * v;
public:
	ptrVertex(Vertex * v);
	Vertex * getNode() const;
	void setNode(Vertex * v);
	bool operator<(const ptrVertex &v2) const;
};

class closestVertex {
private:
	Vertex * v;
	double dist;
public:
	closestVertex(Vertex * v, double dist);
	Vertex * getNode() const;
	void setNode(Vertex * v);
	double getDist() const;
	void setDist(double dist);
	bool operator<(const closestVertex &v2) const;
};

#endif /* SRC_GRAPH_H_ */
