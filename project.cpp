/* ASA Project
	*
	*Implementing DFS Algorithm 
**/


//Lots to fix

//Fix all Monday and do the pdf

#include <iostream>
#include <cstdio>
#include <list>
#define NIL -1
using namespace std;
int numberFundamentals = 0;

//Class Graph TODO:describe the object
class Graph {
	//Number of vertices
	int _V; 
	//Array of adjacency lists
	list<int> *adj;

public:
	Graph(int V, int N); 
	void addEdge(int a, int b);
	void apDFS(int a, bool visited[], int d[], int low[], int parent[], bool fundamental[]);
	void printFundamentals();
};

Graph::Graph(int V, int N) {
	this->_V = V;
	adj = new list<int>[V];
	int a,b;//represent edges to add to the graph
	for(int i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		addEdge(a - 1, b - 1);
	}
}

void Graph::addEdge(int a, int b) {
	adj[a].push_back(b);
	adj[b].push_back(a);
}


//parent array is basically the pi
//ap stores all the vertices which are fundamental
void Graph::apDFS(int a, bool visited[], int d[], int low[], int parent[], bool fundamental[]) {
	static int time = 0;
	int children = 0;
	visited[a] = true;
	d[a]= low[a] = ++time;


	list<int>::iterator it;
	for(it = adj[a].begin(); it != adj[a].end(); ++it) {
		int v = *it;

		if(!visited[v]) {
			children++;
			parent[v] = a;
			apDFS(v, visited, d, low, parent, fundamental);


			low[a] = min(low[a], low[v]);

			if(parent[a] == NIL && children > 1) {//if a is root and has at least two children
				fundamental[a] = true;
				numberFundamentals++;
			}
			if(parent[a] != NIL && low[v] >= d[a]) { //if low value of one of its child is more than discovery value of u
				fundamental[a] = true;
				numberFundamentals++;
			}
		}

		else if (v != parent[a])
			low[a] = min(low[a], d[v]);
	}
}

void Graph::printFundamentals() {
	bool *visited = new bool[_V];
	int *d = new int[_V];
	int *low = new int[_V];
	int *parent = new int[_V];
	bool *fundamental = new bool[_V];

	for(int i=0; i < _V; i++) {
		parent[i] = NIL;
		visited[i] = false;
		fundamental[i] = false;
	}

	for(int i=0; i< _V; i++) {
		if(visited[i] == false)
			apDFS(i, visited, d, low, parent, fundamental);
	}

	cout << numberFundamentals << "\n";
	int m = -1, M = -1;
	for(int s = 0, e = _V -1; s < _V && e >= 0; s++, e--) {
		if(m > 0 && M > 0) break;
		if(fundamental[s] == true) m = s + 1;
		if(fundamental[e] == true) M = e + 1;
	}
	cout << m << " " << M << "\n";
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







