/*
 * UserInterface.cpp
 *
 *  Created on: 05/04/2017
 *      Author: up201504570
 */

#include "UserInterface.h"


UserInterface::UserInterface(Parking * p) {
	this->p = p;

}

UserInterface::~UserInterface() {
	// TODO Auto-generated destructor stub
}


/*
void UserInterface::start()const{

	clearScreen();

	cout << TAB << "PRESS ENTER TO CALCULATE ROUTE" << endl;

	pauseScreen();
	clearScreen();

	cout << TAB << "Please choose the street your in..." << endl;


	vector<string> streetNames = p->getStreetNames();


	for(string name : streetNames)
		cout << TAB << "-> "<< name << endl;

	// Aqui escolher a rua certa
	// Vou assumir que é Pearl Street

	pauseScreen();
	clearScreen();

	string street = "Pearl Street";



	p->toogleStreetNodes(street);
	vector<long> streetNodes = p->getStreetNodes(street);

	cout <<  TAB << "From the green nodes choose the closest to your position" << endl;

	for(long node: streetNodes)
		cout << TAB << "-> "<<  node << endl;



	// Escolher nó certo
	// vou assumir que é o 1


	Vertex * src = p->getVertex(streetNodes.at(0));

	pauseScreen();
	clearScreen();

	vector<DestPlace *> destinations= p->getDestinations();


	cout << TAB << "Where do you want to go?" << endl;

	for(DestPlace * dst : destinations){
		cout << TAB << "->" <<  dst->getPlace() << endl;
	}



	pauseScreen();
	clearScreen();


	// Escolher destino certo
	// vou assumir que é o school

	Vertex * dst = destinations.at(0)->getNode();



	cout << TAB << "Park Option" << endl;

	cout << TAB << "-> Nearest  car park" << endl;
	cout << TAB << "-> Cheapest car park within a maximum distance" << endl;

	pauseScreen();
	clearScreen();

	// SE ESCOLHER O PARQUE MAIS PERTO CHAMAR ESTE CODIGO

	// -------------------------------------------------------
	//ParkType * car_park = p->planDirectShortPath(src, dst);

	//if(car_park != NULL) displayRouteInformation(src,dst,car_park);

	// ---------------------------------------------------------


	// SE ESCOLHER O PARQUE MAIS BARATO CHAMAR ESTE CÓDIGO

	// ----------------------------------------------

	cout << TAB << "Max distance between the Car Park and your Destination" << endl;
	cout << TAB << "-> 50 m" << endl;
	cout << TAB << "-> 100 m" << endl;
	cout << TAB << "-> 200 m" << endl;
	cout << TAB << "-> 300 m" << endl;
	cout << TAB << "-> 400 m" << endl;

	// faz a tua cena Daniel

	pauseScreen();
	clearScreen();


	long max_distance = 200;

	ParkType * car_park = p->planDirectCheapestPath(src,dst, max_distance);

	if(car_park != NULL) displayRouteInformation(src,dst,car_park);

	// -----------------------------------------------------------


}*/

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}


void writeStreetName(int i, vector<string> streetNames){

    if(i == 1)
        cout << setw(15) << " " << left << setw(30)<< streetNames[i] << setw(10) <<  " " << endl;
    else
        cout << setw(15) << " " << left << setw(30)<< streetNames[i] << setw(20) <<  " " << endl;
}


string chooseStreetName(vector<string> streetNames){

    int menu_item = 0, x = 7;
    bool running = true;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


    SetConsoleTextAttribute(console, 240);
    gotoXY(25, 7); writeStreetName(0,streetNames);

    SetConsoleTextAttribute(console, 15);
    for(int i = 1; i < streetNames.size(); i++){
        gotoXY(25, i+7);  writeStreetName(i,streetNames);
    }

    while(running){

        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) && x < streetNames.size()+6) //down button pressed
        {
            gotoXY(25, x);SetConsoleTextAttribute(console, 15);
            writeStreetName(x-7,streetNames);
            x++;

            gotoXY(25, x); SetConsoleTextAttribute(console, 240);
            writeStreetName(x-7,streetNames);

            SetConsoleTextAttribute(console, 15);
            menu_item++;
            continue;

        }

        if (GetAsyncKeyState(VK_UP) && x > 7) //up button pressed
        {
            gotoXY(25, x); SetConsoleTextAttribute(console, 15);
            writeStreetName(x-7,streetNames);
            x--;

            gotoXY(25, x); SetConsoleTextAttribute(console, 240);
            writeStreetName(x-7,streetNames);

            SetConsoleTextAttribute(console, 15);
            menu_item--;
            continue;
        }

        if (GetAsyncKeyState(VK_RETURN))  // Enter key pressed
        {
        	return streetNames[x-7];
        }
    }
}




void UserInterface::start(){

    clearScreen();
    SetConsoleTextAttribute(console, 15);

    cout << TAB << "PRESS ENTER TO CALCULATE ROUTE" << endl;

    pauseScreen();
    clearScreen();

    gotoXY(37,3); cout << "|| Please chose the street your in ||" << endl;


    vector<string> streetNames = p->getStreetNames();

    string street  = chooseStreetName(streetNames);


    // Aqui escolher a rua certa
    // Vou assumir que é Adams Street

    p->toogleStreetNodes(street);
    vector<Vertex *> streetNodes = p->getStreetNodes(street);

    cout <<  TAB << "From the green nodes choose the closest to your position" << endl;


    pauseScreen();
    clearScreen();

    cout << street;

/*
    street = "Pearl Street";  //MUDAR

    p->toogleStreetNodes(street);
*/
}


void UserInterface::displayRouteInformation(Vertex * src, Vertex * dst, ParkType * park)const {

	vector<Vertex *> pathToPark = p->getGraph().getPath(src, park->getNode());

	p->drawPath(pathToPark, "red");

	cout	<< "Total distance: "
			<< dst->getDist() << " m   ( "<< park->getNode()->getDist()
			<< " by car and " << dst->getDist() - park->getNode()->getDist()
			<< " by foot )" << endl;


	cout << "Type of Park: ";
	if(park->getType() == "meter") {
		cout << "Parking meter\n";
	} else
		cout << "Garage\n";

	cout << "Price: " << park->getPrice() << " euros/h\n";

}
