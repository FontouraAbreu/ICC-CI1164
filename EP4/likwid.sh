#!/bin/bash

# executable name
EXECUTABLE="matmult"
# test sizes
SIZES="64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000"
# likwid groups
EVENTS="FLOPS_DP ENERGY"
#CPU core
CORE=15

# function to parse the output based on the metric needed using switch case
function parse_output() {
    case $1 in
        FLOPS_DP)
            likwid_output=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==1 {dp = $(NF-1)} NR%3==2 {avx_dp = $(NF-1); printf "%s %s ", dp, avx_dp}')
            time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            ;;
        ENERGY)
            likwid_output=$(cat $g_$n.txt | grep "Energy\ \[J\]\ " | awk {'print $5'} | tr '\n' ' ')
            time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            ;;
        MEM)
            likwid_output=$(echo "$g_$n.txt" | grep "MEM\ \[MBytes/s\]\ STAT" | head -n1 | awk {'print $12'})
            time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            ;;
        # cache miss ratio
        CACHE)
            likwid_output=$(echo "$g_$n.txt" | grep "cache\ miss\ ratio\ \[\%\]\ STAT" | head -n1 | awk {'print $12'})
            time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            ;;
        *)
            echo "Invalid metric"
            ;;
    esac
}

# creating time.csv only once
echo "N,MultMatVet,OptimizedMultMatVet,MultMatMat,OptmizedMultMatMat" > time.csv

# for each group, run the executable for each size and parse the output
for g in $EVENTS; do
    if [ -f $g.csv ]; then
        rm $g.csv
    fi
    echo "N,MultMatVet,OptimizedMultMatVet,MultMatMat,OptmizedMultMatMat" > $g.csv

    for n in $SIZES; do
        likwid-perfctr -C $CORE -g $g -m -f ./$EXECUTABLE $n > $g_$n.txt
        parse_output $g $n
        echo "$n, $likwid_output" >> $g.csv
        # if is the first group, save the time spent
        if [ $g == "FLOPS_DP" ]; then
            echo "$n, $time_spent" >> time.csv
        fi
        rm $g_$n.txt
    done
done


