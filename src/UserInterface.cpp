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

	getchar();


	cout << TAB << "Please chose the street your in..." << endl;

	map<long, Road*> roads = p->getRoads();
	map<long, Road*>::iterator it;
	vector<string> streetNames;
	vector<long> streetNodes;
	string street;

	for(it = roads.begin(); it != roads.end(); it++){
		if(it->second->getName()!= "")
			streetNames.push_back(it->second->getName());
	}

	sort(streetNames.begin(), streetNames.end());
	streetNames.erase(unique(streetNames.begin(), streetNames.end()), streetNames.end());

	for(string name : streetNames)
		cout << TAB << "-> "<< name << endl;

	// Aqui escolher a rua certa
	// Vou assumir que é Adams Street

	street = "Pearl Street";

	p->toogleStreetNodes(street);








}

