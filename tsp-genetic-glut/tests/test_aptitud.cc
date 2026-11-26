// Unit tests for the TSP fitness and the GA that uses it (no OpenGL needed).
// The generator is seeded with fixed values, so every run is identical.
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

#include "../xorshift.h"
#include "../geometria.h"
#include "../grafo.h"
#include "../genetico.h"

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

static void sembrar(long long s) {
	xorshift_x = s;
	xorshift_y = s ^ 123456789;
	xorshift_z = s << 31;
	xorshift_w = s >> 11;
}

static Individuo recorrido(const vector<int>& orden) {
	Represent r((int)orden.size());
	r.ciudades = orden;
	return Individuo(r);
}

// Unit square: the perimeter tour is 4, the "bow tie" is 2 + 2*sqrt(2).
static void test_longitud_conocida() {
	Grafo G;
	G.insertarNodo(Punto(0, 0));
	G.insertarNodo(Punto(1, 0));
	G.insertarNodo(Punto(1, 1));
	G.insertarNodo(Punto(0, 1));
	Problema P(&G, 10, 1);
	Individuo cuadrado = recorrido({0, 1, 2, 3});
	Individuo lazo = recorrido({0, 2, 1, 3});
	CHECK(fabs(P.longitud(cuadrado) - 4.0) < 1e-9);
	CHECK(fabs(P.longitud(lazo) - (2 + 2 * sqrt(2.0))) < 1e-9);
	// shorter tour => higher fitness, since the GA keeps the highest
	CHECK(P.aptitud(cuadrado) > P.aptitud(lazo));
	CHECK(P.aptitud(cuadrado) > 0);
}

// Order crossover and swap mutation must always produce a permutation:
// a tour that visits every city exactly once.
static bool es_permutacion(const Individuo& ind, int n) {
	vector<int> o = ind.representacion.ciudades;
	if ((int)o.size() != n) return false;
	sort(o.begin(), o.end());
	for (int i = 0; i < n; i++) if (o[i] != i) return false;
	return true;
}

static void test_operadores_conservan_permutacion() {
	const int n = 12;
	Grafo G;
	for (int i = 0; i < n; i++) G.insertarNodo(Punto(i, i * i));
	Problema P(&G, 10, 1);
	sembrar(77);
	int malos = 0;
	for (int k = 0; k < 500; k++) {
		Individuo a, b;
		P.generar_nuevo_individuo(a);
		P.generar_nuevo_individuo(b);
		if (!es_permutacion(a, n) || !es_permutacion(b, n)) malos++;
		if (!es_permutacion(a.cruzamiento(&b), n)) malos++;
		if (!es_permutacion(a.mutacion(), n)) malos++;
	}
	CHECK(malos == 0);
}

// 16 cities on a circle, inserted in a scrambled order so the identity
// permutation is a bad tour. The GA (same parameters as the program) must
// return a valid permutation much shorter than a random tour.
static void test_genetico_acorta_el_recorrido() {
	const int n = 16;
	const double R = 300;
	int mezcla[n] = {0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};
	Grafo G;
	for (int i = 0; i < n; i++) {
		double a = 2 * acos(-1.0) * mezcla[i] / n;
		G.insertarNodo(Punto(R * cos(a), R * sin(a)));
	}
	double optimo = n * 2 * R * sin(acos(-1.0) / n);

	sembrar(20180901);
	Problema P(&G, 10, 200);
	Genetico genetico(&P, 0.7, 0.02);
	double suma = 0;
	double mejor_inicial = 1e18;
	for (auto it = genetico.poblacion->begin(); it != genetico.poblacion->end(); it++) {
		double l = P.longitud(*it);
		suma += l;
		mejor_inicial = min(mejor_inicial, l);
	}
	double media_inicial = suma / genetico.poblacion->size();

	Individuo mejor = genetico.iniciar();
	double final_ = P.longitud(mejor);

	vector<int> orden = mejor.representacion.ciudades;
	sort(orden.begin(), orden.end());
	for (int i = 0; i < n; i++) CHECK(orden[i] == i);

	cout << "tour length: random mean " << media_inicial << ", best initial " << mejor_inicial
	     << ", GA " << final_ << ", optimum " << optimo << endl;
	CHECK(final_ >= optimo - 1e-6);
	CHECK(final_ <= mejor_inicial);
	CHECK(final_ < 0.75 * media_inicial);
}

int main() {
	test_longitud_conocida();
	test_operadores_conservan_permutacion();
	test_genetico_acorta_el_recorrido();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "tsp-genetic-glut: all tests passed" << endl;
	return 0;
}
