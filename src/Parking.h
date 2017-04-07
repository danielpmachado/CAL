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
	Graph myGraph = Graph();
	map<long, Road*> roads;
	GraphViewer *myGV= new GraphViewer(5000, 3496, false);
	vector<ParkType*>parkTypeSet;
	vector<DestPlace *>destPlacesSet;
	vector<GasPump *>gasPumpSet;

public:
	Parking();
	virtual ~Parking();

	map<long, Road*> getRoads();
	GraphViewer * getGraphViewer();
	Graph getGraph();

	void readRoadsFile();
	void readConnectionsFile();
	void readNodesFile();
	void readParks();
	void readDestinations();
	void readGasPumps();

	void createGraphViewer();
	ParkType * getClosestPark(Vertex* src, Vertex * dest, double &finalDist);
	ParkType * getCheapestPark(Vertex * src, Vertex * dest, double distMax, double &finalDist);
	void drawPath(vector<Vertex*> path, string color);
	/**
	 * Planeia o caminho mais curto de um parque ao destino sem passar por bomba de gasolina
	 */
	void planGasPumpShortPath(Vertex * src, Vertex * dest);
	long calculateGasPumpShortPath(Vertex * src, Vertex * dest, GasPump * &finalGasPump,  ParkType * &finalParkType);
	ParkType * getParkType(Vertex * v);


	ParkType * planDirectShortPath(Vertex * src, Vertex * dest);
	ParkType * planDirectCheapestPath(Vertex * src, Vertex * dest, double maxDist);


	double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;
	void toogleStreetNodes(string street);

	vector<string> getStreetNames()const;
	vector<DestPlace *> getDestinations()const;
	vector<Vertex*> getStreetNodes(string street);


	Vertex * getVertex(long id);

};


// auxiliary functions


#endif /* SRC_PARKING_H_ */
