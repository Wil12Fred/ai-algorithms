# predator-prey-simulation

[![predator-prey-simulation](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/predator-prey-simulation.yml/badge.svg)](https://github.com/Wil12Fred/ai-algorithms/actions/workflows/predator-prey-simulation.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

"Foxes and rabbits": a grid-based, agent-based predator-prey simulation in
C++ where grass, rabbits (`conejos`) and foxes (`zorros`) compete on a
20x20 grid.

## Features

- Random initial grid: each cell starts with grass, a rabbit on grass, or a
  fox.
- 30 iterations; every cell is visited in random order and its animals act:
  move up/down/left/right, stay, or eat.
- Rabbits eat grass in their cell, foxes eat a random rabbit in their cell.
- An animal dies after `v` turns without eating and spawns `d` offspring
  every `t` turns; grass regrows every `grass_t` turns next to other grass.
- Parameters (`n`, `grass_t`, `conejo_t/d/v`, `zorro_t/d/v`,
  `iteraciones`) are at the top of `main()`.

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

For each iteration the grid is printed, each cell labelled by what dominates
it (`gr` grass, `co` rabbits, `zo` foxes, with the count), then the totals
`grass rabbits foxes`. A real run (clock seed), first rows and then the 30
totals lines:

```
gr(1) gr(1) co(1) gr(1) zo(1) gr(1) zo(1) gr(1) gr(1) gr(1) zo(0) zo(1) co(1) ...
gr(1) zo(1) gr(1) zo(1) gr(1) zo(1) gr(1) gr(1) gr(1) co(1) co(1) zo(1) zo(1) ...
...
216 152 127 | 196 141 127 | 180 136 127 | 168 130 127 | 164 553 127 | 150 310 105 | ...
... | 338 310 9 | 513 298 9 | 486 285 7 | 476 602 3
```

## Tests

```bash
make test
```

- `tests/test_animal.cc`: grid bounds check; a new animal's reproduction
  counter starts at 0 even on dirty memory; an animal spawns exactly `d`
  offspring every `t` turns; one that never eats dies on turn `v+1` while a
  fed one survives; 5000 random moves from a corner never leave the grid;
  grass regrows only next to grass and never goes negative.
- `tests/run_check.sh` runs `./main` and checks the output shape: 30
  iterations of 20 rows x 20 `gr/co/zo(n)` cells plus a totals line.

## Project layout

| File | Contents |
|---|---|
| `main.cc` | `conejo`, `zorro`, grid cell logic and the simulation loop |
| `animal.h` | shared animal behaviour: movement, reproduction, starvation |
| `grass.h` | grass regrowth |
| `utility.h` | bounds check and weighted random choice |
| `tests/` | unit tests and the output check |

## Known limitations

- Fixed: `animal::timeToReproduce` was never initialised, so the first
  litter came after an arbitrary number of turns.
- Species-specific movement preferences (`conejo::act_pr`, `zorro::act_pr`)
  exist but are commented out in favour of the generic random walk.
- Animals are allocated with `new` and never freed.
- Seeded from the clock (`srand(time(NULL))`); output labels are in Spanish.

## Background

Coursework for a university Artificial Intelligence course, 2018.

## License

MIT — see [LICENSE](../LICENSE).
