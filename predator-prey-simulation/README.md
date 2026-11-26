# ZorrosYConejos

"Foxes and rabbits": a grid-based predator-prey simulation in C++ (agent-based
model). University coursework, September 2018. Identifiers and output labels
are in Spanish.

## What it does

A 20x20 grid is seeded at random: each cell starts with grass, a rabbit on
grass, or a fox. Then, for 30 iterations, every cell is visited in random
order and its animals act:

- each animal picks at random between moving up/down/left/right, staying,
  or eating;
- rabbits eat grass in their cell, foxes eat a random rabbit in their cell;
- an animal dies if it goes too many turns without eating (`v`), and spawns
  `d` offspring every `t` turns;
- grass regrows every `grass_t` turns in cells next to other grass.

Parameters (`n`, `grass_t`, `conejo_t/d/v`, `zorro_t/d/v`, `iteraciones`) are
hard-coded at the top of `main()`. Species-specific movement preferences
(`conejo::act_pr`, `zorro::act_pr`) exist but are commented out in favour of
the generic random walk.

## Build and run

Requires a C++11 compiler and `make`.

```bash
make
./main
```

Seeded from the clock; every run differs.

## Sample output

For each iteration the grid is printed, each cell labelled by what dominates
it (`gr` = grass, `co` = conejos/rabbits, `zo` = zorros/foxes, with the
count), followed by the totals `grass rabbits foxes`:

```
co(7) gr(1) zo(3) co(7) gr(2) gr(1) gr(1) zo(0) gr(1) co(7) zo(0) co(14) ...
...
213 121 144
```

Totals over the 30 iterations of one run, showing the fox population collapse:

```
213 121 144 | 195 114 144 | 181 105 144 | ... | 447 263 6 | 439 532 5 | ... | 528 455 6
```

## Layout

| File | Contents |
|---|---|
| `main.cc` | `conejo`, `zorro`, grid cell logic and the simulation loop |
| `animal.h` | shared animal behaviour: movement, reproduction, starvation |
| `grass.h` | grass regrowth |
| `utility.h` | bounds check and weighted random choice |
