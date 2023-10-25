#!/bin/bash

# groups
GROUPS="FLOPS_DP MEM CACHE ENERGY"

for group in $GROUPS; do
    likwid-perfctr -g $group -f ./interpola $n > $group.txt
done

# function to parse the output based on the metric needed using switch case
function parse_output() {
    case $1 in
        FLOPS_DP)
            likwid_output=$(echo "$group.txt" | grep "DP\ \[MFLOP/s\]\ STAT" | head -n1 | awk {'print $12'})
            echo "$likwid_output MFLOP/s on average"
            ;;
        MEM)
            likwid_output=$(echo "$group.txt" | grep "MEM\ \[MBytes/s\]\ STAT" | head -n1 | awk {'print $12'})
            echo "$likwid_output MB/s on average"
            ;;
        # cache miss ratio
        CACHE)
            likwid_output=$(echo "$group.txt" | grep "cache\ miss\ ratio\ \[\%\]\ STAT" | head -n1 | awk {'print $12'})
            echo "$likwid_output MB/s on average"
            ;;
        ENERGY)
            likwid_output=$(cat $group.txt | grep "Energy\ \[J\]\ " | awk {'print $5'})
            echo "$likwid_output J on average"
            ;;
        *)
            echo "Invalid metric"
            ;;
    esac
}

