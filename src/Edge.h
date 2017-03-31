/*
 * Edge.h
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <vector>
#include "Graph.h"
#include "Road.h"


class Vertex;
class Graph;

/**
 * @brief Class Edge.
 * Class that represents an Edge belonging to a Graph.
 * It has source and destination vertexes, a unique identification
 * number, a pointer to the Road it belongs to and the distance
 * between source and destination.
 */
class Edge {
private:
	Vertex* source; /** < Source vertex */
	Vertex* destination; /** < Destination vertex*/
	Road* road; /** <Road the edge belongs to */
	static unsigned int nextEdgeID; /** < Next edge identification number*/
	unsigned int edgeID; /** < Unique edge identification number*/
	double distance; /** <Distance between source and destination */
public:
	/**
	 * @brief Edge constructor
	 *
	 * @param s Pointer to Edge source
	 * @param d Pointer to Edge destination
	 * @param road Pointer to road the Edge belongs to
	 */
	Edge(Vertex* s, Vertex *d, Road* road);

	/**
	 * @brief Gets the source Vertex
	 *
	 * @return Pointer to source Vertex
	 */
	Vertex* getSource() const;

	/**
	 * @brief Gets the destination Vertex
	 *
	 * @return Pointer to destination Vertex
	 */
	Vertex* getDestination() const;

	/**
	 * @brief Gets the Edge ID
	 *
	 * @return Returns the Edge ID
	 */
	unsigned int getEdgeID() const;

	/**
	 * @brief Gets the road the Edge belongs to
	 *
	 * @return Pointer to the road the Edge belongs to
	 */
	Road* getRoad() const;

	/**
	 * @brief Gets the road name the Edge belongs to
	 *
	 * @return Name of the road the Edge belongs to
	 */
	string getRoadName() const;
	friend class Graph;
	friend class Vertex;
};

#endif /* SRC_EDGE_H_ */
