#!/bin/bash
start=$(date +%s.%N) # From https://stackoverflow.com/a/32272632

"$@" # Run the provided commands, ignoring output

dur=$(echo "$(date +%s.%N) - $start" | bc)

printf "Execution time: %.6f seconds" $dur