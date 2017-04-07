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
	// Vou assumir que � Pearl Street

	pauseScreen();
	clearScreen();

	string street = "Pearl Street";



	p->toogleStreetNodes(street);
	vector<long> streetNodes = p->getStreetNodes(street);

	cout <<  TAB << "From the green nodes choose the closest to your position" << endl;

	for(long node: streetNodes)
		cout << TAB << "-> "<<  node << endl;



	// Escolher n� certo
	// vou assumir que � o 1


	Vertex * src = p->getVertex(streetNodes.at(0));

	pauseScreen();
	clearScreen();

	vector<DestPlace *> destinations= p->getDestinations();


	cout << TAB << "Where do you want to go?" << endl;

	for(DestPlace * dst : destinations){
		cout << TAB << "->" <<  dst->getPlace() << endl;
	}



	pauseScreen();
	clearScreen();


	// Escolher destino certo
	// vou assumir que � o school

	Vertex * dst = destinations.at(0)->getNode();



	cout << TAB << "Park Option" << endl;

	cout << TAB << "-> Nearest  car park" << endl;
	cout << TAB << "-> Cheapest car park within a maximum distance" << endl;

	pauseScreen();
	clearScreen();

	// SE ESCOLHER O PARQUE MAIS PERTO CHAMAR ESTE CODIGO

	// -------------------------------------------------------
	//ParkType * car_park = p->planDirectShortPath(src, dst);

	//if(car_park != NULL) displayRouteInformation(src,dst,car_park);

	// ---------------------------------------------------------


	// SE ESCOLHER O PARQUE MAIS BARATO CHAMAR ESTE C�DIGO

	// ----------------------------------------------

	cout << TAB << "Max distance between the Car Park and your Destination" << endl;
	cout << TAB << "-> 50 m" << endl;
	cout << TAB << "-> 100 m" << endl;
	cout << TAB << "-> 200 m" << endl;
	cout << TAB << "-> 300 m" << endl;
	cout << TAB << "-> 400 m" << endl;

	// faz a tua cena Daniel

	pauseScreen();
	clearScreen();


	long max_distance = 200;

	ParkType * car_park = p->planDirectCheapestPath(src,dst, max_distance);

	if(car_park != NULL) displayRouteInformation(src,dst,car_park);

	// -----------------------------------------------------------


}


void UserInterface::displayRouteInformation(Vertex * src, Vertex * dst, ParkType * park)const {

	vector<Vertex *> pathToPark = p->getGraph().getPath(src, park->getNode());

	p->drawPath(pathToPark, "red");

	cout	<< "Total distance: "
			<< dst->getDist() << " m   ( "<< park->getNode()->getDist()
			<< " by car and " << dst->getDist() - park->getNode()->getDist()
			<< " by foot )" << endl;


	cout << "Type of Park: ";
	if(park->getType() == "meter") {
		cout << "Parking meter\n";
	} else
		cout << "Garage\n";

	cout << "Price: " << park->getPrice() << " euros/h\n";

}
