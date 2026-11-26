#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#include "xorshift.h" //semilla y función para puntos aleatorios
#include "matematica.h" //definiciones basicas
#include "genetico.h"
#include "simulated_annealing.h"
#include "horario.h"

int main(int argc, char **argv){
	SeedXorShift();
	vector<int> H;
	int horas_libres=crearHorario(H,7,2);
	imprimirHorario(H);
	/*Parcial<Individuo> HorarioDeEstudio1(1,300,108,H);
	Simulated_Annealing<Parcial<Individuo> > SA(&HorarioDeEstudio1);
	Individuo mejor=SA.iniciar(false);
	double ma = HorarioDeEstudio1.aptitud(mejor, true);*/
	
	Parcial<Individuo> HorarioDeEstudio(30,300,horas_libres,H);
	Genetico<Parcial<Individuo> > G(&HorarioDeEstudio,0.4,0.3,true);
	Individuo mejorg=G.iniciar(false);
	double ma = HorarioDeEstudio.aptitud(mejorg, true);

	cout << ma << endl;

	return 0;
}
