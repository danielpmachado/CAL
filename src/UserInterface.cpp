/*
 * UserInterface.cpp
 *
 *  Created on: 05/04/2017
 *      Author: up201504570
 */

#include "UserInterface.h"

UserInterface::UserInterface(Parking * p) {
	this->p = p;

}

UserInterface::~UserInterface() {
	// TODO Auto-generated destructor stub
}

void UserInterface::start(){

	cout << TAB << "PRESS ENTER TO CALCULATE ROUTE" << endl;


	cout << TAB << "Please chose the street your in..." << endl;

	map<long, Road*> roads = p->getRoads();
	map<long, Road*>::iterator it;

	for(it = roads.begin(); it != roads.end(); it++){
		//cout << it->second->getName() << endl;
	}


}

