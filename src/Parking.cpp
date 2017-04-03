/*
 * Parking.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#include "Parking.h"

Parking::Parking() {

	readRoadsFile();
	readNodesFile();
	//readConnectionsFile();
	//createGraphViewer();

}

Parking::~Parking() {
	// TODO Auto-generated destructor stub
}

void Parking::readRoadsFile() {
	ifstream file;
	ull_int id;
	string name;
	bool twoWays;
	string line;

	file.open("roads.txt");
	if (!file) {
		cout << "Unable to open file roads.txt" << endl;
		return;
	}

	while (getline(file, line)) {
		stringstream linestream(line);
		string data;

		linestream >> id;

		getline(linestream, data, ';');
		getline(linestream, data, ';');

		name = data.substr(0, data.size() - 1);

		linestream >> data;

		twoWays = (data == "False") ? false : true;

		Road *newRoad = new Road(id, name, twoWays);
		roads.insert(pair<long, Road*>(id, newRoad));

	}

}

void Parking::readConnectionsFile() {
	ifstream file;
	file.open("connections.txt");

	if (!file.is_open())
		return;

	while (!file.eof()) {

		string buff;
		buff.clear();
		stringstream ss;

		int roadID, srcNodeID, destNodeID;

		if (getline(file, buff, ';')) {
			ss << buff;
			ss >> roadID;
			ss.clear();
		}

		if (getline(file, buff, ';')) {
			ss << buff;
			ss >> srcNodeID;
			ss.clear();
		}

		if (getline(file, buff)) {
			ss << buff;
			ss >> destNodeID;
			ss.clear();
		}


		Vertex * srcNode = myGraph.getVertex(srcNodeID);
		Vertex * destNode = myGraph.getVertex(destNodeID);

		// cálculo da distância está errado
		double dist = distanceBetweenVertex(srcNode, destNode);

		myGraph.addEdge(srcNodeID, destNodeID, dist,
				roads.find(roadID)->second);
		if ((roads.find(roadID)->second)->isTwoWays()) {
			myGraph.addEdge(destNodeID, srcNodeID, dist,
					roads.find(roadID)->second);
		}
	}

	file.close();

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


			// valores inuteis
			// o melhor era ignorar

			std::getline(linestream, data, ';');
			linestream >> long_rad;
			std::getline(linestream, data, ';');
			linestream >> lat_rad;


			myGraph.addVertex(new Vertex(node_id, long_degrees, lat_degrees, long_rad, lat_rad));


		}

		nodesFile.close();




}

void Parking::createGraphViewer() {

	myGV->createWindow(600, 600);
	myGV->defineVertexColor("blue");
	myGV->defineEdgeColor("black");

	/*
	 for (Vertex * v : myGraph.getVertexSet())
	 myGV->addNode(v->getID(), convertLongitudeToX(v->getLongitude()),
	 convertLatitudeToY(v->getLatitude()));


	 for(int i = 0; i < myGraph.getNumVertex(); i++) {
	 Vertex * v = myGraph.getVertexSet()[i];
	 for(int j = 0; j < v->getAdj().size(); j++) {
	 Edge * e = v->getAdj()[j];
	 if(!e->isInGraphViewer()) {
	 if(e->getRoad()->isTwoWays()) {
	 myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(), EdgeType::UNDIRECTED);
	 } else {
	 myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(), EdgeType::DIRECTED);
	 }
	 e->setInGraphViewer();
	 }
	 }
	 }
	 */

	myGV->rearrange();

}

// o cálcula da distância está mal

double distanceBetweenVertex(Vertex * v1, Vertex * v2) {
	return sqrt(pow((v1->getLongitude() - v2->getLongitude()), 2)
					+ pow((v1->getLatitude() - v2->getLatitude()), 2));
}

double convertLongitudeToX(long longitude) {
	return floor(((longitude - MIN_LON) * (IMAGE_Y)) / (MAX_LON - MIN_LON));
}

double convertLatitudeToY(long latitude) {
	return floor(((latitude - MIN_LAT) * (IMAGE_X)) / (MAX_LAT - MIN_LAT));
}

