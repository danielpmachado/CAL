/*
 * DestPlaces.h
 *
 *  Created on: 05/04/2017
 *      Author: bibib
 */

#ifndef SRC_DESTPLACE_H_
#define SRC_DESTPLACE_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class DestPlace {
private:
	string place;
	Vertex * v;
public:
	DestPlace(string place, Vertex * v);
	string getPlace() const;
	Vertex * getNode() const;
	void setPlace(string place);
	void setNode(Vertex * v);
};



#endif /* SRC_DESTPLACE_H_ */
