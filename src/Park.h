#ifndef PARK_H_
#define PARK_H_

#include "Vertex.h"

class Park {
private:
	string type; //Parking Meter or Garage
	double price; //euros per hour
	Vertex * node; //point in the graph
	string name;
};

#endif
