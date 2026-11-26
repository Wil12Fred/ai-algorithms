// Unit tests for the chromosome decoding, the objective and the GA.
// The generator is seeded with fixed values, so every run is identical.
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

#include "../xorshift.h"
#include "../matematica.h"
#include "../genetico.h"

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

static void sembrar(long long s) {
	xorshift_x = s;
	xorshift_y = s ^ 123456789;
	xorshift_z = s << 31;
	xorshift_w = s >> 11;
}

// 24 bits = 2 x (sign, 2 integer bits, 9 fraction bits).
static void test_decodificacion() {
	Represent r(24);
	// x1 = +1.5 : sign=1, int=01, frac=1000...
	r.cromosomas[0] = 1; r.cromosomas[2] = 1; r.cromosomas[3] = 1;
	// x2 = -2.25: sign=0, int=10, frac=01000...
	r.cromosomas[13] = 1; r.cromosomas[16] = 1;
	pair<double, double> x = r.getX();
	CHECK(x.first == 1.5);
	CHECK(x.second == -2.25);
}

static void test_funcion_objetivo() {
	Practica2<Individuo> P(10, 10, 24);
	CHECK(fabs(P.func(0, 0) - 1) < 1e-6);       // global maximum at the origin
	CHECK(P.func(1, 0) < 1e-12);                // sinc^2 vanishes at r = 1
	CHECK(P.func(0.5, 0) < P.func(0.1, 0));     // decreasing from the origin
}

// With elitism the GA reaches f > 0.99 (the maximum is 1) for every seed,
// and never ends worse than its initial population.
static void test_genetico_converge() {
	for (long long semilla = 1; semilla <= 5; semilla++) {
		sembrar(semilla * 104729);
		Practica2<Individuo> P(200, 300, 24);
		streambuf* viejo = cout.rdbuf(); ostringstream nulo; cout.rdbuf(nulo.rdbuf());
		Genetico<Practica2<Individuo> > G(&P, 0.3, 0.2, true);
		double inicial = G.obtenerMejor().aptitud;
		Individuo mejor = G.iniciar(false);
		cout.rdbuf(viejo);
		pair<double, double> x = mejor.representacion.getX();
		double f = P.func(x.first, x.second);
		cout << "seed " << semilla << ": f(best) = " << f << endl;
		CHECK(f > 0.99);
		CHECK(mejor.aptitud >= inicial);
		CHECK((int)G.poblacion->size() == 200);
	}
}

int main() {
	test_decodificacion();
	test_funcion_objetivo();
	test_genetico_converge();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "genetic-algorithm: all tests passed" << endl;
	return 0;
}
