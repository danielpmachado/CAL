/*
 * DestPlaces.cpp
 *
 *  Created on: 05/04/2017
 *      Author: bibib
 */

#include "DestPlaces.h"

DestPlaces::DestPlaces(string place, Vertex * v) {
	this->place = place;
	this->v = v;
}
string DestPlaces::getPlace() const {
	return place;
}
Vertex * DestPlaces::getNode() const {
	return v;
}
void DestPlaces::setPlace(string place) {
	this->place = place;
}
void DestPlaces::setNode(Vertex * v) {
	this->v = v;
}


