/*
Description: Reads the distances, data capacities and exchange locations of N
neighborhoods and prints the fiber wiring (MST), the mail delivery route (TSP),
the maximum information flow and the region of each exchange (Voronoi).
Authors: TODO Name - A0XXXXXXX, TODO Name - A0XXXXXXX, TODO Name - A0XXXXXXX
Created: 2026-11-09   Last modified: 2026-11-10
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Edge {
	int u = 0;
	int v = 0;
	int weight = 0;
};

struct Point {
	double x = 0.0;
	double y = 0.0;
};

// Reads an n x n matrix from standard input.
// n: number of rows and columns.
// Returns: the matrix that was read.
vector<vector<int>> readMatrix(int n) {
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}
	return matrix;
}

// Reads n points of the form (x,y) from standard input.
// n: number of points.
// Returns: the list of points.
vector<Point> readPoints(int n) {
	vector<Point> points;
	char symbol = ' ';
	for (int i = 0; i < n; i++) {
		Point p;
		cin >> symbol >> p.x >> symbol >> p.y >> symbol;
		points.push_back(p);
	}
	return points;
}

// Converts a neighborhood index to its name (0 = A, 1 = B, ..., 26 = AA).
// index: index of the neighborhood.
// Returns: the name of the neighborhood.
string nodeName(int index) {
	string name = "";
	index++;
	while (index > 0) {
		index--;
		name = char('A' + index % 26) + name;
		index = index / 26;
	}
	return name;
}

// Compares two edges by their weight, used to sort them.
// a: first edge.
// b: second edge.
// Returns: true if a is lighter than b.
bool compareEdges(Edge a, Edge b) {
	return a.weight < b.weight;
}

// Finds the root of the group that node i belongs to (union-find).
// parent: parent of each node.
// i: node to look for.
// Returns: the root of the group.
int findRoot(vector<int>& parent, int i) {
	if (parent[i] == i) {
		return i;
	}
	parent[i] = findRoot(parent, parent[i]);
	return parent[i];
}

// Part 1: finds the cheapest way to connect all neighborhoods with fiber (Kruskal).
// matrix: distances in km between neighborhoods, 0 means there is no connection.
// Returns: the list of edges of the minimum spanning tree.
vector<Edge> fiberWiring(const vector<vector<int>>& matrix) {
	int n = matrix.size();
	vector<Edge> edges;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (matrix[i][j] > 0) {
				Edge e;
				e.u = i;
				e.v = j;
				e.weight = matrix[i][j];
				edges.push_back(e);
			}
		}
	}
	sort(edges.begin(), edges.end(), compareEdges);

	vector<int> parent(n, 0);
	for (int i = 0; i < n; i++) {
		parent[i] = i;
	}

	vector<Edge> mst;
	int edgesAdded = 0;
	int k = 0;
	while (k < (int)edges.size() && edgesAdded < n - 1) {
		int rootU = findRoot(parent, edges[k].u);
		int rootV = findRoot(parent, edges[k].v);
		if (rootU != rootV) {
			mst.push_back(edges[k]);
			parent[rootU] = rootV;
			edgesAdded++;
		}
		k++;
	}
	return mst;
}

// ==================== PART 2: TODO ====================
// Part 2: finds the shortest route that visits every neighborhood exactly once
// and returns to the first one (Traveling Salesman Problem).
// matrix: distances in km between neighborhoods (Matrix 1).
// Returns: the neighborhood indices in visiting order, starting and ending at 0.
//          Example for the sample input: {0, 1, 2, 3, 0}, printed as "A B C D A".
vector<int> deliveryRoute(const vector<vector<int>>& matrix) {
	vector<int> route;

	// TODO: implement the algorithm here and fill "route".
	// main() already prints whatever this function returns.

	return route;
}

// ==================== PART 3: TODO ====================
// Part 3: finds the maximum information flow from the first neighborhood (A)
// to the last one (Max Flow). The graph is directed: capacities[i][j] can be
// different from capacities[j][i].
// capacities: maximum data capacity from neighborhood i to neighborhood j (Matrix 2).
// Returns: the value of the maximum flow.
int maxFlow(const vector<vector<int>>& capacities) {
	int flow = 0;

	// TODO: implement the algorithm here and store the result in "flow".
	// main() already prints whatever this function returns.

	return flow;
}

// Keeps the part of a polygon that is closer to p than to q.
// A point (x,y) is closer to p when a * x + b * y <= c.
// polygon: vertices of the polygon, in order.
// p: exchange whose side is kept.
// q: exchange whose side is removed.
// Returns: the vertices of the cut polygon.
vector<Point> clipPolygon(const vector<Point>& polygon, Point p, Point q) {
	double a = q.x - p.x;
	double b = q.y - p.y;
	double c = (q.x * q.x + q.y * q.y - p.x * p.x - p.y * p.y) / 2.0;

	vector<Point> result;
	int n = polygon.size();
	for (int i = 0; i < n; i++) {
		Point current = polygon[i];
		Point next = polygon[(i + 1) % n];
		double fCurrent = a * current.x + b * current.y - c;
		double fNext = a * next.x + b * next.y - c;

		if (fCurrent <= EPS) {
			result.push_back(current);
		}

		// The edge crosses the bisector, so we add the crossing point
		bool goesOut = fCurrent < -EPS && fNext > EPS;
		bool goesIn = fCurrent > EPS && fNext < -EPS;
		if (goesOut || goesIn) {
			double t = fCurrent / (fCurrent - fNext);
			Point cross;
			cross.x = current.x + t * (next.x - current.x);
			cross.y = current.y + t * (next.y - current.y);
			result.push_back(cross);
		}
	}
	return result;
}

// Part 4: finds the region of the map that is closest to each exchange (Voronoi).
// exchanges: locations of the exchanges.
// Returns: one polygon per exchange, in the same order as the input.
vector<vector<Point>> voronoiCells(const vector<Point>& exchanges) {
	vector<vector<Point>> cells;
	int n = exchanges.size();
	if (n == 0) {
		return cells;
	}

	double minX = exchanges[0].x;
	double maxX = exchanges[0].x;
	double minY = exchanges[0].y;
	double maxY = exchanges[0].y;
	for (int i = 0; i < n; i++) {
		minX = min(minX, exchanges[i].x);
		maxX = max(maxX, exchanges[i].x);
		minY = min(minY, exchanges[i].y);
		maxY = max(maxY, exchanges[i].y);
	}
	double margin = max(maxX - minX, maxY - minY);
	if (margin == 0.0) {
		margin = 1.0;
	}

	// Every cell starts as a box around all exchanges
	vector<Point> box(4);
	box[0].x = minX - margin;
	box[0].y = minY - margin;
	box[1].x = maxX + margin;
	box[1].y = minY - margin;
	box[2].x = maxX + margin;
	box[2].y = maxY + margin;
	box[3].x = minX - margin;
	box[3].y = maxY + margin;

	for (int i = 0; i < n; i++) {
		vector<Point> cell = box;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				cell = clipPolygon(cell, exchanges[i], exchanges[j]);
			}
		}
		cells.push_back(cell);
	}
	return cells;
}

// Prints the fiber edges as (A,B) and the total distance.
// edges: edges of the minimum spanning tree.
void printFiberWiring(const vector<Edge>& edges) {
	int totalKm = 0;
	for (int i = 0; i < (int)edges.size(); i++) {
		cout << "(" << nodeName(edges[i].u) << "," << nodeName(edges[i].v) << ")";
		if (i < (int)edges.size() - 1) {
			cout << ", ";
		}
		totalKm = totalKm + edges[i].weight;
	}
	cout << endl;
	cout << "Total: " << totalKm << " km" << endl;
}

// Prints a route as neighborhood names separated by spaces.
// route: neighborhood indices in visiting order.
void printRoute(const vector<int>& route) {
	for (int i = 0; i < (int)route.size(); i++) {
		cout << nodeName(route[i]);
		if (i < (int)route.size() - 1) {
			cout << " ";
		}
	}
	cout << endl;
}

// Prints each polygon on its own line as a list of (x,y) points.
// polygons: list of polygons.
void printPolygons(const vector<vector<Point>>& polygons) {
	cout << fixed << setprecision(2);
	for (int i = 0; i < (int)polygons.size(); i++) {
		for (int j = 0; j < (int)polygons[i].size(); j++) {
			cout << "(" << polygons[i][j].x << "," << polygons[i][j].y << ")";
			if (j < (int)polygons[i].size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
}

// Reads the input and prints the result of the four parts.
// Returns: 0 when the program ends correctly.
int main() {
	int n = 0;
	cin >> n;
	vector<vector<int>> distances = readMatrix(n);
	vector<vector<int>> capacities = readMatrix(n);
	vector<Point> exchanges = readPoints(n);

	printFiberWiring(fiberWiring(distances));
	printRoute(deliveryRoute(distances));
	cout << maxFlow(capacities) << endl;
	printPolygons(voronoiCells(exchanges));

	return 0;
}
