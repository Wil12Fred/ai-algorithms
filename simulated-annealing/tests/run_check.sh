#!/bin/sh
# Runs the program (seeded from the clock): every line is
# "step; x1; x2; f; T", steps are consecutive, T never rises, and the final
# f is above 0.9.
set -eu
cd "$(dirname "$0")/.."
out=$(mktemp)
timeout 120 ./main >"$out"
awk -F'; ' '
NF != 5 || $1 != NR || $4 < 0 || $4 > 1 || (NR > 1 && $5 > prevT) { print "FAIL: " $0; bad=1 }
{ prevT = $5 + 0; last = $4 + 0 }
END { if (NR == 0 || last <= 0.9) { print "FAIL: final f = " last; bad=1 } exit bad }' "$out"
echo "simulated-annealing: $(wc -l <"$out") steps, final $(tail -n1 "$out")"
