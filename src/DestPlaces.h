/*
 * DestPlaces.h
 *
 *  Created on: 05/04/2017
 *      Author: bibib
 */

#ifndef SRC_DESTPLACES_H_
#define SRC_DESTPLACES_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class DestPlaces {
public:
	string place;
	Vertex * v;
private:
	DestPlaces(string place, Vertex * v);
	string getPlace() const;
	Vertex * getNode() const;
	void setPlace(string place);
	void setNode(Vertex * v);
};



#endif /* SRC_DESTPLACES_H_ */
