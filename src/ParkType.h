/*
 * ParkType.h
 *
 *  Created on: 04/04/2017
 *      Author: bibib
 */

#ifndef SRC_PARKTYPE_H_
#define SRC_PARKTYPE_H_

#include <iomanip>
#include <iostream>
#include <string>

#include "Graph.h"
using namespace std;

class ParkType {
private:
	Vertex * v;
	string type; //meter or garage
	double price;
public:

	/*
	 * Park Type constructor
	 *
	 * @param v the vertex
	 *
	 * @param type it can be a garage or a meter
	 *
	 * @param price the price of the parking
	 */
	ParkType(Vertex * v, string type, double price);


	/*
	 * @brief gets the node of the park
	 *
	 * @return the node of the park
	 *
	 */
	Vertex * getNode();

	/*
	 * @brief gets the type of the park
	 *
	 * @return the type of the park
	 *
	 */
	string getType() const;

	/*
	 * @brief gets the price of the park
	 *
	 * @return the price of the park
	 *
	 */
	double getPrice() const;

	/*
	 * @brief sets the node of the park
	 *
	 * @param v the node of the park
	 *
	 */
	void setNode(Vertex * v);

	/*
	 * @brief sets the type of the park
	 *
	 * @param type the type of the park
	 *
	 */
	void setType(string type);

	/*
	 * @brief sets the type of the park
	 *
	 * @param type the type of the park
	 *
	 */
	void setPrice(double type);
};


#endif /* SRC_PARKTYPE_H_ */
