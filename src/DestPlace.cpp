/*
 * DestPlaces.cpp
 *
 *  Created on: 05/04/2017
 *      Author: bibib
 */

#include "DestPlace.h"

DestPlace::DestPlace(string place, Vertex * v) {
	this->place = place;
	this->v = v;
}
string DestPlace::getPlace() const {
	return place;
}
Vertex * DestPlace::getNode() const {
	return v;
}
void DestPlace::setPlace(string place) {
	this->place = place;
}
void DestPlace::setNode(Vertex * v) {
	this->v = v;
}


