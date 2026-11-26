#!/bin/sh
# Runs the program (seeded from the clock): it reports 102 free hours
# (144 - 7 courses x 2 lectures x 3 hours), prints the knowledge of all 7
# courses, and ends with a positive fitness.
set -eu
cd "$(dirname "$0")/.."
out=$(mktemp)
timeout 60 ./main >"$out"
[ "$(head -n1 "$out")" = "102" ] || { echo "FAIL: first line $(head -n1 "$out"), expected 102"; exit 1; }
for c in 1 2 3 4 5 6 7; do
	grep -q "^curso $c: " "$out" || { echo "FAIL: no knowledge line for course $c"; exit 1; }
done
grep -q "^curso 8: " "$out" && { echo "FAIL: unexpected course 8"; exit 1; }
tail -n1 "$out" | grep -Eq '^[0-9.e+]+$' || { echo "FAIL: last line is not the fitness"; exit 1; }
echo "study-schedule-ga: 7 courses planned, fitness $(tail -n1 "$out")"
