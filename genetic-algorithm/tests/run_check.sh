#!/bin/sh
# Runs the program (seeded from the clock): every line is "generation; f"
# with f in [0, 1], generations increase, and the last f is above 0.99.
set -eu
cd "$(dirname "$0")/.."
out=$(mktemp)
timeout 60 ./main >"$out"
awk -F'; ' '
NF != 2 || $2 < 0 || $2 > 1 || $1 + 0 < prev { print "FAIL: " $0; bad=1 }
{ prev = $1 + 0; last = $2 + 0 }
END { if (NR == 0 || last <= 0.99) { print "FAIL: final f = " last; bad=1 } exit bad }' "$out"
echo "genetic-algorithm: $(wc -l <"$out") progress lines, final $(tail -n1 "$out")"
