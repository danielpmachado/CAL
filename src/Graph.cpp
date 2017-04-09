/*
 * Graph.cpp
 *
 *  Created on: 01/04/2017
 *      Author: bibib
 */
#include "Graph.h"
/*
 * CLASS VERTEX
 */

Vertex::Vertex(long id, double lon, double lat): longitude(lon),latitude(lat), visited(false), processing(false), indegree(0), dist(0), inQueue(false) {

	this->id = id;
	path = NULL;
}

void Vertex::addEdge(Vertex *dest, Road * road, double w, bool real) {
	Edge *edgeD = new Edge(dest, road, w, real);
	adj.push_back(edgeD);
}
vector<Edge *> Vertex::getAdj() {
	return adj;
}
long Vertex::getID() const {
	return id;
}

double Vertex::getLongitude() const {
	return longitude;
}

double Vertex::getLatitude() const {
	return latitude;
}



long Vertex::getDist() const {
	return this->dist;
}

void Vertex::setLongitude(long lon) {
	this->longitude = lon;
}

void Vertex::setLatitude(long lat) {
	this->latitude = lat;
}

void Vertex::setID(long id) {
	this->id = id;
}

void Vertex::setDist(long dist){
	this->dist= dist;
}


int Vertex::getIndegree() const {
	return this->indegree;
}

bool Vertex::removeEdgeTo(Vertex *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge*>::iterator it= adj.begin();
	typename vector<Edge*>::iterator ite= adj.end();
	while (it!=ite) {
		if ((*it)->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

Edge * Vertex::getEdgeToVertex(Vertex * dest) {
	for(Edge * e : adj) {
		if(e->getDest() == dest) {
			return e;
		}
	}
	return NULL;
}
bool Vertex::isAccessible() const{
	return visited;
}
/*
 * CLASS EDGE
 */
int Edge::edgesID = 0;
Edge::Edge(Vertex *d, Road * road, double w, bool real): dest(d), weight(w){
	edgesID++;
	this->id = edgesID;
	this->road = road;
	this->real = real;
	inGraphViewer = false;
}
Road * Edge::getRoad () const {
	return road;
}
Vertex * Edge::getDest() {
	return dest;
}
int Edge::getID() {
	return id;
}
double Edge::getWeight() {return weight;}
bool Edge::isInGraphViewer() {
	return inGraphViewer;
}
void Edge::setInGraphViewer() {
	inGraphViewer = inGraphViewer ? false : true;
}
bool Edge::isReal() {
	return real;
}

/*
 * CLASS GRAPH
 */
int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex * > Graph::getVertexSet() {
	return vertexSet;
}

bool Graph::addVertex(Vertex * v) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it) == v) return false;

	vertexSet.push_back(v);
	return true;
}

bool Graph::addEdge(int sourcID, int destID, double w, Road * road, bool real) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->getID() == sourcID )
			{ vS=*it; found++;}
		if ( (*it)->getID() == destID )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD, road, w, real);

	return true;
}
bool Graph::removeVertex(Vertex * v) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it) == v) {
			Vertex * vertexRemoved= *it;
			vertexSet.erase(it);
			typename vector<Vertex*>::iterator it1= vertexSet.begin();
			typename vector<Vertex*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(vertexRemoved);
			}

			typename vector<Edge*>::iterator itAdj= vertexRemoved->adj.begin();
			typename vector<Edge*>::iterator itAdje= vertexRemoved->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				(*itAdj)->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}
Vertex * Graph::getVertex(long id) {
	for (int i = 0; i < vertexSet.size(); i++) {
		if(vertexSet[i]->getID() == id) {
			return vertexSet[i];
		}
	}
	return NULL;
}

void Graph::dfs(Vertex * origin) {
	typename vector<Vertex*>::iterator it= vertexSet.begin();
	typename vector<Vertex*>::iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	dfsAux(origin);
}

void Graph::dfsAux(Vertex *v) {
	v->visited = true;
	typename vector<Edge*>::iterator it= (v->adj).begin();
	typename vector<Edge*>::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( ((*it)->dest->visited == false) && (*it)->isReal() ){
	    	dfsAux((*it)->dest);
	    }
}

vector<Vertex*> Graph::getSources() {
	vector< Vertex* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}

void Graph::dijkstraShortestPathByFoot(Vertex * v) {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = LONG_MAX;
	}

	v->dist = 0;
	ptrVertex node = ptrVertex(v);
	priority_queue< ptrVertex > q;
	q.push(node);
	v->inQueue = true;

	while( !q.empty() ) {
		Vertex * processingVertex = q.top().getNode(); q.pop();
		processingVertex->inQueue = false;
		for(unsigned int i = 0; i < processingVertex->adj.size(); i++) {
			Vertex* w = processingVertex->adj[i]->dest;
			if( w->dist > (processingVertex->dist+ processingVertex->adj[i]->weight) ) {
				w->dist = (processingVertex->dist+ processingVertex->adj[i]->weight);
				w->path = processingVertex;
				if(!(w->inQueue)) {
					ptrVertex ptrW = ptrVertex(w);
					q.push(ptrW);
					w->inQueue = true;
				}
			}
		}
	}
}

void Graph::dijkstraShortestPathByCar(Vertex * v) {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = LONG_MAX;
	}

	v->dist = 0;
	ptrVertex node = ptrVertex(v);
	priority_queue< ptrVertex > q;
	q.push(node);
	v->inQueue = true;

	while( !q.empty() ) {
		Vertex * processingVertex = q.top().getNode(); q.pop();
		processingVertex->inQueue = false;
		for(unsigned int i = 0; i < processingVertex->adj.size(); i++) {
			if(processingVertex->adj[i]->isReal()) {
				Vertex* w = processingVertex->adj[i]->dest;
				if( w->dist > (processingVertex->dist+ processingVertex->adj[i]->weight) ) {
					w->dist = (processingVertex->dist+ processingVertex->adj[i]->weight);
					w->path = processingVertex;
					if(!(w->inQueue)) {
						ptrVertex ptrW = ptrVertex(w);
						q.push(ptrW);
						w->inQueue = true;
					}
				}
			}
		}
	}
}

vector<Vertex *> Graph::getPath(Vertex * origin, Vertex * dest){

	list<Vertex *> buffer;
	Vertex * v = dest;
	//cout << v->info << " ";
	buffer.push_front(v);
	while ( v->path != NULL &&  v->path != origin) {
		v = v->path;
		buffer.push_front(v);
	}
	if( v->path != NULL )
		buffer.push_front(v->path);


	vector<Vertex *> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}


vector<long> Graph::searchStreetNodes(string street) {
    for (Vertex* v : vertexSet) {
    	v->visited = false;
    }
	vector<long> streetVertex;
    typename vector<Vertex*>::iterator it;
    bool found = false;

    for (it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->visited = false;
    }

    for (it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if (!(*it)->visited)
            searchStreetNodes(*it, street, streetVertex);
    }

    return streetVertex;
}

void Graph::searchStreetNodes(Vertex * v,string street, vector<long> &streetVertex) const {
    v->visited = true;


    for (Edge * e : v->getAdj()) {

        if(e->road->getName() == street && !e->dest->visited){

            streetVertex.push_back(v->getID());
            streetVertex.push_back(e->dest->getID());
        }

        if (!e->dest->visited)
            searchStreetNodes(e->dest,street, streetVertex);


    }

}

/*
 * CLASS PTRVERTEX
 */
ptrVertex::ptrVertex(Vertex * v) {
	this->v = v;
}
Vertex * ptrVertex::getNode() const {
	return v;
}
void ptrVertex::setNode(Vertex * v) {
	this->v = v;
}
bool ptrVertex::operator<(const ptrVertex &v2) const {
	return v->getDist() > v2.getNode()->getDist();
}

/*
 * CLASS CLOSESTVERTEX
 */
closestVertex::closestVertex(Vertex * v, double dist) {
	this->v = v;
	this->dist = dist;
}
Vertex * closestVertex::getNode() const {
	return v;
}
void closestVertex::setNode(Vertex * v) {
	this->v = v;
}
double closestVertex::getDist() const {
	return dist;
}
void closestVertex::setDist(double dist) {
	this->dist = dist;
}
bool closestVertex::operator<(const closestVertex &v2) const {
	return dist > v2.getDist();
}

/*
 * CLASS CHEAPESTVERTEX
 */

cheapestVertex::cheapestVertex(Vertex * v, double price) {
	this->v = v;
	this->price = price;
}
Vertex * cheapestVertex::getNode() const {
	return v;
}
void cheapestVertex::setNode(Vertex * v) {
	this->v = v;
}
double cheapestVertex::getPrice() const {
	return price;
}
void cheapestVertex::setPrice(double price) {
	this->price = price;
}
bool cheapestVertex::operator<(const cheapestVertex &v2) const {
	return price > v2.getPrice();
}
