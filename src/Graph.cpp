/*
 * Graph.cpp
 */

#include "Graph.h"
#include "Vertex.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cfloat>
#include <queue>
#include <climits>

using namespace std;

Graph::Graph() : lastComputedSource(NULL) { }

int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex> Graph::getVertexSet() const {
	return vertexSet;
}

bool Graph::addVertex(const Point &in) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info == in)
			return false;
	}

	vertexSet.push_back(Vertex(in));
	return true;
}

bool Graph::addEdge(const Point &sourc, const Point &dest, Road* road) {
	int sourceIndex = 0;
	int destIndex = 0;
	bool hasSource = false, hasDest = false;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info == sourc) {
			sourceIndex = i;
			hasSource = true;
		}
	}

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info == dest) {
			destIndex = i;
			hasDest = true;
		}
	}

	if (!hasDest || !hasSource)
		return false;

	Edge* edge = new Edge(&vertexSet[sourceIndex], &vertexSet[destIndex], road);
	vertexSet[sourceIndex].adj.push_back(edge);

	if (road->getTwoWay()) {
		vertexSet[destIndex].adj.push_back(edge);
	}

	return true;
}

list<Vertex*> Graph::getShortestPath(Vertex* source, Vertex* goal) {
	if(lastComputedSource == NULL || source != lastComputedSource)
		computePaths(source);

	list<Vertex*> path = list<Vertex*>();
	Vertex* v = goal;

	if(goal->getDistance() == DBL_MAX)
		return path;

	while(v->previous != NULL) {
		path.push_front(v->previous);
		v = v->previous;
	}

	return path;
}

void Graph::computePaths(Vertex* source) {
	resetPathfinding();

	source->minDistance = 0;

	priority_queue<Vertex*> toBeProcessed = priority_queue<Vertex*>();
	toBeProcessed.push(source);

	while(!toBeProcessed.empty()) {
		Vertex* beingProcessed = toBeProcessed.top();
		toBeProcessed.pop();

		for(unsigned int i = 0; i < beingProcessed->adj.size(); i++) {
			Vertex* dest = beingProcessed->adj[i]->destination;
			double distanceToDest = beingProcessed->adj[i]->distance + beingProcessed->minDistance;

			if(distanceToDest < dest->minDistance) {
				dest->minDistance = distanceToDest;
				dest->previous = beingProcessed;

				toBeProcessed.push(dest);
			}
		}
	}
}

Vertex* Graph::getVertexFromID(unsigned int pointID) {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info.getId() == pointID)
			return &vertexSet[i];
	}

	return NULL;
}

Vertex* Graph::getApproximateVertex(const string &roadName) {
	unsigned int minEditDist = UINT_MAX;
	Vertex* minVertex = NULL;
	unsigned int roadDist, POIDist;

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		POIDist = EasyPilot::editDistance(roadName, vertexSet[i].getInfo().getPOI());

		if(POIDist < minEditDist) {
			minVertex = &vertexSet[i];
			minEditDist = POIDist;
		}

		for(unsigned int j = 0; j < vertexSet[i].getAdj().size(); j++) {
			roadDist = EasyPilot::editDistance(roadName, vertexSet[i].getAdj()[j]->getRoad()->getName());

			if(roadDist < minEditDist) {
				minVertex = &vertexSet[i];
				minEditDist = roadDist;
			}
		}
	}

	cout << "Could not find an exact match. Assuming " << minVertex->getRoadName();

	return minVertex;
}

Vertex* Graph::getVertexFromRoadName(const string &roadName) {

	for(unsigned int i = 0; i < vertexSet.size(); i++){
		if(EasyPilot::exactMatch(vertexSet[i].getInfo().getPOI(), roadName)) {
			cout << "Found an exact match.\n";
			return &vertexSet[i];
		}

		for(unsigned int j = 0; j < vertexSet[i].getAdj().size();j++){
			if(EasyPilot::exactMatch(vertexSet[i].getAdj()[j]->getRoad()->getName(), roadName)) {
				cout << "Found an exact match.\n";
				return &vertexSet[i];
			}
		}
	}

	return getApproximateVertex(roadName);
}

/*Vertex* Graph::getVertexFromRoadName(const string &roadName) {
	for(unsigned int i = 0; i < vertexSet.size(); i++){
		for(unsigned int j = 0; j < vertexSet[i].getAdj().size();j++){
			if(vertexSet[i].getAdj()[j]->getRoad()->getName().find(roadName) != string::npos ||
					vertexSet[i].getInfo().getPOI().find(roadName) != string::npos)
				return &vertexSet[i];
		}
	}
	return NULL;
}*/

void Graph::resetPathfinding() {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i].minDistance = DBL_MAX;
		vertexSet[i].previous = NULL;
	}
}

unsigned int Graph::getVertexSetSize() const {
	return vertexSet.size();
}

Vertex* Graph::getVertexFromIndex(unsigned int index) {
	return &vertexSet[index];
}
