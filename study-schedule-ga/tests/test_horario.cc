// Unit tests for the timetable and the study-plan fitness.
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
#include "../horario.h"

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

static void sembrar(long long s) {
	xorshift_x = s;
	xorshift_y = s ^ 123456789;
	xorshift_z = s << 31;
	xorshift_w = s >> 11;
}

// Every one of the 7 courses gets its 2 lectures of 3 hours (6 slots),
// none of them is written as 0 (= free hour), and all fall in 07:00-21:59.
static void test_todos_los_cursos_tienen_clases() {
	for (long long semilla = 1; semilla <= 20; semilla++) {
		sembrar(semilla * 7919);
		vector<int> H;
		streambuf* viejo = cout.rdbuf(); ostringstream nulo; cout.rdbuf(nulo.rdbuf());
		int libres = crearHorario(H, 7, 2);
		cout.rdbuf(viejo);
		CHECK(H.size() == 144);
		map<int, int> horas;
		for (int i = 0; i < 144; i++) {
			if (H[i] != 0) {
				horas[H[i]]++;
				CHECK(i % 24 >= 7 && i % 24 <= 21);
			}
		}
		CHECK(horas.size() == 7);
		for (int c = 1; c <= 7; c++) CHECK(horas[c] == 6);
		CHECK(libres == 144 - 7 * 2 * 3);
	}
}

// The problem sees 7 courses, so an individual's genes range over 0..7
// and the fitness (a product over courses 1..7) is positive.
static void test_problema_ve_siete_cursos() {
	sembrar(424242);
	vector<int> H;
	streambuf* viejo = cout.rdbuf(); ostringstream nulo; cout.rdbuf(nulo.rdbuf());
	int libres = crearHorario(H, 7, 2);
	cout.rdbuf(viejo);
	Parcial<Individuo> P(30, 300, libres, H);
	CHECK(P.n_cursos == 7);
	Individuo ind;
	P.generar_nuevo_individuo(ind);
	CHECK(ind.representacion.tamano() == libres);
	for (int i = 0; i < ind.representacion.tamano(); i++) {
		CHECK(ind.representacion.cromosomas[i] >= 0 && ind.representacion.cromosomas[i] <= 7);
	}
	CHECK(P.aptitud(ind) > 0);
}

// With elitism the GA never loses its best plan: the result is at least
// as good as the best individual of the initial population.
static void test_genetico_mejora() {
	sembrar(2018);
	vector<int> H;
	streambuf* viejo = cout.rdbuf(); ostringstream nulo; cout.rdbuf(nulo.rdbuf());
	int libres = crearHorario(H, 7, 2);
	Parcial<Individuo> P(30, 300, libres, H);
	Genetico<Parcial<Individuo> > G(&P, 0.4, 0.3, true);
	double inicial = G.obtenerMejor().aptitud;
	Individuo mejor = G.iniciar(false);
	cout.rdbuf(viejo);
	CHECK(mejor.aptitud >= inicial);
	CHECK(mejor.aptitud > 0);
}

int main() {
	test_todos_los_cursos_tienen_clases();
	test_problema_ve_siete_cursos();
	test_genetico_mejora();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "study-schedule-ga: all tests passed" << endl;
	return 0;
}
