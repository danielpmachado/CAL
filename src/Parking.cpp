/*
 * Parking.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#include "Parking.h"

Parking::Parking() {
	// TODO Auto-generated constructor stub

}

Parking::~Parking() {
	// TODO Auto-generated destructor stub
}

void Parking::readRoadsFile() {
	int id;
	string name;
	bool twoWays;


	ifstream roadsFile;

	roadsFile.open("roads.txt");

	if (!roadsFile) {
		cout << "Unable to open file roads.txt" << endl;
		return;
	}

	string line;


	while (getline(roadsFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> id;

		getline(linestream, data, ';');
		getline(linestream, data, ';');

		name =  data.substr(0, data.size()-1);

		linestream >> data;

		if(data == "False") twoWays = false;
		else twoWays = true;


		Road r(id,name, twoWays);
	}

	roadsFile.close();

}

