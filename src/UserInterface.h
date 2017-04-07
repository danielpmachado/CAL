/*
 * UserInterface.h
 *
 *  Created on: 05/04/2017
 *      Author: up201504570
 */

#ifndef SRC_USERINTERFACE_H_
#define SRC_USERINTERFACE_H_

#include <iostream>
#include <algorithm>

#include "Parking.h"
#include "utils.h"

using namespace std;

class UserInterface {
	Parking * p;
public:
	UserInterface(Parking * p);
	virtual ~UserInterface();
	void start();
	void displayRouteInformation(Vertex * src, Vertex * dst, ParkType * park)const;
};

#endif /* SRC_USERINTERFACE_H_ */
