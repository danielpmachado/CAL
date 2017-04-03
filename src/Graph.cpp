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
Vertex::Vertex(int id, double lon, double lat, double x, double y): longitude(lon),latitude(lat), visited(false), processing(false), indegree(0), dist(0), inQueue(false) {
	this->id = id;
	this->x = x;
	this->y = y;
	path = NULL;
}

void Vertex::addEdge(Vertex *dest, Road * road, double w) {
	Edge *edgeD = new Edge(dest, road, w);
	adj.push_back(edgeD);
}
int Vertex::getID() const {
	return id;
}

double Vertex::getLongitude() const {
	return longitude;
}

double Vertex::getLatitude() const {
	return latitude;
}

double Vertex::getX() const {
	return x;
}
double Vertex::getY() const {
	return y;
}

int Vertex::getDist() const {
	return this->dist;
}

void Vertex::setLongitude(double lon) {
	this->longitude = lon;
}

void Vertex::setLatitude(double lat) {
	this->latitude = lat;
}

void Vertex::setID(int id) {
	this->id = id;
}

void Vertex::setX(double x) {
	this->x = x;
}
void Vertex::setY(double y) {
	this->y = y;
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

/*
 * CLASS EDGE
 */
int Edge::edgesID = 0;
Edge::Edge(Vertex *d, Road * road, double w): dest(d), weight(w){
	edgesID++;
	this->id = edgesID;
	this->road = road;
	inGraphViewer = false;
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

/*
 * CLASS GRAPH
 */
int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex * > Graph::getVertexSet() const {
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
bool Graph::addEdge(int sourcID, int destID, double w, Road * road) {
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
	vS->addEdge(vD, road, w);

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
Vertex * Graph::getVertex(int id) const {
	for (int i = 0; i < vertexSet.size(); i++) {
		if(vertexSet[i]->getID() == id) {
			return vertexSet[i];
		}
	}
	return NULL;
}
vector<Vertex*> Graph::dfs() const {
	typename vector<Vertex*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<Vertex*> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

void Graph::dfs(Vertex *v,vector<Vertex*> &res) const {
	v->visited = true;
	res.push_back(v);
	typename vector<Edge*>::iterator it= (v->adj).begin();
	typename vector<Edge*>::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( (*it)->dest->visited == false ){
	    	dfs((*it)->dest, res);
	    }
}

vector<Vertex*> Graph::getSources() const {
	vector< Vertex* > buffer;
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if( vertexSet[i]->indegree == 0 ) buffer.push_back( vertexSet[i] );
	}
	return buffer;
}

void Graph::dijkstraShortestPath(Vertex * v) {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	v->dist = 0;
	priority_queue< Vertex* > q;
	q.push(v);
	v->inQueue = true;

	while( !q.empty() ) {
		Vertex * processingVertex = q.top(); q.pop();
		processingVertex->inQueue = false;
		for(unsigned int i = 0; i < processingVertex->adj.size(); i++) {
			Vertex* w = processingVertex->adj[i]->dest;
			if( w->dist > (processingVertex->dist+ processingVertex->adj[i]->weight) ) {
				w->dist = (v->dist+ v->adj[i]->weight);
				w->path = processingVertex;
				if(!(w->inQueue)) {
					q.push(w);
					w->inQueue = true;
				}
			}
		}
	}
}

vector<Vertex *> Graph::getPath(Vertex * origin, Vertex * dest){

	list<Vertex *> buffer;
	Vertex * v = dest;
	//cout << v->info << " ";
	buffer.push_front(dest);
	while ( v->path != NULL &&  v->path != origin) {
		v = v->path;
		buffer.push_front(v);
	}
	if( v->path != NULL )
		buffer.push_front(v->path);
	else
		buffer.push_front(v);


	vector<Vertex *> res;
	while( !buffer.empty() ) {
		res.push_back( buffer.front() );
		buffer.pop_front();
	}
	return res;
}

