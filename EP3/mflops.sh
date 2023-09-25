#!/bin/bash
#extracts the argument from the command line
#and stores it in the variable n
n=$1

# Define the command to run your executable with likwid-perfctr
command_to_run="likwid-perfctr -g FLOPS_DP -f ./interpola $n"

# Execute the command and capture the output
full_output="$($command_to_run)"


# Separate the likwid output from the executable output
likwid_output=$(echo "$full_output" | grep "DP\ \[MFLOP/s\]\ STAT" | head -n1 | awk {'print $12'})
# extract output beetwen the second "----" and third "----"
executable_output=$(echo "$full_output" | awk '/^-+$/ {count++; next} count == 2, /Group 1: FLOPS_DP/' | head -n -1)


# Print the output
echo "$executable_output"

# Print the likwid output
echo "$likwid_output MFLOP/s on average"
