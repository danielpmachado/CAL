#include "ParkingSystem.h"

ParkingSystem::ParkingSystem(unsigned int windowWidth, unsigned int windowHeight) {
	mapGraph = Graph();
	gv = new GraphViewer(windowWidth, windowHeight, false);
	gv->setBackground("outputSmall.png");
	gv->createWindow(windowWidth, windowHeight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
}

void ParkingSystem::start() {
	float distance = 0;
		char answer = 'Y';
		Vertex* begin;
		Vertex* destination;
		list<Vertex*> path;
		cout << "Reading files...\n";
		loadFiles();
		cout << "Finished reading files ...\n";
		cout << "Filling the graph viewer with more information...\n";
		fillGraphViewer();
		cout << "Graph viewer is ready!\n";

		//cout << "Please introduce the starting point: ";
		askForPath();
}

void ParkingSystem::readNodes(const char* filename) {

	ifstream file;
	stringstream ss;

	Point newPoint;
	Vertex *newNode;

	file.open(filename);
	if (file.is_open()) {

		unsigned long id;
		double lat, lon, x, y;
		string file_buf;
		file_buf.clear();

		while (!file.eof()) {
			if (getline(file, file_buf, ';')) {//extrair node_id
				ss << file_buf;
				ss >> id;
				file_buf.clear();
				ss.clear();

			}

			if (getline(file, file_buf, ';')) {//extrair latitude_in_degrees
				ss << file_buf;
				ss >> lat;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf, ';')) {//extrair longitude_in_degrees
				ss << file_buf;
				ss >> lon;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf, ';')) {//extrair longitude_in_radians
				ss << file_buf;
				ss >> x;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf)) {//extrair latitude_in_radians
				ss << file_buf;
				ss >> y;
				file_buf.clear();
				ss.clear();
			}

			newPoint = Point(id, lat, lon, x, y);
			newNode = new Vertex(newPoint);
			mapGraph.addVertex(newNode);
		}
	}

	file.close();
}

void ParkingSystem::readRoads(const char* filename) {
	ifstream file;

	file.open(filename);

	if (!file.is_open())
		return;

	while (!file.eof()) {

		string buff;
		buff.clear();
		stringstream ss;

		unsigned long id;
		string name;
		bool twoWay = false;

		if (getline(file, buff, ';')) {//extrair road_id
			ss << buff;
			ss >> id;
			ss.clear();
		}

		getline(file, name, ';');//extrair road_name

		if (getline(file, buff)) {//extrair is_two_way
			twoWay = (buff.c_str()[0] == 'F') ? false : true;
		}

		Road *newRoad = new Road(id, name, twoWay);
		roads.insert(pair<unsigned int, Road *>(newRoad->getId(), newRoad));
	}

	file.close();

	return;
}

void ParkingSystem::readEdges(const char *filename) {

	ifstream file;
	file.open(filename);

	if (!file.is_open())
		return;

	while (!file.eof()) {

		string buff;
		buff.clear();
		stringstream ss;
		Road *currRoad = NULL;

		bool twoway;
		unsigned long edgeID, nodeFromID, nodeToID;
		Node *nodeFrom, *nodeTo;

		if (getline(file, buff, ';')) {//extrair road_id
			ss << buff;
			ss >> edgeID;
			ss.clear();
		}

		if (getline(file, buff, ';')) {//extrair node1_id
			ss << buff;
			ss >> nodeFromID;
			ss.clear();
		}

		if (getline(file, buff)) {//extrair node2_id
			ss << buff;
			ss >> nodeToID;
			ss.clear();
		}

		nodeFrom = mapGraph.getVertexFromID(nodeFromID);
		nodeTo = mapGraph.getVertexFromID(nodeToID);
		currRoad = roads.find(edgeID)->second;
		twoway = currRoad->getTwoWay();
		Edge * newEdge = new Edge(nodeFrom, nodeTo, currRoad);

		nodeFrom->addEdge(newEdge);

		if (twoway) {
			nodeTo->addEdge(newEdge);
		}
	}

	file.close();

}

void ParkingSystem::computePrefix(const string &pattern, int prefix[]) {
	unsigned int length = pattern.length();
	int k = -1;

	prefix[0] = -1;

	for (unsigned int i = 1; i < length; i++) {
		while (k > -1 && tolower(pattern[k+1]) != tolower(pattern[i])) {
			k = prefix[k];
		}

		if (tolower(pattern[k+1]) == tolower(pattern[i]))
			k++;

		prefix[i] = k;
	}
}

void ParkingSystem::readGasPumps(const char* filename) {
	ifstream file;
		file.open(filename);

		if (!file.is_open())
			return;

		while (!file.eof()) {

			string buff;
			buff.clear();
			stringstream ss;

			unsigned long vertexID;

			if (getline(file, buff)) {//extrair node_id
				ss << buff;
				ss >> vertexID;
				ss.clear();
			}

			Vertex * node = mapGraph.getVertexFromID(vertexID);
			node->getInfo().setPOI("Gas Pump");
			GasPump * g = new GasPump(node);
			gasPumps.insert(pair<unsigned long, GasPump *>(vertexID, g));
		}

		file.close();
}

void ParkingSystem::readParks(const char* filename) {
	ifstream file;
		file.open(filename);

		if (!file.is_open())
			return;

		while (!file.eof()) {

			string buff;
			buff.clear();
			stringstream ss;

			unsigned long vertexID, price;
			string parkType;

			if (getline(file, buff, ';')) {//extrair node_id
				ss << buff;
				ss >> vertexID;
				ss.clear();
			}
			getline(file, parkType, ';'); //extrair o tipo de estacionamento

			if (getline(file, buff)) {//extrair pre�o do estacionamento
						ss << buff;
						ss >> price;
						ss.clear();
					}
			Vertex * node = mapGraph.getVertexFromID(vertexID);
			node->getInfo().setPOI("Park");
			Park * p = new Park(parkType, price, node);
			parks.insert(pair<unsigned long, Park *>(vertexID, p));
		}

		file.close();
}

int ParkingSystem::exactMatch(const string &text, const string &pattern) {
	int num = 0;
	int prefix[pattern.length()];

	computePrefix(pattern, prefix);

	int q = -1;
	for (unsigned int i = 0; i < text.length(); i++) {

		while (q > -1 && tolower(pattern[q+1]) != tolower(text[i]))
			q = prefix[q];

		if (tolower(pattern[q+1]) == tolower(text[i]))
			q++;

		if (q == pattern.length() - 1) {
			num++;
			q = prefix[q];
		}
	}

	return num;
}

unsigned int ParkingSystem::editDistance(const string &pattern, const string &text) {
	unsigned int distance[text.length()+1];
	unsigned int oldDistance, newDistance;

	for (unsigned int i = 0; i <= text.length(); i++)
		distance[i] = i;

	for (unsigned int i = 1; i <= pattern.length(); i++) {
		oldDistance = distance[0];
		distance[0] = i;

		for (unsigned int j = 1; j <= text.length(); j++) {
			//Check is not case sensitive
			if (tolower(pattern[i-1]) == tolower(text[j-1]))
				newDistance = oldDistance;
			else {
				newDistance = min(oldDistance, min(distance[j], distance[j-1]));
				newDistance++;
			}

			oldDistance = distance[j];
			distance[j] = newDistance;
		}
	}

	return distance[text.length()];
}

int ParkingSystem::loadFiles () {

	readNodes("mapA.txt");
	readRoads("mapB.txt");
	readEdges("mapC.txt");
	readGasPumps("gasPump.txt");//TODO: criar ficheiros
	readParks("park.txt");

		return 0;
	}

void ParkingSystem::addNodesToGraphViewer() {
	for (unsigned int i = 0; i < mapGraph.getVertexSetSize(); i++) {
		Vertex* vertex = mapGraph.getVertexFromIndex(i);

		gv->addNode(vertex->getInfo().getId(),
				convertLatitudeToY(vertex->getInfo().getLatitude()),
				convertLongitudeToX(vertex->getInfo().getLongitude()));
		gv->setVertexLabel(vertex->getInfo().getId(), ".");

		if(vertex->getInfo().getPOI() != ""){
			gv->setVertexColor(vertex->getInfo().getId(),POI_NODE_COLOR);
			gv->setVertexLabel(vertex->getInfo().getId(), vertex->getInfo().getPOI());
		}
	}
}

int ParkingSystem::convertLongitudeToX(float longitude) {
	return floor(((longitude - MIN_LON) * (IMAGE_Y)) / (MAX_LON - MIN_LON));
}

int ParkingSystem::convertLatitudeToY(float latitude) {
	return floor(((latitude - MIN_LAT) * (IMAGE_X)) / (MAX_LAT - MIN_LAT));
}

void ParkingSystem::askForPath() {
	Vertex* start = readVertex();
		begin = start;

		while(toupper(answer) == 'Y'){
			destination = readVertex();
			list<Vertex*> temp = mapGraph.getShortestPath(start, destination);

			if(destination->getDistance() != DBL_MAX) {
				distance += destination->getDistance();
				cout << "\nDistance between " << start->getRoadName() << " and " << destination->getRoadName() << " is " << destination->getDistance() << " kilometers.\n";
			}

			list<Vertex*>::iterator it2=temp.end();
			list<Vertex*>::iterator it1=temp.begin();
			list<Vertex*>::iterator it=path.end();
			path.insert(it,it1,it2);//copia para a lista path a nova parte do caminho a acrescentar

			start=destination;
			cout << "Do you want to add another place? (Y/N) ";
			cin >> answer;
			cin.ignore();
			cin.clear();
		}

		displayPath(path, begin, destination);
		if(distance > 0)
			cout << "\nTotal path distance is " << distance << " kilometers.\n";
}

void ParkingSystem::displayPath(const list<Vertex*> &path, Vertex* start,Vertex* destination) {

	if (path.size() < 1) {
		cout << "Path not found.\nAre you sure there is a connection?\n";
		return;
	}

	list<Vertex*>::const_iterator nextIt = path.begin()++;
	list<Vertex*>::const_iterator it;
	for (it = path.begin(); nextIt != path.end(); it++) {
		//nextIt++; acho que assim vai estar a passar por cima de um v�rtice do caminho
		Edge* edgeBetween = (*it)->getEdgeBetween(*nextIt);

		gv->setVertexColor((*it)->getInfo().getId(), PATH_FOUND_COLOR);
		if(edgeBetween != NULL) {
			//If the road is two way, we have to color both of the edges.
			//Even though one of them may not be displayed

			if(edgeBetween->getRoad()->getTwoWay()) {
				gv->setEdgeThickness((*nextIt)->getEdgeBetween(*it)->getEdgeID(), 5);
				gv->setEdgeColor((*nextIt)->getEdgeBetween(*it)->getEdgeID(), PATH_FOUND_COLOR);
			}

			gv->setEdgeThickness(edgeBetween->getEdgeID(), 5);
			gv->setEdgeColor(edgeBetween->getEdgeID(), PATH_FOUND_COLOR);
		}
	}

	gv->setVertexColor(start->getInfo().getId(), START_NODE_COLOR);
	gv->setVertexColor(destination->getInfo().getId(), END_NODE_COLOR);
}

Vertex* ParkingSystem::readVertex() {
	Vertex *vertex;
	string roadName;

	cout << "Please introduce a point: ";
	getline(cin, roadName);

	while ((vertex = mapGraph.getVertexFromRoadName(roadName)) == NULL) {
		cout << "Invalid road name. Try again.\n";
		getline(cin, roadName);
	}

	cout << "What suburb does the road belong to?\n";

	string suburb;
	getline(cin, suburb);

	if(!exactMatch(vertex->getInfo().getSuburb(), suburb)) {
		cout << "The road you provided does not belong to the suburb you specified.\nDo you want to choose another road? (Y/N)\n";

		string answer;
		cin >> answer;

		cin.ignore();
		cin.clear();

		if(exactMatch("Y", answer))
			return readVertex();
	}

	return vertex;
}

void ParkingSystem::addEdgesToGraphViewer() {
	set<unsigned int> addedEdges = set<unsigned int>();

	for (unsigned int i = 0; i < mapGraph.getVertexSetSize(); i++) {
		Vertex* vertex = mapGraph.getVertexFromIndex(i);
		for (unsigned int j = 0; j < vertex->getAdj().size();j++) {
			Edge* edge = vertex->getAdj()[j];
			int destID = edge->getDestination()->getInfo().getId();
			int srcID = edge->getSource()->getInfo().getId();

			if (edge->getRoad()->getTwoWay()) {
				set<unsigned int>::iterator it = addedEdges.find(edge->getDestination()->getEdgeBetween(edge->getSource())->getEdgeID());
				if(it != addedEdges.end())  {//edge j� tinha sido colocado no GraphViewer
					addedEdges.erase(it);
				} else {
					gv->addEdge(edge->getEdgeID(), srcID, destID, EdgeType::UNDIRECTED);
					addedEdges.insert(edge->getEdgeID());//necess�rio para o edge n�o aparecer repetido no GraphViewer
				}
			} else {
				gv->addEdge(edge->getEdgeID(), srcID, destID,
						EdgeType::DIRECTED);
			}
		}
	}
}

void EasyPilot::fillGraphViewer() {
	cout << "Adding nodes to graph viewer...\n";
	addNodesToGraphViewer();
	cout << "Finished adding nodes to graph viewer...\n";
	cout << "Adding edges to graph viewer...\n";
	addEdgesToGraphViewer();
	cout << "Finished adding edges to graph viewer...\n";

	gv->rearrange();
}
