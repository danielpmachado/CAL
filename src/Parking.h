/*
 * Parking.h
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#ifndef SRC_PARKING_H_
#define SRC_PARKING_H_

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <climits>

#include "graphviewer.h"
#include "Graph.h"
#include "Road.h"
#include "utils.h"
#include "ParkType.h"
#include "DestPlace.h"
#include "GasPump.h"


using namespace std;

class Parking {
private:

	map<long, Road*> roads;
	GraphViewer *myGV;
	vector<ParkType*>parkTypeSet;
	vector<DestPlace *>destPlacesSet;
	vector<GasPump *>gasPumpSet;

public:
	Graph myGraph = Graph();
	/**
	 * @brief parking class Constructor
	 */
	Parking();

	/**
	 * @brief parking class destructor
	 */
	virtual ~Parking();

	/**
	 * @brief returns the map with roads id (key) and roads (value)
	 *
	 * @return map with roads and roads id
	 */
	map<long, Road*> getRoads();

	/**
	 * @brief returns the GraphViewer (myGV)
	 *
	 * @return GraphViewer (myGV)
	 */
	GraphViewer * getGraphViewer();

	/**
	 * @brief returns the graph (myGraph)
	 *
	 * @return  the graph (myGraph)
	 */
	Graph getGraph();

	/**
	 * @brief read the file with roads information
	 *
	 */
	void readRoadsFile();

	/**
	 * @brief read the file with connections information
	 *
	 */
	void readConnectionsFile();

	/**
	 * @brief read the file with nodes information
	 *
	 */
	void readNodesFile();

	/**
	 * @brief read the file with parks information
	 *
	 */
	void readParks();

	/**
	 * @brief read the file with destinations information
	 *
	 */
	void readDestinations();

	/**
	 * @brief read the file with gas pumps information
	 *
	 */
	void readGasPumps();

	/**
	 * @brief sets edges and nodes in GraphViewer and edits other atributes
	 *
	 */
	void createGraphViewer();

	/**
	 * @brief returns the closest park (ignoring gas pumps)
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param finalDist the distance between the beginning and the end
	 *
	 * @return the park type
	 */
	ParkType * getClosestPark(Vertex* src, Vertex * dest, double &finalDist);

	/**
	 * @brief returns the cheapest park
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param distMax the max distance you choose to drive by
	 *
	 * @param finalDist the distance between the beginning and the end
	 *
	 * @return the park type
	 */
	ParkType * getCheapestPark(Vertex * src, Vertex * dest, double distMax, double &finalDist);

	/**
	 * @brief paint in the map  the path with a specific color
	 *
	 * @param path the vertexes vector
	 *
	 * @param color the color that is going to be used to paint the map
   *
	 */
	void drawPath(vector<Vertex*> path, string color);

	/**
	 * @brief plans the shortest path between the park and the destiny passing by a gas bump
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @return the park
	 */
	ParkType * planGasPumpShortPath(Vertex * src, Vertex * dest);

	/**
	 * @brief calculates witch gas bump and park you are going by (the shortest path)
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param finalGasPump the chosen gas bump
	 *
	 * @param finalParkType the chosen park type
	 *
	 * @return a reference to the path
	 */
	long calculateGasPumpShortPath(Vertex * src, Vertex * dest, GasPump * &finalGasPump,  ParkType * &finalParkType);

	/**
	 * @brief plans the cheapest path passing by a gas bump
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param masDist the maximum distance that is chosen by the user
	 *
	 * @return the park type
	 */
	ParkType * planGasPumpCheapestPath(Vertex * src, Vertex * dest, double maxDist);

	/**
	 * @brief calculates witch gas bump and park you are going by (the cheapest path)
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param finalGasPump the chosen gas bump
	 *
	 * @param finalParkType the chosen park type
	 *
	 * @return a reference to the path
	 */
	long calculateGasPumpCheapestPath(Vertex * src, Vertex * dest, double maxDist, GasPump * &finalGasPump,  ParkType * &finalParkType);

	/*
	 * @brief return the ParkType object with the vertex v
	 *
	 * @param the vertex v
	 *
	 * @return the park type
	 */
	ParkType * getParkType(Vertex * v);

	/**
	 * @plans the shortest path to a park, without passing by a gas bump
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @return a park type
	 *
	 */
	ParkType * planDirectShortPath(Vertex * src, Vertex * dest);

	/**
	 * @plans the cheapest path to a park, without passing by a gas bump
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param maxDist the maximum distance that is chosen by the user
	 *
	 * @return a park type
	 */
	ParkType * planDirectCheapestPath(Vertex * src, Vertex * dest, double maxDist);

	/*
	 * @brief calculates the distance between 2 vertexes (in the image)
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @return the distance between 2 vertexes
   *
	 */
	double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;

	/*
	 * @brief toogles the street nodes in a specific street
	 *
	 * @param street the street passed by param
	 *
	 */
	void toogleStreetNodes(string street);

	/*
	 * @brief gets the street names
	 *
	 * @return a vector with the street names
	 *
	 */
	vector<string> getStreetNames()const;

	/*
	 * @brief gets the destinations
	 *
	 * @return a vector with the destinations
	 *
	 */
	vector<DestPlace *> getDestinations()const;

	/*
	 * @brief gets the street names
	 *
	 * @param street the street where you are working
	 *
	 * @return a vector with the street nodes
	 *
	 */
	vector<Vertex*> getStreetNodes(string street);


	/*
	 * @brief gets a vertex
	 *
	 * @param id the vertex id
	 *
	 * @return a vertex
	 *
	 */
	Vertex * getVertex(long id);

};

#endif /* SRC_PARKING_H_ */
