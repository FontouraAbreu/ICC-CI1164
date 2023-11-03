#!/bin/bash

# executable name
EXECUTABLE="matmult"
# test sizes
SIZES="64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000"
# likwid groups
EVENTS="FLOPS_DP ENERGY L2CACHE L3"
#CPU core
CORE=15
TIME_SAVED=0

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# function to parse the output based on the metric needed using switch case
function parse_output() {
    case $1 in
        FLOPS_DP)
            likwid_output=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==1 {dp = $(NF-1); printf "%s ", dp}')
            likwid_output_flops_avx=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==2 {avx_dp = $(NF-1); printf "%s ", avx_dp}')
            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        ENERGY)
            likwid_output=$(cat $g_$n.txt | grep "Energy\ \[J\]\ " | awk {'print $5'} | tr '\n' ' ')
            
            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        L2CACHE)
            likwid_output=$(cat "L2Cache.txt" | grep "\ miss \ratio\ " | awk '{print $(NF-1)}' | tr '\n' ' ')
            
            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        # cache miss ratio
        L3)
            likwid_output=$(cat "$g_$n.txt" | grep "L3\ bandwidth\ " | awk '{print $(NF-1)}' | tr '\n' ' ')

            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        *)
            echo "Invalid metric"
            ;;
    esac
}

# creating time.csv only once
echo "N MultMatVet OptimizedMultMatVet MultMatMat OptmizedMultMatMat" > time.csv

# for each group, run the executable for each size and parse the output
for g in $EVENTS; do
    if [ -f $g.csv ]; then
        rm $g.csv
    fi
    echo "N MultMatVet OptimizedMultMatVet MultMatMat OptmizedMultMatMat" > $g.csv
    if [ $g == "FLOPS_DP" ]; then
            echo "N MultMatVet OptimizedMultMatVet MultMatMat OptmizedMultMatMat" > FLOPS_AVX.csv
        fi

    for n in $SIZES; do
        likwid-perfctr -C $CORE -g $g -m -f ./$EXECUTABLE $n > $g_$n.txt
        parse_output $g $n
        echo "$n $likwid_output" >> $g.csv

        # handling FLOPS_AVX case
        if [ $g == "FLOPS_DP" ]; then
            echo "$n $likwid_output_flops_avx" >> FLOPS_AVX.csv
        fi

        # if is the first group, save the time spent
        first_group=$(echo $EVENTS | awk '{print $1}')
        if [ $g == $first_group ]; then
            echo "$n $time_spent" >> time.csv
        fi
        rm $g_$n.txt
    done
    TIME_SAVED=1
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 