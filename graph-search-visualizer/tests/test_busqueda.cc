// Search algorithms on small hand-built graphs (no OpenGL needed).
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

#include "../geometria.h"
#include "../grafo.h"

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

// Path from end back to begin through Anterior, as node ids begin..end.
static vector<int> camino(const vector<int>& Anterior, int begin, int end) {
	vector<int> c;
	for (int v = end; v != -1 && (int)c.size() <= (int)Anterior.size(); v = Anterior[v]) c.push_back(v);
	reverse(c.begin(), c.end());
	return c;
}

static bool camino_valido(Grafo& G, const vector<int>& c) {
	for (int i = 0; i + 1 < (int)c.size(); i++) {
		if (G.nodos[c[i]]->aristas.count(c[i + 1]) == 0) return false;
		if (G.Obstaculos.count(make_pair(c[i], c[i + 1]))) return false;
	}
	return true;
}

// 3x3 grid, ids row by row:   0 1 2 / 3 4 5 / 6 7 8
static void grilla(Grafo& G) {
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) G.insertarNodo(Punto(x, y));
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) {
			if (x < 2) G.insertarArista(Punto(x, y), Punto(x + 1, y));
			if (y < 2) G.insertarArista(Punto(x, y), Punto(x, y + 1));
		}
}

// BFS finds a shortest path (in edges): 0 -> 8 needs 4 edges.
static void test_bfs_camino_mas_corto() {
	Grafo G; grilla(G);
	vector<pair<int,int> > visitados; vector<int> Anterior;
	CHECK(G.bfs(0, 8, visitados, Anterior));
	vector<int> c = camino(Anterior, 0, 8);
	CHECK(c.front() == 0 && c.back() == 8);
	CHECK(c.size() == 5);
	CHECK(camino_valido(G, c));
}

// Obstacle edges are never crossed; a node cut off by obstacles is unreachable.
static void test_obstaculos() {
	Grafo G;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) G.insertarNodo(Punto(x, y));
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) {
			// node 8 = (2,2) only reachable through obstacle edges
			if (x < 2) G.insertarArista(Punto(x, y), Punto(x + 1, y), y == 2 && x == 1);
			if (y < 2) G.insertarArista(Punto(x, y), Punto(x, y + 1), x == 2 && y == 1);
		}
	vector<pair<int,int> > v1, v2; vector<int> A1, A2;
	CHECK(!G.bfs(0, 8, v1, A1));
	CHECK(!G.mejorElPrimero(0, 8, v2, A2));
	for (auto& e : v1) CHECK(G.Obstaculos.count(e) == 0);
	for (auto& e : v2) CHECK(G.Obstaculos.count(e) == 0);
	// 7 is still reachable, around the obstacles
	vector<pair<int,int> > v3; vector<int> A3;
	CHECK(G.bfs(0, 7, v3, A3));
	CHECK(camino_valido(G, camino(A3, 0, 7)));
}

// Greedy best-first reaches the goal with a valid path and, on a grid with a
// straight-line heuristic, explores fewer edges than BFS.
static void test_mejor_el_primero() {
	Grafo G;
	const int n = 6;
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) G.insertarNodo(Punto(x, y));
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			if (x < n - 1) G.insertarArista(Punto(x, y), Punto(x + 1, y));
			if (y < n - 1) G.insertarArista(Punto(x, y), Punto(x, y + 1));
		}
	int fin = n * n - 1;
	vector<pair<int,int> > vb, vg; vector<int> Ab, Ag;
	CHECK(G.bfs(0, fin, vb, Ab));
	CHECK(G.mejorElPrimero(0, fin, vg, Ag));
	vector<int> c = camino(Ag, 0, fin);
	CHECK(c.front() == 0 && c.back() == fin);
	CHECK(camino_valido(G, c));
	CHECK(vg.size() < vb.size());
}

int main() {
	test_bfs_camino_mas_corto();
	test_obstaculos();
	test_mejor_el_primero();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "graph search: all tests passed" << endl;
	return 0;
}
