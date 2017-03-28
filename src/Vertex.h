/*
 * Vertex.h
 */

#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include <vector>
#include "Graph.h"

class Edge;
class Graph;

/**
 * @brief Class Vertex
 * This class contains the vertex info, such as its edges, mindistance and previous vertex
 */

class Vertex {
	friend class Graph;
	Point info; /** <private member containing the coordinates of the vertex> */
	vector<Edge*> adj; /** <private member containing the adjacent vertexes> */
	double minDistance; /** <private member containing the minimum distance> distancia minima deste vertice ao primeiro vertice de todos (a origem) */
	Vertex* previous; /** <private member contains the previous vertex> */
public:
	/**
	 * @brief function that returns the point
	 * @return Point
	 */
	Point& getInfo();
	/**
	 * @brief function that returns the vector with all the adjacent edges
	 * @return vector of edges
	 */
	vector<Edge*>& getAdj();
	/**
	 * @brief Constructor of Vertex
	 * Initializes an empty Road
	 * @param point
	 */
	Vertex(const Point &in);
	/**
	 * @brief function that return the edge between this point and the other given as argument
	 * @param vertex
	 * @return edge
	 */
	Edge* getEdgeBetween(Vertex* dest) const;
	/**
	 * @brief function that return the road between this point and the other given as argument
	 * @param vertex
	 * @return edge
	 */
	Road* getRoadBetween(Vertex* dest) const;

	/**
	 * @brief function that return the distance
	 * @return double containg the distance
	 */
	double getDistance() const;
	/**
	 * @brief function  that returns the road's name
	 * @return string containing the road's name
	 */
	string getRoadName() const;

	/**
	 * @brief function that allows the overloading of the operator == , in order to compare two vertexes
	 * @param vertex
	 * @return true if equal, false if different
	 */
	bool operator==(const Vertex &rhs);
	/**
	 * @brief function that allows the overloading of the operator < , in order to compare two vertexes
	 * @param vertex
	 * @return true if smaller, false if bigger
	 */
	bool operator<(const Vertex &rhs);
	/**
	 * @brief function that allows the overloading of the operator == , in order to compare two vertexes
	 * @param vertex
	 * @return true if different, false if true
	 */
	bool operator!=(const Vertex &rhs);
};

#endif /* SRC_VERTEX_H_ */
