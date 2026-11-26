#!/bin/sh
# Runs the simulation (seeded from the clock) and checks the output shape:
# 30 iterations, each a 20x20 grid of gr(n)/co(n)/zo(n) cells followed by a
# "grass rabbits foxes" line of non-negative integers.
set -eu
cd "$(dirname "$0")/.."
out=$(mktemp)
timeout 60 ./main >"$out"
awk '
/^([a-z][a-z]\([0-9]+\) ){20}$/ { rows++; next }
/^[0-9]+ [0-9]+ [0-9]+$/        { if (rows != 20) { print "FAIL: block with " rows " rows"; bad=1 } rows=0; totals++; next }
/^$/ { next }
{ print "FAIL: unexpected line: " $0; bad=1 }
END { if (totals != 30) { print "FAIL: " totals " iterations"; bad=1 } exit bad }' "$out"
grep -Eo '[a-z]{2}\(' "$out" | sort -u | grep -vqE '^(gr|co|zo)\($' && { echo "FAIL: unknown cell label"; exit 1; }
echo "predator-prey-simulation: output has 30 iterations of a 20x20 grid"
