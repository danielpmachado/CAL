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
	 * @return true if the edge is successfully added false otherwise
	 *
	 */
	bool addEdge(int sourcID, int destID, double w, Road * road, bool real);

	/**
	 * @brief removes the vertex pointed bt v
	 *
	 * @param v pointer to the vertex to be removed
	 *
	 */
	bool removeVertex(Vertex * v);
	/**
	 * @brief removes the edge between the vertexs pointed by sourc and dest
	 *
	 * @param sourc pointer to the source vertex
	 *
	 * @param dest pointer to the dest vertex
	 *
	 * @return true if the edge was successfully removed, false otherwise
	 *
	 */
	bool removeEdge(Vertex * sourc, Vertex * dest);
	/**
	 * @brief returns a vector containing all the vertex of the graph
	 *
	 * @return VertexSet
	 *
	 */
	vector<Vertex *> getVertexSet();
	/**
	 * @brief return the total number of vertex in the graph
	 *
	 * @return number of vertex in the graph
	 *
	 */
	int getNumVertex() const;

	/**
	 * @brief algorithm to explore the graph in depth setting the parameter visited to true in all vertex analyzed
	 *
	 * @param origin pointer to the first vertex to be explored
	 *
	 */
	void dfs(Vertex * origin);
	/**
	 * @brief auxiliary method to the dfs algorithm, that is responsible for changing the visited parameter
	 *
	 * @param v pointer to the vertex to be analyzed
	 *
	 */
	void dfsAux(Vertex *v);
	/**
	 * @brief gets the vertex with the number identification id
	 *
	 * @param id id of the vertex to be returned
	 *
	 * @param pointer to the vertex with the specified id
	 *
	 */
	Vertex * getVertex(long id);
	/**
	 * @brief returns a vector containing all vertex that aren't the destination of any edge
	 *
	 * @return vector containing pointer to vertex with indegree =0
	 *
	 */
	vector<Vertex*> getSources();
	/**
	 * @brief returns a vector containing all vertex in the path from origin vertex to dest vertex
	 *
	 * @param origin pointer to the source vertex
	 *
	 * @param dest pointer to the destination vertex
	 *
	 * @return vector of pointer to the vertex between origin and dest
	 *
	 */
	vector<Vertex*> getPath(Vertex* origin, Vertex* dest);
	/**
	 * @brief algorithm to calculate the shortest path from a source vertex to all the other vertex
	 *  on the map by foot (assumes that every edge is bidirectional)
	 *
	 * @param v pointer to the origin vertex
	 *
	 */
	void dijkstraShortestPathByFoot(Vertex * v);
	/**
	 * @brief algorithm to calculate the shortest path from a source vertex to all the other vertex
	 *  on the map by car (only analyzes the edges that belong to the original map)
	 *
	 * @param v pointer to the origin vertex
	 *
	 */
	void dijkstraShortestPathByCar(Vertex * v);
	/**
	 * @brief returns all the vertex that are in the designated street using a dfs algorithm
	 *
	 * @param street street which vertex are returned
	 *
	 * @return vector containing the id's from the vertex of the designated street
	 *
	 */
	vector<long> searchStreetNodes(string street);
	/**
	 * @brief auxiliary method to searchStreetNodes
	 *
	 * @param v pointer to the vertex to be analyzed
	 *
	 * @param street street whose vertex id's are to be returned
	 *
	 * @param vector passed by reference where the id's of the vertex are saved
	 *
	 */
	void searchStreetNodesAux(Vertex * v, string street,
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
	/**
	 * @brief ptrVertex constructor
	 *
	 * @param v pointer to the vertex
	 *
	 */
	ptrVertex(Vertex * v);
	/**
	 * @brief gets the vertex pointer
	 *
	 * @return pointer to the vertex stored in ptrVertex
	 *
	 */
	Vertex * getNode() const;
	/**
	 * @brief changes the vertex pointed by v
	 *
	 * @param v pointer to ththe new vertex
	 *
	 */
	void setNode(Vertex * v);
	/**
	 * @brief overload of the < operator
	 *
	 * @param v2 const reference of the vertex to be compared
	 *
	 * @return true if the vertex pointed by v distance is higher than the vertex pointed by v2 distance
	 *
	 */
	bool operator<(const ptrVertex &v2) const;
};

class closestVertex {
private:
	Vertex * v;
	double dist;
public:
	/**
	 * @brief closestVertex constructor
	 *
	 * @param v pointer to  Vertex that represents a park
	 *
	 * @param dist distance to the park represented by vertex v
	 *
	 */
	closestVertex(Vertex * v, double dist);
	/**
	 * @brief gets the vertex pointer to the park
	 *
	 * @return pointer to vertex v
	 *
	 */
	Vertex * getNode() const;
	/**
	 * @brief changes the value pointed by v
	 *
	 * @param v pointer to the vertex that is going to replace v
	 *
	 */
	void setNode(Vertex * v);
	/**
		 * @brief gets the distance of v to the src vertex
		 *
		 * @return dist
		 *
		 */
	double getDist() const;
	/**
		 * @brief changes the distance of the vertex pointed by v
		 *
		 * @param dist new distance value
		 *
		 */
	void setDist(double dist);
	/**
		 * @brief overload of the < operator
		 *
		 * @param v2 vertex to be compared to v
		 *
		 * @return true if v distance is higher than v2 distance, false otherwise
		 *
		 */
	bool operator<(const closestVertex &v2) const;
};

class cheapestVertex {
private:
	Vertex * v;
	double price;
public:
	/**
		 * @brief cheapestVertex constructor
		 *
		 * @param v pointer to the vertex that represents a park
		 *
		 * @param price price of the the park represented by vertex poitner v
		 *
		 *
		 */
	cheapestVertex(Vertex * v, double price);
	/**
		 * @brief gets a pointer to the vertex v
		 *
		 * @return pointer to the vertex (car park)
		 *
		 */
	Vertex * getNode() const;
	/**
		 * @brief changes the value pointed by v
		 *
		 * @param v pointer to the vertex that is going to replace v
		 *
		 */
	void setNode(Vertex * v);
	/**
		 * @brief gets the price of the car park represented by v
		 *
		 * @return price
		 *
		 */
	double getPrice() const;
	/**
		 * @brief changes the price of the car park
		 *
		 * @param price new price
		 *
		 */
	void setPrice(double price);

	/**
		 * @brief overload of the < operator
		 *
		 * @param v2 vertex to be compared to v
		 *
		 * @return true if v price is higher than v2 price, false otherwise
		 *
		 */
	bool operator<(const cheapestVertex &v2) const;
};

#endif /* SRC_GRAPH_H_ */
