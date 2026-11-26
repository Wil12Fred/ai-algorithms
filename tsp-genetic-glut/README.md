# tsp-genetic-glut

[![tsp-genetic-glut](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/tsp-genetic-glut.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/tsp-genetic-glut.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

A travelling-salesman ("agente viajero") solver in C++: a genetic algorithm
over city permutations, drawn with OpenGL/GLUT.

![A 20-city tour](docs/screenshot.png)

## Features

- Random cities in an 850x850 area; each individual is a permutation
  (a closed tour).
- Order crossover, swap mutation, roulette-wheel selection and truncation of
  the worst individuals; 10 individuals for 200 generations.
- Fitness `Problema::aptitud` = `100 * distancia_total / tour length`,
  where `Problema::longitud` is the closed tour length (lower is better) and
  `distancia_total` the sum of all pairwise distances. The GA keeps the
  **highest** fitness, so shorter tours win.
- Draws the cities (green) and the best tour (blue). Arrows pan, `+`/`-`
  zoom, `Esc` quits.

## Requirements

A C++11 compiler, `make` and OpenGL/GLUT. For the headless smoke test also
Xvfb and (optionally) xdotool.

- Debian/Ubuntu: `sudo apt install g++ make freeglut3-dev xvfb xdotool`
- Arch: `sudo pacman -S gcc make freeglut xorg-server-xvfb xdotool`
- macOS: the system OpenGL/GLUT frameworks.

## Build

```bash
make
```

## Run

```bash
./main          # then type the number of cities, e.g. 20
printf '20\n' | ./main
```

Console output of a real run (the prompt, then the number of cities printed
on each redraw):

```
Numero de Nodos: 20
20
```

## Tests

```bash
make test       # unit tests, no window
make smoke      # headless run on a private Xvfb display
```

- `tests/test_aptitud.cc` (fixed seed): on a unit square the perimeter tour
  has length 4 and the "bow tie" `2 + 2*sqrt(2)`, and the shorter tour has
  the higher fitness; 500 crossovers and mutations of random tours all
  produce valid permutations; on 16 cities on a circle (inserted in scrambled
  order) the GA returns a valid tour no shorter than the optimum, no longer
  than the best initial tour and under 75% of the mean random tour
  (measured: mean 6877, best initial 6479, GA 4046, optimum 1873).
- `tests/test_teclado.cc`: `+`/`-`/`Esc` work through the ASCII keyboard
  handler, arrows through the special-key handler, and `main.cc` registers
  the keyboard handler.
- `tests/smoke.sh` (always under `xvfb-run`): the program keeps running
  until `timeout` (exit 124) with 20 cities, and `Esc` closes it (exit 0).

## Project layout

| File | Contents |
|---|---|
| `main.cc` | entry point, input and render loop |
| `genetico.h` | individual (order crossover, swap mutation), `Problema` (tour length, fitness) and the GA |
| `represent.h` | permutation chromosome |
| `grafoAlgoritmos.h` | random cities and the GA call that builds the tour |
| `grafoInterfaz.h` | OpenGL drawing of the tour |
| `grafo.h`, `nodo.h`, `geometria.h` | graph and 2D point types |
| `camara.h`, `windowControl.h`, `xorshift.h` | camera, input handlers, random generator |
| `tests/` | unit tests and the headless smoke run |

## Known limitations

- Fixed: the fitness function was a TODO that returned `0` for every tour,
  so the drawn tour was a random permutation. It now scores tour length.
- Fixed: the order crossover dropped cities whenever it copied the parent's
  segment, producing tours with repeated and missing cities (invisible while
  the fitness was 0).
- Fixed: `Esc`, `+` and `-` were on the special-key callback and never fired.
- With 10 individuals and 200 generations the tour improves a lot but is
  rarely optimal; the GA reruns on every redraw, so panning recomputes it.
- Legacy fixed-function OpenGL/GLUT. Identifiers and prompts are in Spanish.

## Background

Coursework for a university Artificial Intelligence course, 2018; reuses the
graph and drawing code of `graph-search-visualizer` and an earlier,
non-generic version of the `genetic-algorithm` engine.

## License

MIT — see [LICENSE](../LICENSE).
