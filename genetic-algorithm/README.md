# genetic-algorithm

[![genetic-algorithm](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/genetic-algorithm.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/genetic-algorithm.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

A small, header-only genetic algorithm in C++ that maximises a two-variable
function, written so that any problem type with `generar_nuevo_individuo`
and `aptitud` can be plugged into the same `Genetico<Problem>` engine.

## Features

- 24-bit chromosomes decoded into two signed fixed-point numbers `x1`, `x2`
  in roughly `(-4, 4)` (sign bit, 2 integer bits, 9 fraction bits each).
- Objective `f(x1, x2) = (sin(pi*r) / (pi*r))^2`, `r = sqrt(x1^2 + x2^2)`,
  global maximum `1` at the origin.
- Roulette-wheel selection, two-segment crossover, bit-flip mutation and
  optional elitism; stops when the best fitness is stable for 10 generations.
- Xorshift pseudo-random generator seeded from the clock.

## Requirements

A C++11 compiler and `make`.

- Debian/Ubuntu: `sudo apt install g++ make`
- Arch: `sudo pacman -S gcc make`

## Build

```bash
make
```

## Run

```bash
./main
```

Each line is `generation; f(best individual)`, printed when the best changes
and once at the end. A real run (the seed comes from the clock, so every run
differs):

```
6; 0.907292
8; 0.947367
11; 0.949918
12; 0.975741
13; 0.998131
14; 0.998996
16; 0.999373
18; 0.999548
19; 0.999598
20; 0.999799
23; 1
35; 1
```

## Tests

```bash
make test
```

- `tests/test_genetico.cc` (fixed seeds): decoding of a hand-built chromosome
  to `(1.5, -2.25)`; the objective is `1` at the origin, `0` at `r = 1`
  and decreasing near the origin; for five seeds the elitist GA ends with
  `f > 0.99`, never worse than its initial population, with the population
  size preserved.
- `tests/run_check.sh` runs `./main` and checks the output format
  (increasing generations, `f` in `[0, 1]`, final `f > 0.99`).

## Project layout

| File | Contents |
|---|---|
| `main.cc` | entry point: runs the GA with elitism (non-elitist variant commented out) |
| `genetico.h` | the generic genetic algorithm (`Genetico<P>`) |
| `individuo.h` | individual: crossover and mutation operators |
| `represent.h` | bit-string chromosome and its decoding to `(x1, x2)` |
| `problema.h` | base problem and the `Practica2` fitness function |
| `xorshift.h`, `matematica.h` | random generator and constants |
| `tests/` | unit tests and the output check |

## Known limitations

- The seed always comes from the clock; `main` has no option to fix it (the
  tests set the generator state directly).
- `simulated-annealing` and `study-schedule-ga` started as copies of this
  engine and still carry near-identical headers; they have diverged
  (`genetico.h`, `individuo.h` differ), so they were not merged.
- Identifiers and comments are in Spanish.

## Background

Coursework for a university Artificial Intelligence course, 2018.

## License

MIT — see [LICENSE](../LICENSE).
