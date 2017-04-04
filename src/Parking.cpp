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
	readConnectionsFile();
	createGraphViewer();

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
	ull_int srcNodeID;
	ull_int dstNodeID;
	ull_int roadID;
	string line;

	file.open("connections.txt");

	if (!file) {
		cerr << "Unable to open file connections.txt";
		return;
	}

	while (getline(file, line)) {
		stringstream linestream(line);
		string data;

		linestream >> roadID;

		std::getline(linestream, data, ';');
		linestream >> srcNodeID;

		std::getline(linestream, data, ';');
		linestream >> dstNodeID;

		Vertex * srcNode = myGraph.getVertex(srcNodeID);
		Vertex * dstNode = myGraph.getVertex(dstNodeID);

		double dist = distanceBetweenVertex(srcNode, dstNode);

		myGraph.addEdge(srcNodeID, dstNodeID, dist, roads.find(roadID)->second);
		if ((roads.find(roadID)->second)->isTwoWays()) {
			myGraph.addEdge(dstNodeID, srcNodeID, dist,
					roads.find(roadID)->second);
		}



	}

	file.close();

}

void Parking::readNodesFile() {
	ifstream nodesFile;
	ull_int node_id;
	float lon;
	float lat;
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
		linestream >> lat;
		std::getline(linestream, data, ';');
		linestream >> lon;

		// valores inuteis
		// o melhor era ignorar

		std::getline(linestream, data, ';');

		std::getline(linestream, data, ';');



		myGraph.addVertex(new Vertex(node_id, lon, lat));

	}

	nodesFile.close();

}

void Parking::createGraphViewer() {
	myGV->setBackground("map.png");
	myGV->createWindow(1217, 825);
	myGV->defineVertexColor("blue");
	myGV->defineEdgeColor("black");

	ull_int node_id;
	int x;
	int y;
	for (Vertex * v : myGraph.getVertexSet()){
		node_id = v->getID();
		x = convertLongitudeToX(v->getLongitude());
		y= convertLatitudeToY(v->getLatitude());

		cout << node_id << endl << x << endl << y << endl;

		myGV->addNode(node_id,x,y);
		myGV->setVertexSize(node_id, 5);
		myGV->setVertexLabel(node_id, ".");
	}
	myGV->defineEdgeCurved(false);
	for (Vertex * v : myGraph.getVertexSet()){
		for (Edge * e : v->getAdj()) {
			if(!e->isInGraphViewer()) { //se ja estiver no myGV, nao voltamos a inseri-lo
				if(e->getRoad()->isTwoWays()) {
					myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(), EdgeType::UNDIRECTED);
					myGV->setEdgeLabel(e->getID(), "");
				} else {
					myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(), EdgeType::DIRECTED);
					myGV->setEdgeLabel(e->getID(), "");
				}
				e->setInGraphViewer();
			}
		}
	}



/*
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

double distanceBetweenVertex(Vertex * v1, Vertex * v2) {

	double lat1r = v1->getLatitude();
	double lon1r = v1->getLongitude();
	double lat2r = v1->getLatitude();
	double lon2r = v1->getLongitude();

	double u = sin((lat2r - lat1r) / 2);
	double v = sin((lon2r - lon1r) / 2);

	return 2.0 * earthRadiusKm
			* asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}



int Parking::convertLongitudeToX(double longitude) {
	cout << longitude << " " << minLng << " " << maxLng << " " << maxLng - minLng;

	return floor((longitude - minLng) * IMAGE_X / (maxLng - minLng));
}

int Parking::convertLatitudeToY(double latitude) {
	return IMAGE_Y-floor((latitude - minLat) * IMAGE_Y / (maxLat - minLat))-20;

}


