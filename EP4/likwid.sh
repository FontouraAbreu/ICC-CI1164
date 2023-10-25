#!/bin/bash

# executable name
EXECUTABLE="matmult"
# test sizes
SIZES="64, 100, 128,  200, 256, 512, 600, 900, 1024, 2000, 2048, 3000, 4000"
# likwid groups
GROUPS="FLOPS_DP MEM CACHE ENERGY"

for group in $GROUPS; do
    for n in $SIZES; do
        likwid-perfctr -g $group -f ./$EXECUTABLE $n > $group.txt
        parse_output $group
    done
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

