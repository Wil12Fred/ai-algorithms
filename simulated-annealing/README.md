# simulated-annealing

[![simulated-annealing](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/simulated-annealing.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/simulated-annealing.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

Simulated annealing in C++, built as a subclass of the genetic-algorithm
engine from [`genetic-algorithm`](../genetic-algorithm) with a population of
one, applied to the same `sinc^2` objective.

## Features

- 18-bit chromosomes decoded into `(x1, x2)`; objective
  `f(x1, x2) = (sin(pi*r) / (pi*r))^2`, maximum `1` at the origin.
- `Simulated_Annealing<P>` derives from `Genetico<P>`: each step mutates the
  current solution and keeps the neighbour with a Boltzmann-style probability
  `exp((fitness / total) / T)`.
- Temperature starts at `1`, multiplied by `0.99` after an improvement and
  by `0.9999` otherwise; stops once the best is stable for 10 steps.

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

Each line is `step; x1; x2; f(x1, x2); T`. A real run (clock seed; a few
thousand steps is typical):

```
1; 1.60938; 2.875; 0.00596309; 1.00000000
2; 1.60938; 0.890625; 0.0070001; 0.99990000
3; 1.54688; 1.89062; 0.0164371; 0.98990100
4; 0.546875; 1.76562; 0.00623505; 0.98000199
...
4185; 0; -0.015625; 0.999197; 0.00004149
4186; 0; -0.015625; 0.999197; 0.00004148
```

## Tests

```bash
make test
```

- `tests/test_annealing.cc` (fixed seeds): the state stays a single solution
  for 200 steps and the temperature only cools; for five seeds the run ends
  with `f > 0.9` (the first ring of local maxima is at `f ~ 0.047`).
- `tests/run_check.sh` runs `./main` and checks the output: consecutive
  steps, `f` in `[0, 1]`, `T` never rising, final `f > 0.9`.

## Project layout

| File | Contents |
|---|---|
| `main.cc` | entry point: runs simulated annealing (GA variants commented out) |
| `simulated_annealing.h` | `Simulated_Annealing<P>`, a subclass of the GA |
| `genetico.h`, `individuo.h`, `represent.h`, `problema.h` | the GA engine (copy of `genetic-algorithm`'s, without its progress output) |
| `xorshift.h`, `matematica.h` | random generator and constants |
| `tests/` | unit tests and the output check |

## Known limitations

- Clock seed only; no option to fix it from the command line.
- The engine headers duplicate those of `genetic-algorithm`
  (`genetico.h` differs only in its logging).
- Identifiers and comments are in Spanish.

## Background

Coursework for a university Artificial Intelligence course, 2018.

## License

MIT — see [LICENSE](../LICENSE).
