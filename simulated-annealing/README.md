# SimulatedAnnealing

Simulated annealing in C++, built on top of the genetic-algorithm engine from
`AlgoritmoGenetico`. University coursework (Artificial Intelligence, 2018);
identifiers and comments are in Spanish.

## What it does

It maximises the same function as `AlgoritmoGenetico`,

```
f(x1, x2) = (sin(pi*r) / (pi*r))^2      with r = sqrt(x1^2 + x2^2)
```

over 18-bit chromosomes that encode `(x1, x2)`. `Simulated_Annealing<P>`
derives from `Genetico<P>` with a population of one: each step mutates the
current solution and keeps the neighbour with a Boltzmann-style probability
`exp((fitness / total) / T)`. The temperature `T` starts at `1` and is
multiplied by `0.99` after an improvement and by `0.9999` otherwise. The run
stops once the best fitness has been stable for 10 steps.

## Build and run

Requires a C++11 compiler and `make`.

```bash
make
./main
```

The seed comes from the clock, so the number of steps varies between runs
(a few thousand is typical).

## Sample output

Each line is `step; x1; x2; f(x1, x2); T`:

```
1; -0.34375; 1.26562; 0.0405508; 1.00000000
2; -2.3125; 1.26562; 0.0120699; 0.99000000
3; -2.3125; 1.26562; 0.0120699; 0.98990100
4; -2.3125; 3.26562; 1.39599e-07; 0.98980201
...
3926; 0.015625; 0; 0.999197; 0.00005093
3927; 0.015625; 0; 0.999197; 0.00005092
```

## Layout

| File | Contents |
|---|---|
| `main.cc` | entry point: runs simulated annealing (GA variants commented out) |
| `simulated_annealing.h` | `Simulated_Annealing<P>`, a subclass of the GA |
| `genetico.h`, `individuo.h`, `represent.h`, `problema.h` | the GA engine, shared with `AlgoritmoGenetico` |
| `xorshift.h`, `matematica.h` | random generator and constants |
