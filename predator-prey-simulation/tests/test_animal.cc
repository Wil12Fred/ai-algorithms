// Unit tests for the animal and grass rules (animal.h, grass.h, utility.h).
#include <iostream>
#include <vector>
#include <map>
#include <new>
#include <cstring>
#include <stdlib.h>

using namespace std;

typedef pair<int,int> pii;

#include "../utility.h"
#include "../grass.h"
#include "../animal.h"

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

static void test_coordenadas() {
	CHECK(isValidCoor(make_pair(0, 0), 20));
	CHECK(isValidCoor(make_pair(19, 19), 20));
	CHECK(!isValidCoor(make_pair(-1, 0), 20));
	CHECK(!isValidCoor(make_pair(0, 20), 20));
}

// A new animal starts its reproduction counter at 0, whatever was in the
// memory it was built on (the counter used to be left uninitialised).
static void test_contador_inicializado() {
	alignas(animal) unsigned char memoria[sizeof(animal)];
	memset(memoria, 0x7f, sizeof memoria);
	animal* a = new (memoria) animal();
	CHECK(a->timeToReproduce == 0);
	CHECK(a->isLive());
	a->~animal();
}

static animal nuevo(int t, int d, int v) {
	animal a;
	a.coor = make_pair(10, 10);
	a.t = t; a.d = d; a.v = v; a.n = 20;
	return a;
}

// Every t turns an animal spawns exactly d offspring at its position.
static void test_reproduccion() {
	srand(1);
	animal a = nuevo(5, 3, 1000);
	for (int turno = 1; turno <= 10; turno++) {
		a.act_pr();
		a++;
		if (a.comer) a.eat();  // keep it fed
		int esperado = 3 * (turno / 5);
		CHECK((int)a.desc.size() == esperado);
	}
	for (size_t i = 0; i < a.desc.size(); i++) {
		CHECK(a.desc[i]->t == 5 && a.desc[i]->d == 3 && a.desc[i]->v == 1000);
	}
}

// An animal that never eats dies on its (v+1)-th turn; one that eats
// resets the counter and survives.
static void test_hambre() {
	srand(2);
	animal a = nuevo(1000, 0, 4);
	for (int i = 0; i < 4; i++) { a.act_pr(); a++; CHECK(a.isLive()); }
	a.act_pr(); a++;
	CHECK(!a.isLive());

	animal b = nuevo(1000, 0, 4);
	for (int i = 0; i < 50; i++) { b.act_pr(); b++; b.eat(); }
	CHECK(b.isLive());
}

// Moves always stay on the grid (the probability of leaving it is 0).
static void test_movimiento_dentro_de_la_grilla() {
	srand(3);
	animal a = nuevo(1000, 0, 1000000);
	a.coor = make_pair(0, 0);
	for (int i = 0; i < 5000; i++) {
		a.act_pr(); a++; a.eat();
		CHECK(isValidCoor(a.coor, 20));
	}
}

// Grass regrows by one every t ticks, only next to other grass, and never
// goes below zero when eaten.
static void test_pasto() {
	grass g; g.t = 3; g.amount = 0;
	g.hasNeighbor = false;
	for (int i = 0; i < 9; i++) g++;
	CHECK(g.amount == 0);
	g.hasNeighbor = true;
	for (int i = 0; i < 9; i++) g++;
	CHECK(g.amount == 3);
	for (int i = 0; i < 5; i++) g--;
	CHECK(g.amount == 0);
}

int main() {
	test_coordenadas();
	test_contador_inicializado();
	test_reproduccion();
	test_hambre();
	test_movimiento_dentro_de_la_grilla();
	test_pasto();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "predator-prey-simulation: all tests passed" << endl;
	return 0;
}
