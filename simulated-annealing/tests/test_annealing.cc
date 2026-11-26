// Unit tests for simulated annealing on the sinc^2 objective.
// The generator is seeded with fixed values, so every run is identical.
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

#include "../xorshift.h"
#include "../matematica.h"
#include "../genetico.h"
#include "../simulated_annealing.h"

// The algorithm prints every step with cout and printf: silence stdout.
static int stdout_guardado = -1;
static void silenciar() { fflush(stdout); cout.flush(); stdout_guardado = dup(1); int n = open("/dev/null", O_WRONLY); dup2(n, 1); close(n); }
static void restaurar() { fflush(stdout); cout.flush(); dup2(stdout_guardado, 1); close(stdout_guardado); }

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

static void sembrar(long long s) {
	xorshift_x = s;
	xorshift_y = s ^ 123456789;
	xorshift_z = s << 31;
	xorshift_w = s >> 11;
}

// The state is a single solution: the population never grows past one.
static void test_una_sola_solucion() {
	sembrar(99);
	Practica2<Individuo> P(1, 300, 18);
	silenciar();
	Simulated_Annealing<Practica2<Individuo> > SA(&P);
	for (int i = 0; i < 200; i++) {
		SA.generar_nueva_poblacion();
		if (SA.poblacion->size() != 1) { fallos++; break; }
	}
	restaurar();
	CHECK(SA.poblacion->size() == 1);
	CHECK(SA.T < 1 && SA.T > 0);   // the temperature only cools down
}

// From a random start, annealing ends near the global maximum (f = 1),
// far above the first ring of local maxima (f ~ 0.047).
static void test_annealing_converge() {
	for (long long semilla = 1; semilla <= 5; semilla++) {
		sembrar(semilla * 15485863);
		Practica2<Individuo> P(1, 300, 18);
		silenciar();
		Simulated_Annealing<Practica2<Individuo> > SA(&P);
		Individuo mejor = SA.iniciar(false);
		restaurar();
		pair<double, double> x = mejor.representacion.getX();
		double f = P.func(x.first, x.second);
		cout << "seed " << semilla << ": f(best) = " << f << " after " << SA.iteration << " steps" << endl;
		CHECK(f > 0.9);
	}
}

int main() {
	test_una_sola_solucion();
	test_annealing_converge();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "simulated-annealing: all tests passed" << endl;
	return 0;
}
