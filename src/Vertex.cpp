/*
 * Vertex.cpp
 */

#include "Vertex.h"
#include <cfloat>

Vertex::Vertex(Point* in) :
info(in), minDistance(DBL_MAX), previous(NULL) {
}

vector<Edge*>& Vertex::getAdj() {
	return adj;
}

void Vertex::addEdge (Edge * e) {
	adj.push_back(e);
}

Point* Vertex::getInfo() {
	return info;
}

bool Vertex::operator==(const Vertex &rhs) {
	return this->info == rhs.info;
}

bool Vertex::operator<(const Vertex &rhs) {
	return this->minDistance < rhs.minDistance;
}

Edge* Vertex::getEdgeBetween(Vertex* dest) const {
	for(unsigned int i = 0; i < adj.size(); i++) {
		if(adj[i]->destination == dest)
			return adj[i];
	}

	return NULL;
}

Road* Vertex::getRoadBetween(Vertex* dest) const {
	Edge* edge = this->getEdgeBetween(dest);

	return edge == NULL ? NULL : edge->getRoad();
}

double Vertex::getDistance() const {
	return minDistance;
}

string Vertex::getRoadName() const {
	if(info.getPOI() != "")
		return info.getPOI();

	if(adj.size() == 1)
		return adj[0]->road->getName();
	else if (adj.size() > 1) {
		return "Intersection between " + adj[0]->road->getName() + " and " + adj[1]->road->getName();
	}
	else return "";
}

bool Vertex::operator!=(const Vertex &rhs) {
	return !(*this == rhs);
}

