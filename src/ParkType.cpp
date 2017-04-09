/*
 * ParkType.cpp
 *
 *  Created on: 04/04/2017
 *      Author: bibib
 */

#include "ParkType.h"

ParkType::ParkType(Vertex * v, string type, double price) {
	this->v = v;
	this->type = type;
	this->price = price;
}
Vertex * ParkType::getNode() {
	return v;
}
string ParkType::getType() const {
	return type;
}
double ParkType::getPrice() const {
	return price;
}
void ParkType::setNode(Vertex * v) {
	this->v = v;
}
void ParkType::setType(string type) {
	this->type = type;
}
void ParkType::setPrice(double price) {
	this->price = price;
}


