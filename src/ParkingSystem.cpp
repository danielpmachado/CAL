#include "ParkingSystem.h"

ParkingSystem::ParkingSystem(unsigned int windowWidth, unsigned int windowHeight) {
	mapGraph = Graph();
	gv = new GraphViewer(windowWidth, windowHeight, false);
	gv->setBackground("outputSmall.png");
	gv->createWindow(windowWidth, windowHeight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
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

/**
 * vector that reads the Roads from a file and stores them in a vector
 */
void readRoads(const char* filename) {
	vector<Road *> vec;
	ifstream file;

	file.open(filename);

	if (!file.is_open())
		return vec;

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
		vec.push_back(newRoad);
	}

	file.close();

	return vec;
}

/**
 * \brief function that reads the edges from the subroads file and creates the aproppriate edges in the nodes
 *
 * the function creates an Edge, sets the Road it refers to and checks if it is two way and
 * calls the addEdge function in the Node(s)
 *
 * TODO end
 */
void readEdges(const char *filename, vector<Node *> &nodes,
		vector<Road *> &roads, vector<unsigned long> roadIds) {

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

		if (getline(file, buff, ';')) {
			ss << buff;
			ss >> edgeID;
			ss.clear();
		}

		if (getline(file, buff, ';')) {
			ss << buff;
			ss >> nodeFromID;
			ss.clear();
		}

		if (getline(file, buff)) {
			ss << buff;
			ss >> nodeToID;
			ss.clear();
		}

		bool foundMatch = false;

		for (unsigned int i = 0; i < roads.size(); i++) {
			if (roads[i]->getID() == edgeID) {
				twoway = roads[i]->isTwoWay();
				currRoad = roads[i];
				foundMatch = true;
			}
		}

		if (!foundMatch) {
			cout << "Search failure\n";
			cin.get();
			continue;
		}

		for (unsigned int i = 0; i < nodes.size(); i++) {
			if (nodes[i]->getId() == nodeFromID)
				nodeFrom = nodes[i];

			if (nodes[i]->getId() == nodeToID)
				nodeTo = nodes[i];
		}

		if (nodeFrom == NULL) {
			cout << "nodeFrom from not found\n";
			continue;
		}

		if (nodeTo == NULL) {
			cout << "nodeTo not found\n";
			continue;
		}

		nodeFrom->addEdgeTo(nodeTo, new Edge(currRoad));

		if (twoway) {
			nodeTo->addEdgeTo(nodeFrom, new Edge(currRoad));
		}
	}

	file.close();

}

int loadFiles () {
	vector<Road *> roadVec;
	vector<unsigned long> roadIds;

	nodeVec = readNodes("mapA.txt");
	roadVec = readRoads("mapB.txt", roadIds);

	readEdges("mapC.txt", nodeVec, roadVec, roadIds);

		return 0;
	}



