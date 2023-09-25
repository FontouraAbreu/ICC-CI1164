#!/bin/bash

# Define the command to run your executable with likwid-perfctr
command_to_run="likwid-perfctr -g FLOPS_DP -f ./interpola"

# Execute the command and capture the output
full_output="$($command_to_run 2>&1)"

# Separate the likwid output from the executable output
likwid_output=$(echo "$full_output" | grep "DP\ \[MFLOP/s\]\ STAT" | head -n1 | awk {'print $12'})
executable_output=$(echo "$full_output" | grep -v -E '^LIKWID:')
