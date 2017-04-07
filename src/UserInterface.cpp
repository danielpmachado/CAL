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

void UserInterface::start()const{

	clearScreen();

	cout << TAB << "PRESS ENTER TO CALCULATE ROUTE" << endl;

	pauseScreen();
	clearScreen();

	cout << TAB << "Please choose the street your in..." << endl;


	vector<string> streetNames = p->getStreetNames();


	for(string name : streetNames)
		cout << TAB << "-> "<< name << endl;

	// Aqui escolher a rua certa
	// Vou assumir que é Pearl Street

	pauseScreen();
	clearScreen();

	string street = "Pearl Street";



	p->toogleStreetNodes(street);
	vector<long> streetNodes = p->getStreetNodes(street);

	cout <<  TAB << "From the green nodes choose the closest to your position" << endl;

	for(long node: streetNodes)
		cout << TAB << "-> "<<  node << endl;



	// Escolher nó certo
	// vou assumir que é o 1

	int initial_position = 1;

	pauseScreen();
	clearScreen();

	vector<string> destinationNames = p->getDestinationNames();


	cout << TAB << "Where do you want to go?" << endl;

	for(string name : destinationNames){
		cout << TAB << "->" <<  name << endl;
	}

	pauseScreen();
	clearScreen();


	// Escolher destino certo
	// vou assumir que é o school

	string destination = "school";

	cout << TAB << "Park Option" << endl;

	cout << TAB << "-> Nearest  car park" << endl;
	cout << TAB << "-> Cheapest car park within a maximum distance" << endl;

	pauseScreen();
	clearScreen();

	bool nearest = true;
	bool cheapest;

	Vertex * src = p->getVertex(initial_position);
	Vertex * dst = p->getDestination(destination);
//
//	if(nearest)
//		planDirectShortPath(src, dest);






}

