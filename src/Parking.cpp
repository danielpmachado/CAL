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
	//planDirectCheapestPath(myGraph.getVertex(42494919), myGraph.getVertex(42464824), 100);
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
void Parking::readGasPumps() {
	ifstream gasPumpFile;
		string line;
		ull_int node_id;
		gasPumpFile.open("gaspump.txt");

		if (!gasPumpFile) {
			cerr << "Unable to open file gaspump.txt";
			return;
		}
		while (getline(gasPumpFile, line)) {
			stringstream linestream(line);
			linestream >> node_id;

			GasPump * gp = new GasPump(myGraph.getVertex(node_id));
			gasPumpSet.push_back(gp);
		}

		gasPumpFile.close();
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
			} else {
				myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(),EdgeType::UNDIRECTED);
				myGV->setEdgeLabel(e->getID(), "");
			}
		}
	}
}

ParkType * Parking::getClosestPark(Vertex* src, Vertex * dest, double &finalDist) {
	long dist = LONG_MAX;
	vector<Vertex *> shortPath;
	ParkType * park = NULL;
	for(ParkType * p : parkTypeSet) {
		myGraph.dfs(src);
		if(p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPathToDest(p->getNode());
			vector<Vertex *> shortPathAux = myGraph.getPath(p->getNode(), dest);
			if (dest->getDist() < dist && dest->getDist() != 0) {
				shortPath = shortPathAux;
				dist = dest->getDist();
				park = p;
			}
			drawPath(shortPathAux, "pink");
		}
	}
	drawPath(shortPath, "red");
	finalDist = dist;
	return park;
}
ParkType * Parking::getCheapestPark(Vertex * src, Vertex * dest, double distMax, double &finalDist) {
	long dist;
	double price = 1000;
	vector<Vertex *> shortPath;
	ParkType * park = NULL;
	for(ParkType * p : parkTypeSet) {
		myGraph.dfs(src);
		if(p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPathToDest(p->getNode());
			vector<Vertex *> shortPathAux = myGraph.getPath(p->getNode(), dest);
			drawPath(shortPathAux, "pink");
			if(dest->getDist() <= distMax) {
				if (p->getPrice() < price) {
					price = p->getPrice();
					shortPath = shortPathAux;
					dist = dest->getDist();
					park = p;
				}
			}
		}
	}
	drawPath(shortPath, "red");
	finalDist = dist;
	return park;
}

void Parking::drawPath(vector<Vertex*> path, string color) {
	Vertex * aux = NULL;
	for (Vertex * node : path) {
		myGV->setVertexColor(node->getID(),color);
		if(aux != NULL) {
			myGV->setEdgeThickness(aux->getEdgeToVertex(node)->getID(), 20);
			myGV->setEdgeColor(aux->getEdgeToVertex(node)->getID(), color);
		}
		aux = node;
	}
}
void Parking::planDirectShortPath(Vertex * src, Vertex * dest) {
	double dist = 0;
	ParkType * p = getClosestPark(src, dest, dist);
	if(p == NULL) {
		cout << "There is not a possible path. Try again.\n";
		return;
	}
	myGraph.dijkstraShortestPathToPark(src);
	vector<Vertex *> pathToPark = myGraph.getPath(src, p->getNode());
	drawPath(pathToPark, "red");
	dist += p->getNode()->getDist();
	cout << "Total distance: " << dist << " m   ( "<< p->getNode()->getDist() << " by car and " << dist - p->getNode()->getDist() << " by foot )" << endl;
	cout << "Type of Park: ";
	if(p->getType() == "meter") {
		cout << "Parking meter\n";
	} else
		cout << "Garage\n";
	cout << "Price: " << p->getPrice() << " euros/h\n";
}
void Parking::planDirectCheapestPath(Vertex * src, Vertex * dest, double maxDist) {
	double dist = 0;
	ParkType * p = getCheapestPark(src, dest, maxDist, dist);
	if(p == NULL) {
		cout << "There is not a possible path. Try again.\n";
		return;
	}
	myGraph.dijkstraShortestPathToPark(src);
	vector<Vertex *> pathToPark = myGraph.getPath(src, p->getNode());
	drawPath(pathToPark, "red");
	dist += p->getNode()->getDist();
	cout << "Total distance: " << dist << " m   ( "<< p->getNode()->getDist() << " by car and " << dist - p->getNode()->getDist() << " by foot )" << endl;
	cout << "Type of Park: ";
	if(p->getType() == "meter") {
		cout << "Parking meter\n";
	} else
		cout << "Garage\n";
	cout << "Price: " << p->getPrice() << " euros/h\n";
}



double Parking::distanceBetweenVertex(Vertex * v1, Vertex * v2) {

	int lat1r = convertLatitudeToY(v1->getLatitude());
	int lon1r = convertLongitudeToX(v1->getLongitude());
	int lat2r = convertLatitudeToY(v2->getLatitude());
	int lon2r = convertLongitudeToX(v2->getLongitude());
	return SCALE*sqrt(pow(lon2r-lon1r,2)+pow(lat2r-lat1r,2));


}

void Parking::toogleStreetNodes(string street) {
	vector<long> streetNodes = getStreetNodes(street);

	for (int i = 0; i < streetNodes.size(); i++){
		myGV->setVertexColor(streetNodes.at(i),"green");
		myGV->setVertexLabel(streetNodes.at(i), to_string(streetNodes.at(i)));
	}

	myGV->rearrange();


}

vector<string> Parking::getStreetNames()const{

	vector<string> streetNames;
	map<long, Road*>::const_iterator it;

	for(it = roads.begin(); it != roads.end(); it++){
			if(it->second->getName()!= "")
				streetNames.push_back(it->second->getName());
		}

		sort(streetNames.begin(), streetNames.end());
		streetNames.erase(unique(streetNames.begin(), streetNames.end()), streetNames.end());


		return streetNames;

}

vector<string> Parking::getDestinationNames()const{

	vector<DestPlace *>::const_iterator it;

	vector<string> destinationNames;


	for(it = destPlacesSet.begin(); it!= destPlacesSet.end(); it++)
		destinationNames.push_back((*it)->getPlace());

	return destinationNames;


}

vector<long> Parking::getStreetNodes(string street){
	vector<long> streetNodes;

	streetNodes = myGraph.searchStreetNodes(street);
	sort(streetNodes.begin(), streetNodes.end());
	streetNodes.erase(unique(streetNodes.begin(), streetNodes.end()), streetNodes.end());


	return streetNodes;
}

Vertex * Parking::getVertex(long id){

	vector<Vertex*> vertexSet = myGraph.getVertexSet();

	for(Vertex * v: vertexSet)
		if(v->getID() == id) return v;


	return NULL;
}

