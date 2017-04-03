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

#include "Road.h";
#include "utils.h"


using namespace std;

class Parking {
public:
	Parking();
	virtual ~Parking();
	void readRoadsFile();
	void readConnectionsFile();
	void readNodesFile();
};

#endif /* SRC_PARKING_H_ */
