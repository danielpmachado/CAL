/*
 * Parking.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#include "Parking.h"

Parking::Parking() {
	readRoadsFile();
	readConnectionsFile();
	readNodesFile();

}

Parking::~Parking() {
	// TODO Auto-generated destructor stub
}

void Parking::readRoadsFile() {
	ifstream roadsFile;
	ull_int id;
	string name;
	bool twoWays;
	string line;


	roadsFile.open("roads.txt");
	if (!roadsFile) {
		cout << "Unable to open file roads.txt" << endl;
		return;
	}


	while (getline(roadsFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> id;

		getline(linestream, data, ';');
		getline(linestream, data, ';');

		name = data.substr(0, data.size() - 1);

		linestream >> data;

		if (data == "False")
			twoWays = false;
		else
			twoWays = true;

	}

	roadsFile.close();

}

void Parking::readConnectionsFile() {
	ifstream connectionsFile;
	ull_int node_1;
	ull_int node_2;
	ull_int road;
	string line;


	connectionsFile.open("connections.txt");

	if (!connectionsFile) {
		cerr << "Unable to open file connections.txt";
		return;
	}

	while (getline(connectionsFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> road;

		std::getline(linestream, data, ';');
		linestream >> node_1;

		std::getline(linestream, data, ';');
		linestream >> node_2;

	}

	connectionsFile.close();
}

void Parking::readNodesFile() {
	ifstream nodesFile;
	ull_int node_id;
	float long_degrees;
	float lat_degrees;
	float long_rad;
	float lat_rad;
	string line;


	nodesFile.open("nodes.txt");

	if (!nodesFile) {
		cerr << "Unable to open file nodes.txt";
		return;
	}

	while (getline(nodesFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> node_id;

		std::getline(linestream, data, ';');
		linestream >> lat_degrees;
		std::getline(linestream, data, ';');
		linestream >> long_degrees;
		std::getline(linestream, data, ';');
		linestream >> long_rad;
		std::getline(linestream, data, ';');
		linestream >> lat_rad;


		cout << node_id << endl << lat_degrees << endl << long_degrees << endl << long_rad << endl << lat_rad << endl;

	}

	nodesFile.close();
}

