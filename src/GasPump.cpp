/*
 * GasPump.cpp
 *
 *  Created on: 07/04/2017
 *      Author: bibib
 */
#include "GasPump.h"

GasPump::GasPump (Vertex * v) {
	this->v = v;
}
Vertex * GasPump::getNode() const {
	return v;
}
void GasPump::setNode(Vertex * v) {
	this->v = v;
}


