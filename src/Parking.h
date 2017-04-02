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


using namespace std;

class Parking {
public:
	Parking();
	virtual ~Parking();
	void readRoadsFile();
};

#endif /* SRC_PARKING_H_ */
