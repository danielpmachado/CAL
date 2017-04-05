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


using namespace std;

class Parking {
private:
	Graph myGraph = Graph();
	map<long, Road*> roads;
	GraphViewer *myGV= new GraphViewer(1217, 825, false);
	vector<ParkType*>parkTypeSet;


public:
	Parking();
	virtual ~Parking();
	void readRoadsFile();
	void readConnectionsFile();
	void readNodesFile();
	void readParks();
	void createGraphViewer();
	int convertLongitudeToX(double longitude);
	int convertLatitudeToY(double latitude);
	double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;
	map<long, Road*> getRoads();
};


// auxiliary functions


#endif /* SRC_PARKING_H_ */
