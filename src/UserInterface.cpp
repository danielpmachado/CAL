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

	clearScreen();

	cout << TAB << "PRESS ENTER TO CALCULATE ROUTE" << endl;

	pauseScreen();
	clearScreen();

	cout << TAB << "Please chose the street your in..." << endl;


	vector<string> streetNames = p->getStreetNames();
	string street;


	for(string name : streetNames)
		cout << TAB << "-> "<< name << endl;

	// Aqui escolher a rua certa
	// Vou assumir que é Adams Street

	pauseScreen();
	clearScreen();

	street = "Pearl Street";  //MUDAR

	p->toogleStreetNodes(street);








}

