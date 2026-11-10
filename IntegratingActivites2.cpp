/*

The input format:

4                     ← N = number of neighborhoods (A, B, C, D)

 0 16 45 32           ← Matrix 1 (N×N): distances in km
16  0 18 21              Symmetric: A–B = B–A = 16
45 18  0  7              0 on the diagonal
32 21  7  0

 0 48 12 18           ← Matrix 2 (N×N): data capacities
52  0 42 32              NOT symmetric: A→B = 48, B→A = 52
18 46  0 56              Treat it as a directed graph
24 36 52  0

(200,500)             ← Coordinates (x,y) of the exchanges ("centrales")
(300,100)
(450,150)
(520,480)

*/

/*

Part 1: Fiber wiring (Minimum Spanning Tree)
What they want: the cheapest set of cables (by total km) that still connects every neighborhood, directly or through other neighborhoods.
Algorithm: Kruskal (sort the edges, then union-find) or Prim. This is the MST from the Greedy unit.
Uses: Matrix 1. A 0 off the diagonal probably means you can’t run a cable there, so skip those edges.
Output: a list of edges, e.g. (C,D) (A,B) (B,C).
Example answer: (C,D)=7, (A,B)=16, (B,C)=18, total 41 km.

*/

#include <iostream>
#include <vector>
#include <algorithm>

// Note on "std::"
// Everything from the C++ Standard Library (cin, cout, vector, sort, ...) lives
// inside a namespace called "std". A namespace is a named group that keeps
// library names separate from our own names. "std::" means "the one from the
// standard library", e.g. std::vector is the standard library's vector.
// We write std:: explicitly instead of "using namespace std;" so that our own
// names (e.g. a helper called distance or count) never clash with std's names.

struct Edge {
    int u, v; // neighborhood indices (0=A, 1=B, ...)
    int weight; //km
};

struct Point {
    double x, y;
};

std::vector<std::vector<int>> readMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int d;
            std::cin >> d;
            matrix[i][j] = d;
        }
    }
    return matrix;
}

std::vector<Edge> fiberWiring (const std::vector<std::vector<int>>& matrix) {
    std::vector<Edge> edges;
return edges;
}

int main() {
    int MatrixSize = 0;
    char c;
    std::vector<Point> exchanges;

    std::cin >> MatrixSize;
    std::cout << MatrixSize << std::endl;
    std::vector<std::vector<int>> distances = readMatrix(MatrixSize);
    std::vector<std::vector<int>> capacities = readMatrix(MatrixSize);

    for (int i=0; i<MatrixSize; i++) {
        Point p;
        std::cin >> c >> p.x >> c >> p.y >> c;
        exchanges.push_back(p);
    }
    
    fiberWiring(distances);
    return 0;
}