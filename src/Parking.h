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


using namespace std;

class Parking {
private:
	Graph myGraph = Graph();
	map<long, Road*> roads;
	GraphViewer *myGV= new GraphViewer(800, 1000, false);

	double maxLat = -10000;
	double minLat= 100000;
	double maxLng= -10000;
	double minLng= 10000;

public:
	Parking();
	virtual ~Parking();
	void readRoadsFile();
	void readConnectionsFile();
	void readNodesFile();
	void createGraphViewer();


	int convertLongitudeToX(double longitude);
	int convertLatitudeToY(double latitude);
	void updateCoordinates();
};


// auxiliary functions

double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;

#endif /* SRC_PARKING_H_ */
