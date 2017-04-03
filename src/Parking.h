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
	GraphViewer *myGV= new GraphViewer(600, 600, false);

public:
	Parking();
	virtual ~Parking();
	void readRoadsFile();
	void readConnectionsFile();
	void readNodesFile();
	void createGraphViewer();
	void graphViewerNodes();
	void graphViewerEdges();
};


// auxiliary functions
double distanceBetweenVertex(Vertex * v1, Vertex * v2);
double convertLongitudeToX(long longitude);
double convertLatitudeToY(long latitude);


#endif /* SRC_PARKING_H_ */
