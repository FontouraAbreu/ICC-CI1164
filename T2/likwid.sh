#!/bin/bash

# executable name
EXECUTABLE="ajustePol"
# test sizes
SIZES="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 10⁵ 10⁶ 10⁷ 10⁸"
# likwid groups
EVENTS="FLOPS_DP ENERGY"
#CPU core
CORE=15
TIME_SAVED=0
CSV_FORMAT="N LEAST_SQUARE_METHOD SYSTEM_SOLVER LEAST_SQUARE_METHOD_OPTMIZED SYSTEM_SOLVER_OPTMIZED"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# function to parse the output based on the metric needed using switch case
function parse_output() {
    case $1 in
        FLOPS_DP)
            likwid_output=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==1 {dp = $(NF-1); printf "%s ", dp}')
            # if likwid output is '0 0 0 0', change it to '1 1 1 1'
            echo $likwid_output | grep -q "0 0 0 0" && likwid_output_flops_avx="1 1 1 1"

            likwid_output_flops_avx=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==2 {avx_dp = $(NF-1); printf "%s ", avx_dp}')
            echo $likwid_output_flops_avx | grep -q "0 0 0 0" && likwid_output_flops_avx="1 1 1 1"

            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        ENERGY)
            likwid_output=$(cat $g_$n.txt | grep "Energy\ \[J\]\ " | awk {'print $5'} | tr '\n' ' ')
            
            # if likwid output is '0 0 0 0', change it to '1 1 1 1'
            echo $likwid_output | grep -q "0 0 0 0" && likwid_output_flops_avx="1 1 1 1"


            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        L2CACHE)
            likwid_output=$(cat "L2Cache.txt" | grep "\ miss \ratio\ " | awk '{print $(NF-1)}' | tr '\n' ' ')
            
            # if likwid output is '0 0 0 0', change it to '1 1 1 1'
            echo $likwid_output | grep -q "0 0 0 0" && likwid_output_flops_avx="1 1 1 1"


            # if time saved == 1, do not save the time spent
            if [ $TIME_SAVED == 0 ]; then
                time_spent=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}')
            fi
            ;;
        # cache miss ratio
        L3)
            likwid_output=$(cat "$g_$n.txt" | grep "L3\ bandwidth\ " | awk '{print $(NF-1)}' | tr '\n' ' ')

            # if likwid output is '0 0 0 0', change it to '1 1 1 1'
            echo $likwid_output | grep -q "0 0 0 0" && likwid_output_flops_avx="1 1 1 1"


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
echo $CSV_FORMAT > time.csv

# for each group, run the executable for each size and parse the output
for g in $EVENTS; do
    if [ -f $g.csv ]; then
        rm $g.csv
    fi

    # FLOPS_AVX is a special case, so we need to create a new csv file
    echo $CSV_FORMAT > $g.csv
    if [ $g == "FLOPS_DP" ]; then
            echo $CSV_FORMAT > FLOPS_AVX.csv
        fi

    # for each size, run the executable and parse the output
    for n in $SIZES; do
        ./gera_entrada $n | likwid-perfctr -C $CORE -g $g -m -f ./$EXECUTABLE > $g_$n.txt
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
