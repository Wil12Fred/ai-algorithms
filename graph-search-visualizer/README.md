# BusquedaInteligenciaArtificial

Graph search visualiser in C++ and OpenGL/GLUT. Assignment 1 ("Tarea 1:
Búsqueda") of a university Artificial Intelligence course, 2017. Identifiers,
prompts and comments are in Spanish.

![Best-first search on a 40-node map](docs/screenshot.png)

## What it does

1. Asks for a number of nodes and scatters them at random in an 850x850 area.
2. Connects them with a Delaunay triangulation (O(n^4), so keep `n` in the
   tens), capping node degree, and marks about 1 in 10 edges as **obstacles**
   (drawn orange) that a search may not cross.
3. Searches from node `0` (green square) to the last node (red square) with
   either:
   - **option 1**: breadth-first search. The prompt calls it "Búsqueda en
     Profundidad" (depth-first), but `Grafo::bfs` explores in BFS order;
   - **option 2**: greedy best-first search, using straight-line distance to
     the goal as the heuristic.
4. Draws the explored edges in blue and the path found in cyan, and prints
   `Llego` (reached) or `No Llego` (not reached) followed by the node ids on
   the path, goal to start.

## Build and run

Needs a C++11 compiler, `make` and OpenGL/GLUT
(Debian/Ubuntu: `sudo apt install freeglut3-dev`; Arch: `freeglut`; macOS: the
system frameworks).

```bash
make
./main
```

Then type the number of nodes and the option, e.g. `40` and `2`. Input can be
piped: `printf '40\n2\n' | ./main`.

Controls in the window: arrow keys pan, `F1` switches to option 1, `F2` to
option 2. Close the window to exit. (`windowControl.h` also maps `Esc`, `+`
and `-`, but they are registered on GLUT's *special*-key callback, which
never delivers them.)

## Sample output

```
Numero de Nodos: Opcion 1: Busqueda en Profundidad
Opcion 2: Heuristica Mejor el Primero
Llego
32
31
...
4
0
```

## Layout

| File | Contents |
|---|---|
| `busqueda.cc` | entry point, input and render loop |
| `grafo.h`, `nodo.h` | undirected graph with obstacle edges; BFS and best-first search |
| `delaunay.h` | Delaunay triangulation used to build the map |
| `grafoAlgoritmos.h` | random point generation and graph construction |
| `grafoInterfaz.h` | OpenGL drawing of the graph and the search |
| `camara.h`, `windowControl.h` | 2D camera, keyboard and reshape handlers |
| `geometria.h`, `xorshift.h` | 2D point type and random generator |

`AgenteViajero` reuses this graph/rendering code for a travelling-salesman
genetic algorithm.
