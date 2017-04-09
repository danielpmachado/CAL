/*
 * GasPump.h
 *
 *  Created on: 07/04/2017
 *      Author: bibib
 */

#ifndef SRC_GASPUMP_H_
#define SRC_GASPUMP_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class GasPump {
private:
	Vertex * v;
public:
	/**
	 * @brief  Gas pump construtor
	 *
	 * @param v vertex that represents the gas pump on the graph
	 *
	 */
	GasPump(Vertex * v);
	/**
	 * @brief  returns the vertex that represents the gas pump ont he graph
	 *
	 * @return v pointer to the vertex
	 *
	 */
	Vertex * getNode() const;
	/**
	 * @brief changes the vertex that represents the gas pump on the graph
	 *
	 * @param v pointer to the new vertex
	 *
	 */
	void setNode(Vertex * v);
};

#endif /* SRC_GASPUMP_H_ */
