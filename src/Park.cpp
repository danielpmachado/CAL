#include "Park.h"

Park::Park (string type, double price, Vertex * node, string name) {
	this->type = type;
	this->price = price;
	this->node = node;
	this->name = names
}

string Park::getType () const {
	return type;
}

double Park::getPrice () const {
	return price;
}

Vertex * Park::getNode () const {
	return node;
}

string Park::getName () const {
	return name;
}

void Park::setType (string type) {
	this->type = type;
}

void Park::setPrice (double price) {
	this->price = price;
}

void Park::setNode (Vertex * node) {
	this->node = node;
}

void Park::setName (string name) {
	this->name = name;
}
