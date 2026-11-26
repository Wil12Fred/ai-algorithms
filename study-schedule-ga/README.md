# AlgoritmoGeneticoParcial

Midterm exam project ("Parcial") for a university Artificial Intelligence
course (2018): a genetic algorithm that plans **when to study** around a
fixed weekly class timetable. Identifiers and comments are in Spanish.

## What it does

1. `crearHorario` builds a random week of 6 days x 24 hours. Each course gets
   two 3-hour lectures placed between 07:00 and 21:00; every other hour is free.
2. Each individual assigns one value to every free hour: `0` = rest, `k` =
   study course `k`.
3. The fitness simulates the week hour by hour with a simple model of energy
   (drains while studying or in class, recovers while resting), understanding
   and interest per course, and accumulates "knowledge" per course. The
   fitness is the **product** of the knowledge of all courses, so neglecting
   any course is punished.
4. The same `Genetico<P>` engine as `AlgoritmoGenetico` (generalised here to
   integer genes) evolves 30 individuals with elitism until the best fitness
   is stable for 20 generations. A simulated-annealing variant is left
   commented out in `main.cc`.

## Build and run

Requires a C++11 compiler and `make`.

```bash
make
./main
```

The seed comes from the clock, so the timetable and result differ every run.

## Sample output

```
108                                   <- free hours to plan
0 0 0 0 0 0 0 3 3 3 0 6 6 6 0 0 5 5 5 0 0 0 0 0   <- fixed timetable, one row per day
...
632                                   <- generations until stable
<the timetable again, with planned hours highlighted in cyan>
curso 1: 7.1734                       <- knowledge per course
curso 2: 5.29305
...
curso 6: 4.76854
31531.7                               <- fitness (product of the above)
```

## Known limitation

Courses are numbered from `0` inside `crearHorario`, but `0` also means
"free hour", so course 0 never gets lectures: `main` asks for 7 courses and
the timetable effectively has 6 (hence 108 free hours, which `main` also
hard-codes as the chromosome length). Left as written in the original.

## Layout

| File | Contents |
|---|---|
| `main.cc` | timetable generation, printing and the GA run |
| `problema.h` | `Parcial`: individual generation and the study-model fitness |
| `genetico.h`, `individuo.h`, `represent.h` | GA engine (integer genes) |
| `simulated_annealing.h` | alternative solver (unused by default) |
| `xorshift.h`, `matematica.h` | random generator and constants |
