/*
 * DestPlaces.h
 *
 *  Created on: 05/04/2017
 *      Author: bibib
 */

#ifndef SRC_DESTPLACE_H_
#define SRC_DESTPLACE_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class DestPlace {
private:
	string place;
	Vertex * v;
public:
	/**
	 * @brief  Destination Place constructor
	 *
	 * @param place name of the destination place
	 *
	 * @param v pointer to the graph vertex corresponding to the destination place
	 *
	 */
	DestPlace(string place, Vertex * v);
	/**
	 * @brief  returns the name of the destination place
	 *
	 * @return name of the place
	 *
	 *
	 */
	string getPlace() const;
	/**
	 * @brief  returns the vertex corresponding to the destination place
	 *
	 * @return name of the place
	 *
	 */
	Vertex * getNode() const;
	/**
	 * @brief  sets the name of the destination place
	 *
	 * @param place new destination name
	 *
	 */
	void setPlace(string place);
	/**
	 * @brief  sets the vertex of the destination place
	 *
	 * @param v new destination vertex
	 *
	 */
	void setNode(Vertex * v);
};

#endif /* SRC_DESTPLACE_H_ */
