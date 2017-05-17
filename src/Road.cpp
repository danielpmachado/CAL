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

MatchingRoad::MatchingRoad(string s, int dist) {
	this->roadName = s;
	this->editDist = dist;
}

string MatchingRoad::getRoadName() const { return this->roadName; }

void MatchingRoad::setRoadName(string s) { this->roadName = s; }

int MatchingRoad::getDist() const { return this->editDist; }

void MatchingRoad::setDist(int dist) { this->editDist = dist; }

bool MatchingRoad::operator<(const MatchingRoad &r2) const {
	return this->editDist > r2.getDist();
}
