/*
 * Estacionamento.h
 */

#ifndef SRC_PARKINGSYSTEM_H_
#define SRC_PARKINGSYSTEM_H_

class ParkingSystem {
private:
	GraphViewer *gv; /** < Pointer to Graph Viewer Interface*/
	Graph mapGraph; /** < Graph that contains the map */
	map<unsigned long, Road *> roads;
	map<unsigned long, GasPump *> gasPumps;
	map<unsigned long, Park *>parks;
	const static string START_NODE_COLOR; /** < Start node color */
	const static string PATH_FOUND_COLOR; /** < Nodes in the path color*/
	const static string END_NODE_COLOR; /** < End node color*/
	const static string POI_NODE_COLOR; /** < Points of interest color*/
	const static float MAX_LAT; /** < Maximum latitude*/
	const static float MIN_LAT; /** < Minimum latitude*/
	const static float MAX_LON; /** < Maximum longitude*/
	const static float MIN_LON; /** < Minimum longitude*/
	const static int IMAGE_X; /** < Image width*/
	const static int IMAGE_Y; /** < Image height*/
public:
	/**
	 * @brief ParkingSystem constructor
	 *
	 * @param windowWidth Graphical interface window width
	 * @param windowHeight Graphical interface window height
	 */
	ParkingSystem(unsigned int windowWidth, unsigned int windowHeight);
	/**
	 * @brief inicia o programa
	 */
	void start();
	/**
	 * @brief lê a informação dos nós que se encontra no ficheiro mapA.txt
	 */
	void readNodes(const char* filename);
	/**
	 * @brief lê a informação das ruas que se encontra no ficheiro mapB.txt
	 */
	void readRoads(const char* filename);
	/**
	 * @brief lê a informação das arestas do grafo que se encontra no ficheiro mapC.txt
	 */
	void readEdges(const char *filename);
	/**
	 * @brief Computes the prefix of the given pattern
	 *
	 * @param pattern Pattern to compute the prefix
	 * @param prefix Prefix
	 */
	static void computePrefix(const string &pattern, int prefix[]);
	/**
	 * @brief lê a informação sobre as bombas de gasolina guardada no ficheiro gasPump.txt
	 */
	void readGasPumps(const char* filename);
	/**
	 * @brief lê a informação sobre os parques de estacionamento guardada no ficheiro park.txt
	 */
	void readParks(const char* filename);
	/**
	 * @brief Uses the KMP algorithm to find an exact match.
	 *
	 * @param text Text to search in
	 * @param pattern Pattern to search for
	 */
	static int exactMatch(const string &text, const string &pattern);

	/**
	 * @brief Gets the edit distance between pattern and text
	 *
	 * @param pattern Pattern to search for
	 * @param text Text to search in
	 *
	 * @return Returns the edit distance
	 */
	static unsigned int editDistance(const string &pattern, const string &text);

	/**
	 * @brief lê todos os ficheiros e preenche o grafo
	 *
	 * @return Returns 0 on success.
	 */
	int loadFiles();
	/**
	 * @brief pede ao utilizador para introduzir os dados do caminho a traçar e processa-os
	 */
	void askForPath();
	/**
	 * @brief Desenha o caminho
	 *
	 * @param path caminho a ser desenhado
	 * @param start ponto de origem
	 * @param destination ponto de destino
	 */
	void displayPath(const list<Vertex*> &path, Vertex* start,
			Vertex* destination);

	/**
	 * @brief adiciona os nós e arestas do grafo ao GraphViewer
	 */
	void fillGraphViewer();

	/**
	 * @brief lê o input do utilizador (que é um ponto/vértice de destino do caminho a traçar)
	 *
	 * @return Returns the vertex read.
	 */
	Vertex* readVertex();

	/**
	 * @brief adiciona os nós ao GraphViewer
	 */
	void addNodesToGraphViewer();

	/**
	 * @brief adiciona as arestas ao GraphViewer
	 */
	void addEdgesToGraphViewer();

	/**
	 * @brief converte a longitude em coordenadas x no ecrã
	 *
	 * @param longitude longitude a ser convertida
	 *
	 * @return Returns x resultante da conversão
	 */
	int convertLongitudeToX(float longitude);

	/**
	 * @brief converte a latitude em coordenadas y no ecrã
	 *
	 * @param latitude latitude a ser convertida
	 *
	 * @return Returns y resultante da conversão
	 */
	int convertLatitudeToY(float latitude);
};


#endif /* SRC_PARKINGSYSTEM_H_ */
