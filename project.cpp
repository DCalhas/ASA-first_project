/* ASA First Project
	*
	*Implementing DFS Algorithm 
	*The instructions of the project are to find the fundamental points in a network
	*In this code fundamental points are treated as Articulation Points
	*The DFS (Deep-First Search) is used in order to find those points
**/


/** *Legend:
	*AP's - Articulation Points
*/

#include <iostream>
#include <cstdio>
#include <list>
#define NIL -1
using namespace std;


/*	*Graph class:
	*_V - number of vertices of the undirected graph
	*_adj - representation of the graph as an array of adjacency lists
	*_min _max Articulations are used for the output of these program
	*the same for _numberFundamentals that refers to the number of AP's
*/
class Graph {
	int _V; 
	list<int> *_adj;

	int _minArticulation;
	int _maxArticulation;
	int _numberFundamentals;

public:
	Graph(int V, int N); 
	void addEdge(int a, int b);
	void apDFS(int a, bool visited[], int disc[], int low[], int parent[]);
	void printFundamentals();
};

Graph::Graph(int V, int N) {
	this->_V = V;
	_adj = new list<int>[V];
	_minArticulation = -1;			//both min and max Articulations start at -1 in case there are no AP's
	_maxArticulation = -1;
	_numberFundamentals = 0;		
	int a,b;          				//represent edges to add to the graph
	for(int i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		addEdge(a - 1, b - 1);
	}
}

void Graph::addEdge(int a, int b) {
	_adj[a].push_back(b);
	_adj[b].push_back(a);
}


//parent array is basically the pi(Greek letter) 
//low attribute is critical for the discovery of the AP's
void Graph::apDFS(int a, bool visited[], int disc[], int low[], int parent[]) {
	static int time = 0;
	int children = 0;
	visited[a] = true;  //once apDFS is called for a vertex a, its state changes to visited
	disc[a]= low[a] = ++time; //set discovery time of the vertex as well as the low attribute 


	list<int>::iterator it;
	for(it = _adj[a].begin(); it != _adj[a].end(); ++it) {
		int v = *it;
		//analysing the adjacent vertices if they were not visited ...
		if(!visited[v]) {
			children++;
			parent[v] = a;
			apDFS(v, visited, disc, low, parent);


			low[a] = min(low[a], low[v]);
			//There are two cases for a vertex to be an AP
			//case 1 - if the vertex is a root and has at least two children
			if(parent[a] == NIL && children > 1) {
				//Setting the _min and _max if... and increment of the number of AP's attribute
				if(a < _minArticulation || _minArticulation == -1) _minArticulation = a;
				if(a > _maxArticulation) _maxArticulation = a;
				_numberFundamentals++;
			}
			//case 2 - if the vertex it's not the root of the DFS tree and the low value of one of his children is more than its discovery value 
			if(parent[a] != NIL && low[v] >= disc[a]) {
				if(a < _minArticulation || _minArticulation == -1) _minArticulation = a;
				if(a > _maxArticulation) _maxArticulation = a;
				_numberFundamentals++;
			}
		}

		//FIXME: know more about the low attribute
		else if (v != parent[a])
			low[a] = min(low[a], disc[v]);
	}
}

void Graph::printFundamentals() {
	//initialization of the apDFS method attributes where the DFS algorithm is going to be performed
	bool *visited = new bool[_V];
	int *disc = new int[_V];
	int *low = new int[_V];
	int *parent = new int[_V];

	//set every vertex of the Graph with parent attribute = NIL and as not visited
	for(int i=0; i < _V; i++) {
		parent[i] = NIL;
		visited[i] = false;
	}

	//run the apDFS for every vertex that is not visited
	//the DFS algorithm which takes part in this program starts here!
	for(int i=0; i< _V; i++) {
		if(visited[i] == false)
			apDFS(i, visited, disc, low, parent);
	}

	//set output values
	if(_minArticulation != -1) _minArticulation++;
	if(_maxArticulation != -1) _maxArticulation++; 
	//OUTPUT READY! 
	cout << _numberFundamentals << "\n";
	cout << _minArticulation << " " << _maxArticulation << "\n";
}

int main() {
	//V - number of vertices || N - number of edges 
	int V, N;
	scanf("%d %d", &V, &N);
	//if graph is conex then it has no articulation points TODO:verify a simple way to deny right away
	Graph graph(V,N);
	graph.printFundamentals();
	return 0;
}







