/*
 * GasPump.h
 *
 *  Created on: 07/04/2017
 *      Author: bibib
 */

#ifndef SRC_GASPUMP_H_
#define SRC_GASPUMP_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class GasPump {
private:
	Vertex * v;
public:
	GasPump (Vertex * v);
	Vertex * getNode() const;
	void setNode(Vertex * v);
};


#endif /* SRC_GASPUMP_H_ */
