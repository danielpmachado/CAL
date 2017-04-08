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
	void writeStreetName(int i, vector<string> streetNames);
	void writeNodes(int i, vector<Vertex *> streetNodes);
	void writeDestiny(int i, vector<DestPlace *> destinations);
	Vertex* chooseVertex(string street);
	string chooseStreetName();
	Vertex * chooseDestiny();
	void writePreference(int i);
	int choosePreference();
	void writeMaxDistance(int i);
	int chooseMaxDistance();
	bool wantGasoline();
	void writeGasoline(int i);
};

#endif /* SRC_USERINTERFACE_H_ */
