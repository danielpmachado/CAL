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
	friend class Graph;
	/**
	 * @brief  Vertex constructor
	 *
	 * @param id unique number that identifies the vertex
	 *
	 * @param lon longitude of the point represented by the vertex in degrees
	 *
	 * @param lat latitude of the point represented by the vertex in degrees
	 *
	 */
	Vertex(long id, double lon, double lat);
	/**
	 * @brief adds a new edge to the vector adj
	 *
	 * @param dest pointer to the vertex at the other end of the edge
	 *
	 * @param road pointer to the road that is represented by the edge
	 *
	 * @param real true if it is possible for cars to go to in that direction false otherwise
	 */
	void addEdge(Vertex *dest, Road * road, double w, bool real);

	/**
	 * @brief removes the edge from the vector of edges
	 *
	 * @param d destination vertex from the edge to be removed
	 *
	 * @return true if the vertex was removed false otherwise
	 */
	bool removeEdgeTo(Vertex *d);

	/**
	 * @brief returns the vector containing the edges of the vertex
	 *
	 * @return vector adj
	 */
	vector<Edge *> getAdj();

	/**
	 * @brief returns vertex id
	 *
	 * @return  id
	 */
	long getID() const;

	/**
	 * @brief returns the longitude of the point represented by the vertex
	 *
	 * @return lon
	 */
	double getLongitude() const;

	/**
	 * @brief returns the latitude of the point represented by the vertex
	 *
	 * @return lat
	 */
	double getLatitude() const;

	/**
	 * @brief changes the value of the longitude
	 *
	 * @param lon new longitude
	 */
	void setLongitude(long lon);

	/**
	 * @brief changes the value of the latitude
	 *
	 * @param lat new latitude
	 */
	void setLatitude(long lat);

	/**
	 * @brief tells whether the vertex is accessible or not
	 *
	 * @return true if the vertex has been visited false otherwise
	 */
	bool isAccessible() const;

	/**
	 * @brief return distance of the vertex from a certain point
	 *
	 * @return dist
	 */
	long getDist() const;

	/**
	 * @brief changes distance value
	 *
	 * @param dist new distance
	 */
	void setDist(long dist);

	/**
	 * @brief returns the indegree of the vertex
	 *
	 * @return indegree
	 */
	int getIndegree() const;
	/**
	 * @brief whether the vertex is or isn't in queue
	 *
	 * @return true is vertex is in queue false otherwise
	 */
	bool isInQueue() const {
		return inQueue;
	}

	/**
	 * @brief return the edge to the destination vertex pointed by dst
	 *
	 * @param dst pointer to the destination vertex
	 *
	 * @return edge
	 */
	Edge * getEdgeToVertex(Vertex * dst);

	Vertex* path; //vertice antecedente
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
	/**
	 * @brief  Edge constructor
	 *
	 * @param d pointer to the destination vertex
	 *
	 * @param road pointer to the road that is represented by the vertex represented by the edge
	 *
	 * @param w weight of the edge in km (distance between source vertex and destination vertex)
	 *
	 * @param real true if it is possible for cars to go to in that direction false otherwise
	 *
	 */
	Edge(Vertex *d, Road * road, double w, bool real);
	/**
	 * @brief returns a pointer to the road that is represented by the edge
	 *
	 * @return road
	 */
	Road * getRoad() const;
	/**
	 * @brief returns a pointer to the destination vertex
	 *
	 * @return dst
	 */
	Vertex * getDest();
	/**
	 * @brief returns the weight of the edge in km (distance between source vertex and destination vertex)
	 *
	 * @return weight
	 */
	double getWeight();
	/**
	 * @brief returns the number that identifies the edge
	 *
	 * @return id
	 */
	int getID();

	/**
	 * @brief tells if the edge as been already insert in the graph viewer
	 *
	 * @return true if the edge is in the graph viewer, false otherwise
	 */
	bool isInGraphViewer();

	/**
	 * @brief sets the value of the parameter isInGraphViewer to true
	 *
	 */
	void setInGraphViewer();
	/**
	 * @brief tells if it is possible for cars to go in this edge direction
	 *
	 * @return true if it is possible for cars to drive in the edge direction, false otherwise
	 */
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
	/**
	 * @brief graph constructor
	 *
	 */
	Graph() {
	}

	/**
	 * @brief adds a new vertex to the graph
	 *
	 * @param v pointer to the vertex to be added
	 *
	 */
	bool addVertex(Vertex * v);

	/**
	 * @brief adds a new edge to the graph
	 *
	 * @param sourcID id of the source vertex
	 *
	 * @param destID id of the destination vertex
	 *
	 * @param w weight of the edge to be added, represents the distance between the src and dst vertex
	 *
	 * @param road pointer to the road represented by the edge
	 *
	 * @param real true if it is possible for cars to drive in the edge direction, false otherwise
	 *
	 * @return true if the edge is sucessfully added false otherwise
	 *
	 */
	bool addEdge(int sourcID, int destID, double w, Road * road, bool real);

	/**
	 * @brief removes the
	 *
	 * @param v pointer to the vertex to be added
	 *
	 */
	bool removeVertex(Vertex * v);
	bool removeEdge(Vertex * sourc, Vertex * dest);
	vector<Vertex *> getVertexSet();
	int getNumVertex() const;

	void dfs(Vertex * origin); //algoritmo que percorre grafo em profundidade; retorna um vetor so com os vertices que sao alcançaveis
	void dfsAux(Vertex *v); //auxiliar de dfs() que altera o atributo "visited" dos vertices quando estes sao atingidos
	Vertex* getVertex(long lon, long lat) const;
	Vertex * getVertex(long id);
	void resetIndegrees();
	vector<Vertex*> getSources(); //retorna vetor com possiveis vertices origem usados como ponto de começo em algoritmos de ordenacao, ou seja, vertices com indegree 0
	vector<Vertex*> getPath(Vertex* origin, Vertex* dest);
	void dijkstraShortestPathByFoot(Vertex * v);
	void dijkstraShortestPathByCar(Vertex * v);
	vector<long> searchStreetNodes(string street);
	void searchStreetNodes(Vertex * v, string street,
			vector<long>& streetVertex) const;
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

class cheapestVertex {
private:
	Vertex * v;
	double price;
public:
	cheapestVertex(Vertex * v, double price);
	Vertex * getNode() const;
	void setNode(Vertex * v);
	double getPrice() const;
	void setPrice(double price);
	bool operator<(const cheapestVertex &v2) const;
};

#endif /* SRC_GRAPH_H_ */
