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
	/*double maxLat = -10000;
	double minLat= 100000;
	double maxLng= -10000;
	double minLng= 10000;*/
	double maxLat = 40.69559;
	double minLat= 40.69026;
	double maxLng= -73.98061;
	double minLng= -73.99066;

public:
	Parking();
	virtual ~Parking();
	void readRoadsFile();
	void readConnectionsFile();
	void readNodesFile();
	void readParks();
	void readDestinations();
	void createGraphViewer();
	ParkType * getClosestPark(Vertex * dest);
	int convertLongitudeToX(double longitude);
	int convertLatitudeToY(double latitude);
	double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;
};


// auxiliary functions


#endif /* SRC_PARKING_H_ */
