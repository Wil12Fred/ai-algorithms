# study-schedule-ga

[![study-schedule-ga](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/study-schedule-ga.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/study-schedule-ga.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

A genetic algorithm with integer genes that plans **when to study** around a
fixed weekly class timetable, scoring each plan with a small simulation of
energy, understanding and interest.

## Features

- `crearHorario` (`horario.h`) builds a random week of 6 days x 24 hours:
  each of 7 courses (numbered `1..7`) gets two 3-hour lectures between 07:00
  and 21:00; every other hour is free (`0`). It returns the number of free
  hours, which is the chromosome length.
- Each individual assigns a value to every free hour: `0` = rest, `k` =
  study course `k`.
- The fitness simulates the week hour by hour (energy drains while studying
  or in class and recovers while resting; understanding and interest evolve
  per course) and is the **product** of the knowledge of all courses, so
  neglecting any course is punished.
- Same `Genetico<P>` engine as `genetic-algorithm`, generalised to integer
  genes; 30 individuals with elitism until the best is stable for 20
  generations. A simulated-annealing variant is commented out in `main.cc`.

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

A real run (clock seed). First the number of free hours and the fixed
timetable (one row per day), then the number of generations, the timetable
again with planned hours highlighted (cyan in a terminal), the knowledge per
course and the fitness:

```
102
0 0 0 0 0 0 0 5 3 3 3 5 5 0 1 1 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 3 3 3 4 4 4 0 0 0 0 0 0 7 7 7 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 6 6 6 0 0 0 0 0 0 0 0 0 2 2 2 0 0
0 0 0 0 0 0 0 7 7 7 6 6 6 1 1 1 5 5 5 0 0 0 0 0
0 0 0 0 0 0 0 4 4 4 0 0 0 2 2 2 0 0 0 0 0 0 0 0
673
...
curso 1: 3.9034
curso 2: 3.8632
curso 3: 3.72045
curso 4: 4.14965
curso 5: 3.66815
curso 6: 4.0215
curso 7: 3.5141
12068.3
```

## Tests

```bash
make test
```

- `tests/test_horario.cc` (fixed seeds): for 20 seeds every course `1..7`
  gets exactly 6 class hours, all between 07:00 and 21:59, and 102 hours are
  free; the problem sees 7 courses, genes stay in `0..7` and the fitness is
  positive; the elitist GA never ends worse than its initial population.
- `tests/run_check.sh` runs `./main` and checks that it reports 102 free
  hours, a knowledge line for each of the 7 courses and a final fitness.

## Project layout

| File | Contents |
|---|---|
| `main.cc` | the GA run |
| `horario.h` | timetable generation and printing |
| `problema.h` | `Parcial`: individual generation and the study-model fitness |
| `genetico.h`, `individuo.h`, `represent.h` | GA engine (integer genes) |
| `simulated_annealing.h` | alternative solver (unused by default) |
| `xorshift.h`, `matematica.h` | random generator and constants |
| `tests/` | unit tests and the output check |

## Known limitations

- Fixed: course numbers used to start at `0`, which also means "free hour",
  so only 6 of the 7 courses ever got lectures (108 free hours, hard-coded as
  the chromosome length). Courses now start at `1` and the chromosome length
  is the measured number of free hours.
- A 3-hour lecture is not guaranteed to be contiguous: when a slot is taken
  the placement skips forward to the next free hour, so a block can be split.
- Clock seed only. Identifiers and comments are in Spanish.

## Background

Midterm project for a university Artificial Intelligence course, 2018.

## License

MIT — see [LICENSE](../LICENSE).
