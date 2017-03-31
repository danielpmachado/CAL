#include <iostream>
#include "ParkingSystem.h"
using namespace std;


int main(){
	ParkingSystem  parkingSystem(1200,700);

	parkingSystem.start();

	cin.ignore();
	return 0;
}
