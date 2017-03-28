#include "ParkingSystem.h"

ParkingSystem::ParkingSystem(unsigned int windowWidth, unsigned int windowHeight) {
	mapGraph = Graph();
	gv = new GraphViewer(windowWidth, windowHeight, false);
	gv->setBackground("outputSmall.png");
	gv->createWindow(windowWidth, windowHeight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
}

int loadFiles () {
	//Used to temporarily store information from the text files.
		map<unsigned long, Point*> points;
		map<unsigned long, Road*> roads;

		//FileB.txt (mapB.txt) SUBROADS(Road id; Road name; IsTwoWay)
		ifstream secFile("mapB.txt");
		if (secFile.is_open()) {
			while (!secFile.eof()) {
				unsigned long roadID;
				char garbage;
				string name, twoWayStr;
				bool isTwoWay;

				secFile >> roadID >> garbage;

				getline(secFile, name, ';');
				getline(secFile, twoWayStr);

				if (twoWayStr.find("True") == string::npos)
					isTwoWay = false;
				else
					isTwoWay = true;

				roads.insert(
						std::pair<unsigned long, Road*>(roadID,
								new Road(roadID, name, isTwoWay)));
			}
			secFile.close();
		} else {
			cout << "Unable to open file mapB.txt.\n";
			exit(FILE_READING_FAILURE);
		}

		//FileA.txt (mapA.txt) NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
		ifstream mainFile("mapA.txt");
		if (mainFile.is_open()) {
			while (!mainFile.eof()) {
				unsigned long nodeID;
				double latitude, longitude, projectionX, projectionY;
				char garbage;
				string POI;
				string suburb;

				mainFile >> nodeID >> garbage >> latitude >> garbage >> longitude
				>> garbage >> projectionX >> garbage >> projectionY >> garbage;

				getline(mainFile, suburb, ';');
				getline(mainFile, POI, ';');

				if (latitude > MIN_LAT && latitude < MAX_LAT && longitude > MIN_LON	&& longitude < MAX_LON) {
					Point* c = new Point(nodeID, latitude, longitude, projectionX,
							projectionY);
					points.insert(std::pair<unsigned long, Point*>(nodeID, c));
					c->setPOI(POI);
					c->setSuburb(suburb);
					mapGraph.addVertex(*c);
				}
			}
			mainFile.close();
		} else {
			cout << "Unable to open file roads.txt.\n";
			exit(FILE_READING_FAILURE);
		}

		//FileC.txt (mapC.txt) ROADS(Road id; PointID 1; PointID 2)
		ifstream thirdFile("mapC.txt");
		if (thirdFile.is_open()) {
			while (!thirdFile.eof()) {
				unsigned long roadID;
				unsigned long firstNodeID;
				unsigned long secondNodeID;
				char garbage;

				thirdFile >> roadID >> garbage >> firstNodeID >> garbage
				>> secondNodeID >> garbage;

				map<unsigned long, Point*>::iterator firstNodeIterator, secondNodeIterator;

				firstNodeIterator = points.find(firstNodeID);
				secondNodeIterator = points.find(secondNodeID);
				if (firstNodeIterator != points.end()
						&& secondNodeIterator != points.end()) {

					Road* road = roads.find(roadID)->second;

					mapGraph.addEdge(*(firstNodeIterator->second),
							*(secondNodeIterator->second), road);

					if (road->getTwoWay())
						mapGraph.addEdge(*(secondNodeIterator->second),
								*(firstNodeIterator->second), road);
				}
			}
			thirdFile.close();
		} else {
			cout << "Unable to open file mapC.txt.\n";
			exit(FILE_READING_FAILURE);
		}

		return 0;
	}
}



