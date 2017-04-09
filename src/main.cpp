/*
  * main.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */




#include "Parking.h"
#include "UserInterface.h"
#include <iostream>



int main(){

	Parking p;
	UserInterface ui(&p);

	ui.start();

	getchar();
	return 0;
}

