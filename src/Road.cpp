/*
 * Road.cpp
 *
 *  Created on: 02/04/2017
 *      Author: bibib
 */

#include "Road.h"

Road::Road(int id, string name, bool twoWays) {
	this->id = id;
	this->name = name;
	this->twoWays = twoWays;
}

int Road::getID() {
	return id;
}
string Road::getName() {
	return name;
}
bool Road::isTwoWays() {
	return twoWays;
}
void Road::setID(int id) {
	this->id = id;
}
void Road::setName(string name) {
	this->name = name;
}
void Road::setTwoWays() {
	twoWays = twoWays ? false : true;
}


