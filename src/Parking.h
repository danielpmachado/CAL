/*
 * Parking.h
 *
 *  Created on: Apr 2, 2017
 *      Author: Sofia
 */

#ifndef SRC_PARKING_H_
#define SRC_PARKING_H_

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <climits>

#include "graphviewer.h"
#include "Graph.h"
#include "Road.h"
#include "utils.h"
#include "ParkType.h"
#include "DestPlace.h"
#include "GasPump.h"


using namespace std;

class Parking {
private:
	Graph myGraph = Graph();
	map<long, Road*> roads;
	GraphViewer *myGV= new GraphViewer(5000, 3496, false);
	vector<ParkType*>parkTypeSet;
	vector<DestPlace *>destPlacesSet;
	vector<GasPump *>gasPumpSet;

public:
	/**
	 * construtor da classe
	 */
	Parking();
	/**
	 * destrutor da classe
	 */
	virtual ~Parking();
	/**
	 * retorna o map com o id das ruas (como key) e ruas (como value)
	 */
	map<long, Road*> getRoads();
	/**
	 * retorna o GraphViewer (myGV)
	 */
	GraphViewer * getGraphViewer();
	/**
	 * retorna o grafo (myGraph)
	 */
	Graph getGraph();
	/**
	 * le o ficheiro com a informacao sobre as ruas do mapa
	 */
	void readRoadsFile();
	/**
	 * le o ficheiro com a informacao sobre as arestas do grafo
	 */
	void readConnectionsFile();
	/**
	 * le o ficheiro com a informacao sobre os nos do grafo
	 */
	void readNodesFile();
	/**
	 * le o ficheiro com a informacao sobre os parques de estacionamento
	 */
	void readParks();
	/**
	 * le o ficheiro com a informacao sobre os destinos de interesse
	 */
	void readDestinations();
	/**
	 * le o ficheiro com a informacao sobre as bombas de gasolina
	 */
	void readGasPumps();
	/**
	 * atribui nos e arestas ao GraphViewer e edita seus restantes atributos
	 */
	void createGraphViewer();
	/**
	 * retorna o parque mais perto do destino (ignorando as bombas de gasolina)
	 */
	ParkType * getClosestPark(Vertex* src, Vertex * dest, double &finalDist);
	/**
	 * retorna o parque mais barato (ignorando as bombas de gasolina)
	 */
	ParkType * getCheapestPark(Vertex * src, Vertex * dest, double distMax, double &finalDist);
	/**
	 * pinta no mapa o caminho path de cor color
	 */
	void drawPath(vector<Vertex*> path, string color);
	/**
	 * Planeia o caminho mais curto de um parque ao destino passando por bomba de gasolina
	 */
	void planGasPumpShortPath(Vertex * src, Vertex * dest);
	/**
	 * calcula qual a bomba de gasolina e parque pelos quais vai passar (no caminho mais curto)
	 */
	long calculateGasPumpShortPath(Vertex * src, Vertex * dest, GasPump * &finalGasPump,  ParkType * &finalParkType);
	/**
	 * Planeia o caminho mais barato passando por bomba de gasolina
	 */
	void planGasPumpCheapestPath(Vertex * src, Vertex * dest, double maxDist);
	/**
	 * calcula qual a bomba de gasolina e parque pelos quais vai passar (no caminho mais barato)
	 */
	long calculateGasPumpCheapestPath(Vertex * src, Vertex * dest, double maxDist, GasPump * &finalGasPump,  ParkType * &finalParkType);
	/*
	 * Planeia o caminho mais barato passando por bomba de gasolina
	 */
	void planGasPumpShortPath(Vertex * src, Vertex * dest, double maxDist);
	/*
	 * retorna o objeto ParkType (parque de estacionamento) de vertice v
	 */
	ParkType * getParkType(Vertex * v);
	/**
	 * Planeia o caminho mais curto de um parque ao destino sem passar por bomba de gasolina
	 */
	ParkType * planDirectShortPath(Vertex * src, Vertex * dest);
	/*
	 * Planeia o caminho mais barato sem passar por bomba de gasolina
	 */
	ParkType * planDirectCheapestPath(Vertex * src, Vertex * dest, double maxDist);

	/*
	 * calcula a distancia na imagem entre dois vertices
	 */
	double distanceBetweenVertex(Vertex * v1, Vertex * v2) ;
	void toogleStreetNodes(string street);

	vector<string> getStreetNames()const;
	vector<DestPlace *> getDestinations()const;
	vector<Vertex*> getStreetNodes(string street);


	Vertex * getVertex(long id);

};


// auxiliary functions


#endif /* SRC_PARKING_H_ */
