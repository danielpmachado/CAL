#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include "Graph.h"

#define MIN_LAT 41.174174
#define MAX_LAT 41.1972
#define MIN_LON -8.596924
#define MAX_LON -8.570913
#define IMAGE_X 2000//esqueci-me de guardar a imagem do mapa e de ver a largura e altura da mesma
#define IMAGE_Y 2500

void exercicio1();
void exercicio2();
void exercicio3();
Graph myGraph = Graph();
GraphViewer *myGV = new GraphViewer(600, 600, false);
map<long, Road*>roads;
static int edgeID = 0;


/*
double distanceBetweenVertex(Vertex * v1, Vertex * v2) {
	return sqrt(pow((v1->getX() - v2->getX()), 2) + pow((v1->getY() - v2->getY()), 2));
}

double convertLongitudeToX(long longitude) {
	return floor(((longitude - MIN_LON) * (IMAGE_Y)) / (MAX_LON - MIN_LON));
}

double convertLatitudeToY(long latitude) {
	return floor(((latitude - MIN_LAT) * (IMAGE_X)) / (MAX_LAT - MIN_LAT));
}

void loadNodes() {
	ifstream file;
	stringstream ss;
	file.open("nodes.txt");
	if(file.is_open()) {
		long id;
		long longitude, latitude, x, y;
		string file_buf;
		file_buf.clear();

		while(!file.eof()) {
			if (getline(file, file_buf, ';')) {
				ss << file_buf;
				ss >> id;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf, ';')) {
				ss << file_buf;
				ss >> latitude;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf, ';')) {
				ss << file_buf;
				ss >> longitude;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf, ';')) {
				ss << file_buf;
				ss >> x;
				file_buf.clear();
				ss.clear();
			}

			if (getline(file, file_buf)) {
				ss << file_buf;
				ss >> y;
				file_buf.clear();
				ss.clear();
			}
			Vertex * v = new Vertex(id, longitude, latitude, x, y);
			myGraph.addVertex(v);
		}
	}
}

void loadRoads() {
	ifstream file;

	file.open("roads.txt");

	if (!file.is_open())
		return;

	while (!file.eof()) {

		string buff;
		buff.clear();
		stringstream ss;

		long id;
		string name;
		bool twoWays = false;

		if (getline(file, buff, ';')) {
			ss << buff;
			ss >> id;
			ss.clear();
		}

		getline(file, name, ';');

		if (getline(file, buff)) {
			twoWays = (buff.c_str()[0] == 'F') ? false : true;
		}

		Road *newRoad = new Road(id, name, twoWays);
		roads.insert(pair<long,Road*>(id, newRoad));
	}

	file.close();
}

void loadSubroads() {
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
		double dist = distanceBetweenVertex(srcNode, destNode);
		myGraph.addEdge(srcNodeID, destNodeID, dist, roads.find(roadID)->second);
		if((roads.find(roadID)->second)->isTwoWays()) {
			myGraph.addEdge(destNodeID, srcNodeID, dist, roads.find(roadID)->second);
		}
	}
}

void graphViewerNodes() {
	myGV->createWindow(600, 600);
	myGV->defineVertexColor("blue");
	myGV->defineEdgeColor("black");
	for(int i = 0; i < myGraph.getNumVertex(); i++) {
		Vertex * v = myGraph.getVertexSet()[i];
		myGV->addNode(v->getID(),convertLongitudeToX(v->getLongitude()),convertLatitudeToY(v->getLatitude()));
	}
}
void graphViewerEdges() {
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
void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);

	gv->defineEdgeDashed(true);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);

	Sleep(2000); // use sleep(1) in linux ; Sleep(2000) on Windows

	gv->removeEdge(0);
	gv->removeNode(1);
	gv->addNode(2);

	gv->rearrange();

	Sleep(2000);

	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	gv->defineEdgeCurved(false);

	gv->setVertexLabel(0, "Isto e um no");
	gv->setEdgeLabel(1, "Isto e uma aresta");

	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->setVertexSize(2, 40);
	gv->setVertexIcon(0, "icon.gif");

	gv->setEdgeDashed(1, false);

	gv->rearrange();

}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->addNode(0,300,50);
	gv->addNode(1,318,58);
	gv->addNode(4,300,100);
	gv->addNode(7,282,58);
	gv->addNode(2,325,75);
	gv->addNode(3,318,93);
	gv->addNode(6,275,75);
	gv->addNode(5,282,93);

	gv->addNode(8,150,200);

	gv->setVertexColor(8, "green");
	gv->setVertexColor(9, "blue");
	gv->setVertexColor(10, "green");
	gv->setVertexColor(11, "blue");
	gv->setVertexColor(12, "green");
	gv->setVertexColor(13, "green");
	gv->addNode(9,300,200);
	gv->addNode(10,450,200);
	gv->addNode(11,300,400);

	gv->addNode(12,200,550);
	gv->addNode(13,400,550);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);

	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
	gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);


	gv->rearrange();
	bool first=true;

	while(1)
	{
		Sleep(2000);
		if (first)
		{
		  gv->removeNode(12);
		  gv->removeNode(13);
		  first=false;
		}
		else
		{
		  gv->removeNode(20);
		  gv->removeNode(21);
		}
		gv->addNode(14,250,550);
		gv->addNode(15,350,550);
		gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
		gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);
		gv->rearrange();

		Sleep(2000);
		gv->removeNode(14);
		gv->removeNode(15);
		gv->addNode(16,300,550);
		gv->addNode(17,300,550);
		gv->addEdge(16, 11, 16, EdgeType::UNDIRECTED);
		gv->addEdge(17, 11, 17, EdgeType::UNDIRECTED);
		gv->rearrange();
		Sleep(2000);

		gv->removeNode(16);
		gv->removeNode(17);
		gv->addNode(18,250,550);
		gv->addNode(19,350,550);
		gv->addEdge(18, 11, 18, EdgeType::UNDIRECTED);
		gv->addEdge(19, 11, 19, EdgeType::UNDIRECTED);
		gv->rearrange();
		Sleep(2000);

		gv->removeNode(18);
		gv->removeNode(19);
		gv->addNode(20,200,550);
		gv->addNode(21,400,550);
		gv->addEdge(20, 11, 20, EdgeType::UNDIRECTED);
		gv->addEdge(21, 11, 21, EdgeType::UNDIRECTED);
		gv->rearrange();
	}
}

void exercicio3()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
	    cerr << "Unable to open file datafile.txt";
	    exit(1);   // call system to stop
	}

	std::string   line;

	int idNo=0;
	int X=0;
	int Y=0;

	while(std::getline(inFile, line))
	{
	    std::stringstream linestream(line);
	    std::string         data;

	    linestream >> idNo;

	    std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
	    linestream >> X;
	    std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
	    linestream >> Y;
	    gv->addNode(idNo,X,Y);

	}

	inFile.close();


	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

		if (!inFile) {
		    cerr << "Unable to open file datafile.txt";
		    exit(1);   // call system to stop
		}

		int idAresta=0;
		int idNoOrigem=0;
		int idNoDestino=0;

		while(std::getline(inFile, line))
		{
		    std::stringstream linestream(line);
		    std::string data;


		    linestream >> idAresta;

		    std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		    linestream >> idNoOrigem;
		    std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		    linestream >> idNoDestino;
		    gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::UNDIRECTED);

		}

		inFile.close();

	gv->rearrange();
}


int main() {
	//exercicio1();
	//exercicio2();
	//exercicio3();
	//getchar();

	/*loadNodes();
	loadRoads();
	loadSubroads();
	graphViewerNodes();
	graphViewerEdges();
  myGV->rearrange();*/

	return 0;
}*/

