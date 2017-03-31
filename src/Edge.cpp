
#include "Edge.h"

unsigned int Edge::nextEdgeID = 0;

Edge::Edge(Vertex *s, Vertex *d, Road* road) :
	source(s), destination(d), road(road), edgeID(nextEdgeID) {
	distance = s->getInfo().getDistance(d->getInfo());
	nextEdgeID++;
}

Vertex* Edge::getSource() const{
	return source;
}

Vertex* Edge::getDestination() const{
	return destination;
}

string Edge::getRoadName() const{
	return road->getName();
}

Road* Edge::getRoad() const{
	return road;
}

unsigned int Edge::getEdgeID() const{
	return edgeID;
}
