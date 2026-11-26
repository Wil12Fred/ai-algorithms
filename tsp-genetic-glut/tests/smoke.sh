#!/bin/sh
# Headless smoke run (needs xvfb-run; xdotool optional).
#  1. The program starts, reads the number of cities and keeps running until killed
#     by timeout (exit 124 = still running = pass).
#  2. With xdotool: pressing Esc in the window ends the program with exit 0.
set -u
cd "$(dirname "$0")/.."
command -v xvfb-run >/dev/null || { echo "FAIL: xvfb-run is required (never runs on the real display)"; exit 1; }
out=$(mktemp)
printf '20\n' | xvfb-run -a timeout 15 ./main >"$out" 2>&1
rc=$?
cat "$out"
[ "$rc" -eq 124 ] || { echo "FAIL: expected exit 124 (still running), got $rc"; exit 1; }
grep -q "^Numero de Nodos: 20$" "$out" || { echo "FAIL: expected 20 cities"; exit 1; }
echo "smoke: runs headless with 20 cities"

if command -v xdotool >/dev/null 2>&1; then
	xvfb-run -a sh -c '
		printf "20\n" | ./main >/dev/null 2>&1 & pid=$!
		for i in $(seq 150); do
			w=$(xdotool search --name "^Busqueda$" 2>/dev/null | head -n1)
			[ -n "$w" ] && break; sleep 0.1
		done
		[ -n "$w" ] || { echo "FAIL: window not found"; kill $pid; exit 1; }
		xdotool mousemove --window "$w" 10 10
		sleep 0.3
		xdotool key Escape
		for i in $(seq 30); do kill -0 $pid 2>/dev/null || break; sleep 0.1; done
		if kill -0 $pid 2>/dev/null; then echo "FAIL: Esc did not close the program"; kill $pid; exit 1; fi
		wait $pid; rc=$?
		[ $rc -eq 0 ] || { echo "FAIL: exit $rc after Esc"; exit 1; }
		echo "smoke: Esc closes the window (exit 0)"
	' || exit 1
fi
