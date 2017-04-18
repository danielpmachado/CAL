/*
 * UserInterface.h
 *
 *  Created on: 05/04/2017
 *      Author: up201504570
 */

#ifndef SRC_USERINTERFACE_H_
#define SRC_USERINTERFACE_H_

#include <iostream>
#include <algorithm>

#include "Parking.h"
#include "utils.h"

using namespace std;

class UserInterface {
	Parking * p;
public:

	/*
	 * @brief User Interface contructor
	 *
	 * @param p the parking used
	 *
	 */
	UserInterface(){}

	/*
	 * @brief  User Interface desctructor
	 *
	 */
	virtual ~UserInterface();

	/*
	 * @brief initializes the interface
	 *
	 */
	void start();

	/*
	 * @brief displays the route information
	 *
	 * @param src the vertex where the journey begins
	 *
	 * @param dest the vertex where the journey ends
	 *
	 * @param park the park type
	 *
	 */
	void displayRouteInformation(Vertex * src, Vertex * dst, ParkType * park)const;

	/*
	 * @brief writes the name of the street
	 *
	 * @param i the index of the vector
	 *
	 * @param streetNames the vector that contains the name of the streets
	 *
	 */
	void writeStreetName(int i, vector<string> streetNames);

	/*
	 * @brief writes the nodes of the street
	 *
	 * @param i the index of the vector
	 *
	 * @param streetNodes the vector that contains the nodes of the streets
	 *
	 */
	void writeNodes(int i, vector<Vertex *> streetNodes);

	/*
	 * @brief writes the destination
	 *
	 * @param i the index of the vector
	 *
	 * @param destinations the vector that contains the destinations
	 *
	 */
	void writeDestiny(int i, vector<DestPlace *> destinations);

	/*
	 * @brief writes the maximum distance
	 *
	 * @param i the index of the vector
	 *
	 */
	void writeMaxDistance(int i);

	/*
	 * @brief writes the preference
	 *
	 * @param i the index of the vector
	 *
	 */
	void writePreference(int i);

	/*
	 * @brief writes the gasoline
	 *
	 * @param i the index of the vector
	 *
	 */
	void writeGasoline(int i);


	/*
	 * @brief chooses the vertex of a specific street
	 *
	 * @param street the street you are working at
	 *
	 * @return the node you have chosen
	 *
	 */
	Vertex* chooseVertex(string street);

	/*
	 * @brief chooses the street name
	 *
	 * @return the street you have chosen
	 *
	 */
	string chooseStreetName();

	/*
	 * @brief chooses the destination
	 *
	 * @return the destination you have chosen
	 *
	 */
	Vertex * chooseDestiny();

	/*
	 * @brief chooses the preference
	 *
	 * @return the preference you have chosen
	 *
	 */
	int choosePreference();

	/*
	 * @brief chooses the maximum Distance
	 *
	 * @return the maximum Distance you have chosen
	 *
	 */
	int chooseMaxDistance();

	/*
	 * @brief chooses whether you want to pass by a gas bump or not
	 *
	 * @return if you want to pass by a gas bump or not
	 *
	 */
	bool wantGasoline();

};

#endif /* SRC_USERINTERFACE_H_ */
