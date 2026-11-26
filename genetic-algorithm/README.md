# AlgoritmoGenetico

A small, header-only genetic algorithm in C++ that maximises a two-variable
function. University coursework (Artificial Intelligence, 2018); identifiers
and comments are in Spanish.

## What it does

Each individual is a 24-bit chromosome that encodes two signed fixed-point
numbers `x1` and `x2` in roughly `(-4, 4)`. The fitness function is

```
f(x1, x2) = (sin(pi*r) / (pi*r))^2      with r = sqrt(x1^2 + x2^2)
```

whose global maximum is `1` at the origin. The algorithm uses roulette-wheel
selection, two-segment crossover, bit-flip mutation and (in the default
`main`) elitism, and stops once the best fitness has not changed for 10
generations.

The generic `Genetico<Problem>` template only needs a problem type that
provides `generar_nuevo_individuo` and `aptitud`, so other problems can be
plugged in (see `problema.h`).

## Build and run

Requires a C++11 compiler and `make`.

```bash
make
./main
```

The random seed is taken from the clock, so every run differs.

## Sample output

Each line is `generation; f(best individual)`:

```
3; 0.84094
5; 0.843436
7; 0.88253
8; 0.918025
9; 0.963339
...
17; 0.999097
18; 0.999987
27; 1
39; 1
```

## Layout

| File | Contents |
|---|---|
| `main.cc` | entry point: runs the GA with elitism (non-elitist variant commented out) |
| `genetico.h` | the generic genetic algorithm (`Genetico<P>`) |
| `individuo.h` | individual: crossover and mutation operators |
| `represent.h` | bit-string chromosome and its decoding to `(x1, x2)` |
| `problema.h` | base problem and the `Practica2` fitness function |
| `xorshift.h` | xorshift pseudo-random generator seeded from the clock |
| `matematica.h` | constants |

Related repositories: `SimulatedAnnealing` (same problem, solved with simulated
annealing) and `AlgoritmoGeneticoParcial` (same engine applied to a study
timetable).
