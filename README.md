# ai-algorithms

Artificial-intelligence and optimisation algorithms in C++, written for a
university AI course (2017–2018). Each folder is a self-contained program with
its own `README.md`, `Makefile` and CI workflow.

| Folder | What it is | Graphics |
|---|---|---|
| [`genetic-algorithm`](genetic-algorithm) | Generic header-only genetic algorithm; maximises sinc²(r) on 24-bit chromosomes | no |
| [`simulated-annealing`](simulated-annealing) | Simulated annealing built on the same engine, same objective | no |
| [`study-schedule-ga`](study-schedule-ga) | Genetic algorithm with integer genes that plans study hours around a class timetable | no |
| [`graph-search-visualizer`](graph-search-visualizer) | BFS and greedy best-first search on a random Delaunay map with obstacles | OpenGL/GLUT |
| [`tsp-genetic-glut`](tsp-genetic-glut) | Travelling-salesman solver with a genetic algorithm (unfinished: no fitness function yet) | OpenGL/GLUT |
| [`predator-prey-simulation`](predator-prey-simulation) | Foxes-and-rabbits cellular simulation on a 20×20 grid | no |

```bash
make            # build every program
make -C genetic-algorithm && ./genetic-algorithm/main
```

The GLUT programs need `freeglut3-dev` (Debian/Ubuntu) or `freeglut` (Arch).

`genetic-algorithm`, `simulated-annealing` and `study-schedule-ga` started as
copies of one engine, so they still share near-identical headers
(`xorshift.h`, `matematica.h`, `individuo.h`). Each folder keeps the history of
the repository it came from.
