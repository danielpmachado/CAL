/*
 * ParkType.h
 *
 *  Created on: 04/04/2017
 *      Author: bibib
 */

#ifndef SRC_PARKTYPE_H_
#define SRC_PARKTYPE_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class ParkType {
private:
	Vertex * v;
	string type; //meter or garage
	double price;
public:
	ParkType(Vertex * v, string type, double price);
	Vertex * getNode();
	string getType() const;
	double getPrice() const;
	void setNode(Vertex * v);
	void setType(string type);
	void setPrice(double price);
};



#endif /* SRC_PARKTYPE_H_ */
