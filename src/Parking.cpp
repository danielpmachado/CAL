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

		cout << roadID << endl << srcNodeID << endl << dstNodeID << endl;

	}

	file.close();

}

void Parking::readNodesFile() {
	ifstream nodesFile;
	ull_int node_id;
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
		std::getline(linestream, data, ';');

		// valores inuteis
		// o melhor era ignorar

		std::getline(linestream, data, ';');
		linestream >> long_rad;
		std::getline(linestream, data, ';');
		linestream >> lat_rad;

		myGraph.addVertex(new Vertex(node_id, long_rad, lat_rad));

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
	graphViewerNodes();
	graphViewerEdges();
	myGV->rearrange();

}

void Parking::graphViewerNodes() {
	myGV->createWindow(600, 600);
	myGV->defineVertexColor("blue");
	myGV->defineEdgeColor("black");
	for(int i = 0; i < myGraph.getNumVertex(); i++) {
		Vertex * v = myGraph.getVertexSet()[i];
		myGV->addNode(v->getID(),convertLongitudeToX(v->getLongitude()),convertLatitudeToY(v->getLatitude()));
	}
}
void Parking::graphViewerEdges() {
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

double convertLongitudeToX(long longitude) {
	return floor(((longitude - MIN_LON) * (IMAGE_Y)) / (MAX_LON - MIN_LON));
}

double convertLatitudeToY(long latitude) {
	return floor(((latitude - MIN_LAT) * (IMAGE_X)) / (MAX_LAT - MIN_LAT));
}

