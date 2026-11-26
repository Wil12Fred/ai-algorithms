# ai-algorithms

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Artificial-intelligence and optimisation algorithms in C++ — genetic
algorithms, simulated annealing, graph search and an agent-based simulation —
each a small self-contained program with its own README, Makefile, tests and
CI workflow.

| Folder | CI | What it is | Graphics |
|---|---|---|---|
| [`genetic-algorithm`](genetic-algorithm) | [![genetic-algorithm](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/genetic-algorithm.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/genetic-algorithm.yml) | Generic header-only genetic algorithm; maximises sinc²(r) on 24-bit chromosomes | no |
| [`simulated-annealing`](simulated-annealing) | [![simulated-annealing](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/simulated-annealing.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/simulated-annealing.yml) | Simulated annealing built on the same engine, same objective | no |
| [`study-schedule-ga`](study-schedule-ga) | [![study-schedule-ga](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/study-schedule-ga.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/study-schedule-ga.yml) | Genetic algorithm with integer genes that plans study hours around a class timetable | no |
| [`graph-search-visualizer`](graph-search-visualizer) | [![graph-search-visualizer](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/graph-search-visualizer.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/graph-search-visualizer.yml) | BFS and greedy best-first search on a random Delaunay map with obstacles | OpenGL/GLUT |
| [`tsp-genetic-glut`](tsp-genetic-glut) | [![tsp-genetic-glut](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/tsp-genetic-glut.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/tsp-genetic-glut.yml) | Travelling-salesman solver with a genetic algorithm (order crossover, tour-length fitness) | OpenGL/GLUT |
| [`predator-prey-simulation`](predator-prey-simulation) | [![predator-prey-simulation](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/predator-prey-simulation.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/predator-prey-simulation.yml) | Foxes-and-rabbits agent-based simulation on a 20×20 grid | no |

## Requirements

A C++11 compiler and `make`; the two GLUT programs also need OpenGL/GLUT,
and their headless smoke tests Xvfb and xdotool.

- Debian/Ubuntu: `sudo apt install g++ make freeglut3-dev xvfb xdotool`
- Arch: `sudo pacman -S gcc make freeglut xorg-server-xvfb xdotool`

## Build and test

```bash
make            # build every program
make test       # unit tests + output checks of every program (no window opens)
make -C graph-search-visualizer smoke   # headless GUI run under xvfb-run
make -C genetic-algorithm && ./genetic-algorithm/main
```

## Known limitations

`genetic-algorithm`, `simulated-annealing` and `study-schedule-ga` started
as copies of one engine. Only `xorshift.h` and `matematica.h` are still
identical in all three (`genetico.h` and `individuo.h` have diverged), so
they were left per folder rather than moved to a shared directory. Each
folder's README lists its own limitations.

## Background

Coursework for a university Artificial Intelligence course, 2017–2018.
Identifiers and comments are in Spanish; documentation is in English.

## License

MIT — see [LICENSE](LICENSE).
