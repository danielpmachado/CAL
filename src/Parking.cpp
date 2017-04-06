/*
 * Parking.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#include "Parking.h"

Parking::Parking() {
	readNodesFile();
	readRoadsFile();
	readConnectionsFile();
	createGraphViewer();
	readParks();
	readDestinations();
	myGV->rearrange();
	ParkType * p = getClosestPark(myGraph.getVertex(231598396), myGraph.getVertex(42481892));
	cout << p->getNode()->getID();
}

Parking::~Parking() {
	// TODO Auto-generated destructor stub
}

map<long, Road*> Parking::getRoads() {
	return roads;
}

GraphViewer * Parking::getGraphViewer() {
	return myGV;
}

Graph Parking::getGraph() {
	return myGraph;
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

		name = data.substr(0, data.size());

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

		myGraph.addEdge(srcNodeID, dstNodeID, dist, roads.find(roadID)->second, true);
		if ((roads.find(roadID)->second)->isTwoWays()) {
			myGraph.addEdge(dstNodeID, srcNodeID, dist, roads.find(roadID)->second, true);
		} else {
			myGraph.addEdge(dstNodeID, srcNodeID, dist, roads.find(roadID)->second, false);
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

void Parking::readParks() {
	ifstream parksFile;
	string line;
	ull_int node_id;
	string type;
	double price;
	parksFile.open("parkingPlaces.txt");

	if (!parksFile) {
		cerr << "Unable to open file parkingPlaces.txt";
		return;
	}
	while (getline(parksFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> node_id;

		getline(linestream, data, ';');
		getline(linestream, data, ';');
		type = data.substr(0, data.size());
		linestream >> price;
		ParkType * p = new ParkType(myGraph.getVertex(node_id), type, price);
		parkTypeSet.push_back(p);
		if (type == "meter") {
			myGV->setVertexIcon(node_id, "meterIcon.png");
		} else {
			myGV->setVertexIcon(node_id, "garageIcon.png");
		}
	}

	parksFile.close();
}

void Parking::readDestinations() {
	ifstream destFile;
	string line;
	ull_int node_id;
	string place;
	destFile.open("destination.txt");

	if (!destFile) {
		cerr << "Unable to open file destination.txt";
		return;
	}
	while (getline(destFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> node_id;

		getline(linestream, data, ';');
		getline(linestream, data, ';');
		place = data.substr(0, data.size());

		DestPlace * d = new DestPlace (place, myGraph.getVertex(node_id));
		destPlacesSet.push_back(d);
		if(place == "school") {
			myGV->setVertexIcon(node_id, "schoolIcon.png");
		} else if (place == "cinema") {
			myGV->setVertexIcon(node_id, "cinemaIcon.png");
		} else if (place == "shopping") {
			myGV->setVertexIcon(node_id, "shoppingIcon.png");
		}
	}

	destFile.close();
}
void Parking::createGraphViewer() {
	myGV->setBackground("map.png");
	myGV->createWindow(5000, 3496);
	myGV->defineVertexColor("blue");
	myGV->defineEdgeColor("black");

	ull_int node_id;
	int x;
	int y;
	for (Vertex * v : myGraph.getVertexSet()) {
		node_id = v->getID();
		x = convertLongitudeToX(v->getLongitude());
		y = convertLatitudeToY(v->getLatitude());


		myGV->addNode(node_id,x,y);
		myGV->setVertexSize(node_id, 30);
		myGV->setVertexLabel(node_id, to_string(node_id));

	}
	myGV->defineEdgeCurved(false);
	for (Vertex * v : myGraph.getVertexSet()) {
		for (Edge * e : v->getAdj()) {
			if(e->isReal()) {
				if (!e->isInGraphViewer()) { //se ja estiver no myGV, nao voltamos a inseri-lo
					if (e->getRoad()->isTwoWays()) {
						myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(),
								EdgeType::UNDIRECTED);
						myGV->setEdgeLabel(e->getID(), "");
					} else {
						myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(),
								EdgeType::DIRECTED);
						myGV->setEdgeLabel(e->getID(), "");
					}
					e->setInGraphViewer();
				}
			}
		}
	}
}

ParkType * Parking::getClosestPark(Vertex* src, Vertex * dest) {
	long dist = LONG_MAX;
	vector<Vertex *> shortPath;
	ParkType * park = NULL;
	for(ParkType * p : parkTypeSet) {
		myGraph.dfs(src);
		if(p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPath(p->getNode());
			long distAux = 0;
			vector<Vertex *> shortPathAux = myGraph.getPath(p->getNode(), dest, distAux);
			if (distAux < dist && distAux != 0) {
				shortPath = shortPathAux;
				dist = distAux;
				park = p;
			}
		}
	}
	return park;
}

int Parking::convertLongitudeToX(double longitude) {
	return floor((longitude - MIN_LNG) * IMAGE_X / (MAX_LNG - MIN_LNG));
}

int Parking::convertLatitudeToY(double latitude) {
	return IMAGE_Y - floor((latitude - MIN_LAT) * IMAGE_Y / (MAX_LAT - MIN_LAT))
			+ 3.5;

}

double Parking::distanceBetweenVertex(Vertex * v1, Vertex * v2) {

	int lat1r = convertLatitudeToY(v1->getLatitude());
	int lon1r = convertLongitudeToX(v1->getLongitude());
	int lat2r = convertLatitudeToY(v2->getLatitude());
	int lon2r = convertLongitudeToX(v2->getLongitude());
	//	return sqrt(pow(lon2r-lon1r,2)+pow(lat2r-lat1r,2));
	double u = sin((lat2r - lat1r) / 2);
	double v = sin((lon2r - lon1r) / 2);

	return 2.0 * earthRadiusKm
			* asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}

void Parking::toogleStreetNodes(string street) {
	vector<long> streetNodes;

	streetNodes = myGraph.searchStreetNodes(street);
	streetNodes.erase(unique(streetNodes.begin(), streetNodes.end()), streetNodes.end());

	for (int i = 0; i < streetNodes.size(); i++){
		myGV->setVertexColor(streetNodes.at(i),"green");
		myGV->setVertexLabel(streetNodes.at(i), to_string(i+1));
	}

	myGV->rearrange();

}

