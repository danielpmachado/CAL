#include "GasPump.h"

void GasPump::setName(string name) {
	this->name = name;
}

void GasPump::setNode(Vertex * node) {
	this->node = node;
}

string GasPump::getName() const{
	return name;
}

Vertex * GasPump::getNode() const{
	return node;
}
