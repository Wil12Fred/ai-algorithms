// Keyboard handlers: Esc, '+' and '-' are ordinary ASCII keys, so they must
// be handled by the glutKeyboardFunc callback (keyboardPress); arrow keys
// stay on the glutSpecialFunc callback (keyPress). No window is opened:
// glutPostRedisplay is replaced by a counter.
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

static int redibujados = 0;
#define glutPostRedisplay() (redibujados++)

#include "../geometria.h"
#include "../camara.h"
#include "../windowControl.h"

static int fallos = 0;
#define CHECK(cond) do { if (!(cond)) { cerr << __FILE__ << ":" << __LINE__ << ": FAIL: " #cond << endl; fallos++; } } while (0)

static void test_zoom() {
	CAMARA.rotate = 1;
	keyboardPress('+', 0, 0);
	CHECK(CAMARA.rotate == 2);
	CHECK(redibujados == 1);
	keyboardPress('-', 0, 0);
	keyboardPress('-', 0, 0);
	CHECK(CAMARA.rotate == 0.5);
	CHECK(redibujados == 3);
	keyboardPress('a', 0, 0);  // unmapped key: no redraw
	CHECK(redibujados == 3);
}

static void test_flechas_siguen_en_teclas_especiales() {
	CAMARA.rotate = 1;
	CAMARA.CENTER = Punto(0, 0);
	keyPress(GLUT_KEY_LEFT, 0, 0);
	CHECK(CAMARA.CENTER.x == 15);
	keyPress(GLUT_KEY_UP, 0, 0);
	CHECK(CAMARA.CENTER.y == -15);
}

static void test_esc_sale() {
	pid_t pid = fork();
	if (pid == 0) {
		keyboardPress(27, 0, 0);
		_exit(3);  // reached only if Esc did not exit
	}
	int estado = 0;
	waitpid(pid, &estado, 0);
	CHECK(WIFEXITED(estado) && WEXITSTATUS(estado) == 0);
}

// The program must register the ASCII handler with GLUT.
static void test_main_registra_teclado() {
	const char* fuentes[] = {"busqueda.cc", "main.cc"};
	bool registrado = false;
	for (const char* f : fuentes) {
		ifstream in(f);
		string linea;
		while (getline(in, linea))
			if (linea.find("glutKeyboardFunc(keyboardPress)") != string::npos) registrado = true;
	}
	CHECK(registrado);
}

int main() {
	test_zoom();
	test_flechas_siguen_en_teclas_especiales();
	test_esc_sale();
	test_main_registra_teclado();
	if (fallos) { cerr << fallos << " check(s) failed" << endl; return 1; }
	cout << "keyboard handlers: all tests passed" << endl;
	return 0;
}
