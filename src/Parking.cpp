
#include "Parking.h"

Parking::Parking() {
	readNodesFile();
	readRoadsFile();
	readConnectionsFile();
	//createGraphViewer();
	//readParks();
	//readDestinations();
	//readGasPumps();
	//myGV->rearrange();
	//planGasPumpCheapestPath(myGraph.getVertexBySecondID(46), myGraph.getVertexBySecondID(10), 1000);
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

		myGraph.addEdge(srcNodeID, dstNodeID, dist, roads.find(roadID)->second,
				true);
		if ((roads.find(roadID)->second)->isTwoWays()) {
			myGraph.addEdge(dstNodeID, srcNodeID, dist,
					roads.find(roadID)->second, true);
		} else {
			myGraph.addEdge(dstNodeID, srcNodeID, dist,
					roads.find(roadID)->second, false);
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
		myGV->setVertexIcon(node_id, "gasPumpIcon.png");
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

		DestPlace * d = new DestPlace(place, myGraph.getVertex(node_id));
		destPlacesSet.push_back(d);
		if (place == "school") {
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

	myGV= new GraphViewer(5000, 3496, false);

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

		myGV->addNode(node_id, x, y);
		myGV->setVertexSize(node_id, 30);


	}
	myGV->defineEdgeCurved(false);
	for (Vertex * v : myGraph.getVertexSet()) {
		for (Edge * e : v->getAdj()) {
			if (e->isReal()) {
				if (!e->isInGraphViewer()) { //se ja estiver no myGV, nao voltamos a inseri-lo
					if (e->getRoad()->isTwoWays()) {
						myGV->addEdge(e->getID(), v->getID(),
								e->getDest()->getID(), EdgeType::UNDIRECTED);
						myGV->setEdgeLabel(e->getID(), "");
					} else {
						myGV->addEdge(e->getID(), v->getID(),
								e->getDest()->getID(), EdgeType::DIRECTED);
						myGV->setEdgeLabel(e->getID(), "");
					}
					e->setInGraphViewer();
				}
			} else {
				myGV->addEdge(e->getID(), v->getID(), e->getDest()->getID(),
						EdgeType::UNDIRECTED);
				myGV->setEdgeLabel(e->getID(), "");
			}
		}
	}
}

ParkType * Parking::getParkType(Vertex * v) {
	for (ParkType * p : parkTypeSet) {
		if (p->getNode() == v) {
			return p;
		}
	}
	return NULL;
}
ParkType * Parking::getClosestPark(Vertex* src, Vertex * dest, double &finalDist) {
	long dist = LONG_MAX;
	vector<Vertex *> shortPath;
	ParkType * park = NULL;

	for (ParkType * p : parkTypeSet) {
		myGraph.dfs(src);
		if (p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPathByFoot(p->getNode());
			vector<Vertex *> shortPathAux = myGraph.getPath(p->getNode(), dest);
			if (dest->getDist() < dist && dest->getDist() != 0) {
				shortPath = shortPathAux;
				dist = dest->getDist();
				park = p;
			}

		}
	}

	drawPath(shortPath, "red");
	finalDist = dist;
	return park;
}
ParkType * Parking::getCheapestPark(Vertex * src, Vertex * dest, double distMax, double &finalDist) {
	double price = 1000;
	vector<Vertex *> shortPath;
	ParkType * park = NULL;
	for (ParkType * p : parkTypeSet) {
		myGraph.dfs(src);
		if (p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPathByFoot(p->getNode());
			vector<Vertex *> shortPathAux = myGraph.getPath(p->getNode(), dest);
			//drawPath(shortPathAux, "red");
			if (dest->getDist() <= distMax) {
				if (p->getPrice() < price) {
					price = p->getPrice();
					shortPath = shortPathAux;
					finalDist = dest->getDist();
					park = p;

				}
			}
		}
	}
	drawPath(shortPath, "red");
	return park;
}

void Parking::drawPath(vector<Vertex*> path, string color) {
	Vertex * aux = NULL;
	for (Vertex * node : path) {
		if (aux != NULL) {
			myGV->setEdgeThickness(aux->getEdgeToVertex(node)->getID(), 7);
			myGV->setEdgeColor(aux->getEdgeToVertex(node)->getID(), color);
		}
		myGV->setVertexColor(node->getID(), color);
		aux = node;
	}
}

ParkType * Parking::planDirectShortPath(Vertex * src, Vertex * dest) {
	double dist = 0;
	ParkType * p = getClosestPark(src, dest, dist);

	if (p == NULL) {
		cout << "There is not a possible path. Try again.\n";
		return p;
	}

	myGraph.dijkstraShortestPathByCar(src);
	vector<Vertex *> pathToPark = myGraph.getPath(src, p->getNode());
	drawPath(pathToPark, "red");

	dist += p->getNode()->getDist();

	dest->setDist(dist);

	return p;

}

ParkType * Parking::planDirectCheapestPath(Vertex * src, Vertex * dest, double maxDist) {
	double dist = 0;
	ParkType * p = getCheapestPark(src, dest, maxDist, dist);
	if (p == NULL) {
		cout << "There is not a possible path. Try again.\n";
		return p;
	}

	myGraph.dijkstraShortestPathByCar(src);
	vector<Vertex *> pathToPark = myGraph.getPath(src, p->getNode());
	drawPath(pathToPark, "red");

	dist += p->getNode()->getDist();

	dest->setDist(dist);
	return p;
}


long Parking::calculateGasPumpShortPath(Vertex * src, Vertex * dest, GasPump * &finalGasPump, ParkType * &finalParkType) {
	myGraph.dfs(src);
	vector<GasPump *> accessibleGasPumps; //vetor com as bombas de gasolina acessiveis a partir da localizacao do utilizador
	for (GasPump * gp : gasPumpSet) {
		if (gp->getNode()->isAccessible()) {
			accessibleGasPumps.push_back(gp);
		}
	}
	priority_queue<closestVertex> accessibleParks; //fila com closestVertex (= parque de estacionamento + distancia dele ate ao destino); no inicio da fila estao os parque mais perto do destino
	myGraph.dfs(src);
	for (ParkType * p : parkTypeSet) {
		if (p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPathByFoot(p->getNode());
			closestVertex node = closestVertex(p->getNode(), dest->getDist());
			accessibleParks.push(node);
		}
	}
	long dist = LONG_MAX;
	while (!accessibleParks.empty()) {
		Vertex * v = accessibleParks.top().getNode();
		ParkType * parkAux = getParkType(v); //parque que esta a ser analisado
		double distFromSrcToPark = 0;
		for (GasPump * gp : accessibleGasPumps) {
			myGraph.dfs(gp->getNode());
			if (parkAux->getNode()->isAccessible()) {
				myGraph.dijkstraShortestPathByCar(src);
				distFromSrcToPark += gp->getNode()->getDist(); //distancia da origem a bomba de gasolina
				myGraph.dijkstraShortestPathByCar(gp->getNode());
				distFromSrcToPark += parkAux->getNode()->getDist(); //distancia da bomba de gasolina ao parque
				if (distFromSrcToPark < dist) {
					dist = distFromSrcToPark;
					finalGasPump = gp;
					finalParkType = parkAux;
				}
			}
		}
		if (finalParkType != NULL) { //foi encontrado um precurso possivel
			return dist;
		} else {
			accessibleParks.pop();
		}
	}
	return dist;
}

ParkType * Parking::planGasPumpShortPath(Vertex * src, Vertex * dest) {
	GasPump * pump = NULL;
	ParkType * park = NULL;
	long distFromSrcToPark = calculateGasPumpShortPath(src, dest, pump, park);
	if (distFromSrcToPark == LONG_MAX) {
		cout << "There is not a possible path. Try again.\n";
		return park;
	}
	/*
	 * Draw path from origin to GasPump
	 */
	myGraph.dijkstraShortestPathByCar(src);
	vector<Vertex *> pathToGasPump = myGraph.getPath(src, pump->getNode());
	drawPath(pathToGasPump, "red");
	/*
	 * Draw path from GasPump to Park
	 */
	myGraph.dijkstraShortestPathByCar(pump->getNode());
	vector<Vertex *> pathToPark = myGraph.getPath(pump->getNode(),park->getNode());
	drawPath(pathToPark, "red");
	/*
	 * Draw path from Park to dest
	 */
	myGraph.dijkstraShortestPathByFoot(park->getNode());
	vector<Vertex *> pathToDest = myGraph.getPath(park->getNode(), dest);
	drawPath(pathToDest, "red");


	dest->setDist(distFromSrcToPark +dest->getDist());
	park->getNode()->setDist(distFromSrcToPark);


	return park;


}
long Parking::calculateGasPumpCheapestPath(Vertex * src, Vertex * dest, double maxDist, GasPump * &finalGasPump,  ParkType * &finalParkType) {
	myGraph.dfs(src);
	vector<GasPump *> accessibleGasPumps; //vetor com as bombas de gasolina acessiveis a partir da localizacao do utilizador
	for (GasPump * gp : gasPumpSet) {
		if (gp->getNode()->isAccessible()) {
			accessibleGasPumps.push_back(gp);
		}
	}
	priority_queue<cheapestVertex> accessibleParks; //fila com cheapestVertex (= parque de estacionamento + seu preco); no inicio da fila estao os parque mais baratos
	myGraph.dfs(src);
	for (ParkType * p : parkTypeSet) {
		if (p->getNode()->isAccessible()) {
			myGraph.dijkstraShortestPathByFoot(p->getNode());
			if(dest->getDist() <= maxDist) {
				cheapestVertex node = cheapestVertex(p->getNode(), p->getPrice());
				accessibleParks.push(node);
			}
		}
	}
	long dist = LONG_MAX;
	while (!accessibleParks.empty()) {
		Vertex * v = accessibleParks.top().getNode();
		ParkType * parkAux = getParkType(v); //parque que esta a ser analisado
		for (GasPump * gp : accessibleGasPumps) {
			double distFromSrcToPark = 0;
			myGraph.dfs(gp->getNode());
			if (parkAux->getNode()->isAccessible()) {
				myGraph.dijkstraShortestPathByCar(src);
				distFromSrcToPark += gp->getNode()->getDist(); //distancia da origem a bomba de gasolina
				myGraph.dijkstraShortestPathByCar(gp->getNode());
				distFromSrcToPark += parkAux->getNode()->getDist(); //distancia da bomba de gasolina ao parque
				if (distFromSrcToPark < dist) {
					dist = distFromSrcToPark;
					finalGasPump = gp;
					finalParkType = parkAux;
				}
			}
		}
		if (finalParkType != NULL) { //foi encontrado um precurso possivel
			return dist;
		} else {
			accessibleParks.pop();
		}
	}
	return dist;
}
ParkType * Parking::planGasPumpCheapestPath(Vertex * src, Vertex * dest, double maxDist) {
	GasPump * pump = NULL;
	ParkType * park = NULL;
	long distFromSrcToPark = calculateGasPumpCheapestPath(src, dest, maxDist, pump, park);
	if (distFromSrcToPark == LONG_MAX) {
		cout << "There is not a possible path. Try again.\n";
		return park;
	}
	/*
	 * Draw path from origin to GasPump
	 */
	myGraph.dijkstraShortestPathByCar(src);
	vector<Vertex *> pathToGasPump = myGraph.getPath(src, pump->getNode());
	drawPath(pathToGasPump, "red");
	/*
	 * Draw path from GasPump to Park
	 */
	myGraph.dijkstraShortestPathByCar(pump->getNode());
	vector<Vertex *> pathToPark = myGraph.getPath(pump->getNode(),park->getNode());
	drawPath(pathToPark, "red");
	/*
	 * Draw path from Park to dest
	 */
	myGraph.dijkstraShortestPathByFoot(park->getNode());
	vector<Vertex *> pathToDest = myGraph.getPath(park->getNode(), dest);
	drawPath(pathToDest, "red");

	dest->setDist(distFromSrcToPark +dest->getDist());
	park->getNode()->setDist(distFromSrcToPark);

	return park;


}
double Parking::distanceBetweenVertex(Vertex * v1, Vertex * v2) {

	int lat1r = convertLatitudeToY(v1->getLatitude());
	int lon1r = convertLongitudeToX(v1->getLongitude());
	int lat2r = convertLatitudeToY(v2->getLatitude());
	int lon2r = convertLongitudeToX(v2->getLongitude());
	return SCALE * sqrt(pow(lon2r - lon1r, 2) + pow(lat2r - lat1r, 2));

}

void Parking::toogleStreetNodes(string street) {
	vector<Vertex*> streetNodes = getStreetNodes(street);


	for (int i = 0; i < streetNodes.size(); i++) {

		myGV->setVertexColor(streetNodes.at(i)->getID(), "green");

		myGV->setVertexLabel(streetNodes.at(i)->getID(), to_string(i+1));
	}

	myGV->rearrange();

	cout << "1\111";

}

vector<string> Parking::getStreetNames() const {

	vector<string> streetNames;
	map<long, Road*>::const_iterator it;

	for (it = roads.begin(); it != roads.end(); it++) {
		if (it->second->getName() != "")
			streetNames.push_back(it->second->getName());
	}

	sort(streetNames.begin(), streetNames.end());
	streetNames.erase(unique(streetNames.begin(), streetNames.end()),
			streetNames.end());

	return streetNames;

}

vector<DestPlace *> Parking::getDestinations() const {

	return destPlacesSet;

}

vector<Vertex*> Parking::getStreetNodes(string street) {
	vector<Vertex *> streetNodes;
	vector<long> streetNodesIds;

	streetNodesIds = myGraph.searchStreetNodes(street);
	sort(streetNodesIds.begin(), streetNodesIds.end());
	streetNodesIds.erase(unique(streetNodesIds.begin(), streetNodesIds.end()),
			streetNodesIds.end());

	for(int i =0; i < streetNodesIds.size(); i++)
		streetNodes.push_back(getVertex(streetNodesIds.at(i)));

	return streetNodes;
}

Vertex * Parking::getVertex(long id) {

	vector<Vertex*> vertexSet = myGraph.getVertexSet();

	for (Vertex * v : vertexSet)
		if (v->getID() == id)
			return v;

	return NULL;
}



