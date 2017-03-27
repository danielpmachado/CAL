/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include "Point.h"
#include "Vertex.h"
#include "Edge.h"

class Edge;
class Vertex;

/**
 * @brief Class graph
 * Graph class that holds the nodes and edges
 */
class Graph {
	vector<Vertex> vertexSet; /** < Vector of all vertexes*/
	Vertex* lastComputedSource; /** < Last computed source */
public:
	/**
	 * @brief Graph constructor
	 */
	Graph();

	/**
	 * @brief Gets number of vertexes in the graph
	 *
	 * @return Returns the vertex set size
	 */
	int getNumVertex() const;

	/**
	 * @brief Gets the vertex set
	 *
	 * @return Returns the vertex set
	 */
	vector<Vertex> getVertexSet() const;

	/**
	 * @brief Adds a vertex with info in
	 *
	 * @param in Vertex info
	 *
	 * @return Returns true on success.
	 */
	bool addVertex(const Point &in);

	/**
	 * @brief Adds a edge connected to sourc and dest, belonging to road.
	 *
	 * @param sourc Edge source
	 * @param dest Edge destination
	 * @param road Road the edge belongs to
	 *
	 * @return Returns true on success
	 */
	bool addEdge(const Point &sourc, const Point &dest, Road* road);

	/**
	 * @brief Gets the shortest path between source and goal.
	 *
	 * @param source Path beginning point
	 * @param goal Path ending point
	 *
	 * @return Returns the path as a list of pointer to vertexes.
	 */
	list<Vertex*> getShortestPath(Vertex* source, Vertex *goal);

	/**
	 * @brief Gets vertex from ID
	 *
	 * @param pointID ID of the point represented by the vertex
	 *
	 * @return Returns a pointer to the vertex
	 */
	Vertex* getVertexFromID(unsigned int pointID);

	/**
	 * @brief Gets vertex from road name.
	 *
	 * @param roadName road name
	 *
	 * @return Returns a pointer to the vertex
	 */
	Vertex* getVertexFromRoadName(const string &roadName);

	/**
	 * @brief Gets the vertex set size
	 *
	 * @return Returns the vertex set size
	 */
	unsigned int getVertexSetSize() const;

	/**
	 * @brief Gets the vertex in the index of the vertex set
	 *
	 * @param index Index in the vertex set vector
	 *
	 * @return Returns a pointer to the vertex in the position index of vertex set.
	 */
	Vertex* getVertexFromIndex(unsigned int index);
private:

	/**
	 * @brief Computes all paths from source
	 *
	 * @param source Source
	 */
	void computePaths(Vertex* source);

	/**
	 * @brief Resets pathfinding atributes
	 */
	void resetPathfinding();

	/**
	 * @brief
	 */
	Vertex* getApproximateVertex(const string &roadName);
};

#endif /* GRAPH_H_ */
