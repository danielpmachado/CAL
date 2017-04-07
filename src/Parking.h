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

#include "graphviewer.h"
#include "Graph.h"
#include "Road.h";
#include "utils.h"
#include "ParkType.h"
#include "DestPlace.h"


using namespace std;

class Parking {
private:
	Graph myGraph = Graph();
	map<long, Road*> roads;
	GraphViewer *myGV= new GraphViewer(5000, 3496, false);
	vector<ParkType*>parkTypeSet;
	vector<DestPlace *>destPlacesSet;

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

	void createGraphViewer();
	ParkType * getClosestPark(Vertex* src, Vertex * dest, double &finalDist);
	ParkType * getCheaperPark(Vertex * src, Vertex * dest, double distMax);
	void drawPath(vector<Vertex*> path, string color);
	void planDirectShortPath(Vertex * src, Vertex * dest);
	int convertLongitudeToX(double longitude);
	int convertLatitudeToY(double latitude);
	double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;
	void toogleStreetNodes(string street);
};


// auxiliary functions


#endif /* SRC_PARKING_H_ */
