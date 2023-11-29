#!/bin/bash

# executable name
EXECUTABLE="ajustePol"
# test sizes
SIZES="64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 10⁵ 10⁶ 10⁷ 10⁸"
# likwid groups
EVENTS="FLOPS_DP ENERGY L2CACHE L3"
#CPU core
CORE=3
LS_CSV_FORMAT="N LEAST_SQUARE_METHOD LEAST_SQUARE_METHOD_OPTMIZED"
SS_CSV_FORMAT="N SYSTEM_SOLVER SYSTEM_SOLVER_OPTMIZED"
R_CSV_FORMAT="N RESIDUAL RESIDUAL_OPTMIZED"
TIME_SAVED=0


echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
function save_time() {
    time_spent_LS=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}' | cut -d ' ' -f 1,4)
    time_spent_SS=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}' | cut -d ' ' -f 2,5)
    time_spent_R=$(cat $g_$n.txt | awk '/^-+$/ {count++; if (count == 2) flag=1; else flag=0; next} flag && !/^-+$/ {printf "%s ", $0} flag && /^-+$/ {exit}' | cut -d ' ' -f 3,6)
}

# function to parse the output based on the metric needed using switch case
function parse_output() {
    case $1 in
        FLOPS_DP)
            # CONFERIR SE ESTA PEGANDO OS VALORES GERADOS PELO EVENTO "RESIDUAL" TBM
            # SE ESTIVER, EXCLUIR OS VALORES A NÃO SER QUE SEJA O GRUPO TEMPO, FLOPS_DP OU FLOPS_AVX
            likwid_output_LS=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==1 {dp = $(NF-1); printf "%s ", dp}' | cut -d ' ' -f 1,4)
            likwid_output_SS=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==1 {dp = $(NF-1); printf "%s ", dp}' | cut -d ' ' -f 2,5)
            likwid_output_R=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==1 {dp = $(NF-1); printf "%s ", dp}' | cut -d ' ' -f 3,6)

            likwid_output_flops_avx_LS=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==2 {avx_dp = $(NF-1); printf "%s ", avx_dp}' | cut -d ' ' -f 1,4)
            likwid_output_flops_avx_SS=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==2 {avx_dp = $(NF-1); printf "%s ", avx_dp}' | cut -d ' ' -f 2,5)
            likwid_output_flops_avx_R=$(cat $g_$n.txt | grep "DP\ \[MFLOP/s\]" | awk 'NR%3==2 {avx_dp = $(NF-1); printf "%s ", avx_dp}' | cut -d ' ' -f 3,6)
            save_time
            ;;
        ENERGY)
            # CONFERIR SE ESTA PEGANDO OS VALORES GERADOS PELO EVENTO "RESIDUAL" TBM
            # SE ESTIVER, EXCLUIR OS VALORES A NÃO SER QUE SEJA O GRUPO TEMPO OU E FLOPS FLOPS_AVX
            likwid_output_LS=$(cat $g_$n.txt | grep "Energy\ J\ " | awk {'print $5'} | tr '\n' ' ' | cut -d ' ' -f 1,4)
            likwid_output_SS=$(cat $g_$n.txt | grep "Energy\ J\ " | awk {'print $5'} | tr '\n' ' ' | cut -d ' ' -f 2,5)
            likwid_output_R=$(cat $g_$n.txt | grep "Energy\ J\ " | awk {'print $5'} | tr '\n' ' ' | cut -d ' ' -f 3,6)


            save_time
            ;;
        L2CACHE)
            # CONFERIR SE ESTA PEGANDO OS VALORES GERADOS PELO EVENTO "RESIDUAL" TBM
            # SE ESTIVER, EXCLUIR OS VALORES A NÃO SER QUE SEJA O GRUPO TEMPO OU E FLOPS FLOPS_AVX
            likwid_output_LS=$(cat "$g_$n.txt" | grep "\ miss \ratio\ " | awk '{print $(NF-1)}' | tr '\n' ' ' | cut -d ' ' -f 1,4)
            likwid_output_SS=$(cat "$g_$n.txt" | grep "\ miss \ratio\ " | awk '{print $(NF-1)}' | tr '\n' ' ' | cut -d ' ' -f 2,5)
            likwid_output_R=$(cat "$g_$n.txt" | grep "\ miss \ratio\ " | awk '{print $(NF-1)}' | tr '\n' ' ' | cut -d ' ' -f 3,6)

            save_time
            ;;
        # cache miss ratio
        L3)
            # CONFERIR SE ESTA PEGANDO OS VALORES GERADOS PELO EVENTO "RESIDUAL" TBM
            # SE ESTIVER, EXCLUIR OS VALORES A NÃO SER QUE SEJA O GRUPO TEMPO OU E FLOPS FLOPS_AVX
            likwid_output_LS=$(cat "$g_$n.txt" | grep "L3\ bandwidth\ " | awk '{print $(NF-1)}' | tr '\n' ' ' | cut -d ' ' -f 1,4)
            likwid_output_SS=$(cat "$g_$n.txt" | grep "L3\ bandwidth\ " | awk '{print $(NF-1)}' | tr '\n' ' ' | cut -d ' ' -f 2,5)
            likwid_output_R=$(cat "$g_$n.txt" | grep "L3\ bandwidth\ " | awk '{print $(NF-1)}' | tr '\n' ' ' | cut -d ' ' -f 3,6)

            save_time
            ;;
        *)
            echo "Invalid metric"
            ;;
    esac
}

# $1 = group
function create_csv() {
    case $1 in 
        FLOPS_DP)
            echo "$n $likwid_output_LS" >> ${g}_LS.csv
            echo "$n $likwid_output_SS" >> ${g}_SS.csv
            echo "$n $likwid_output_R" >> ${g}_R.csv

            echo "$n $likwid_output_flops_avx_LS" >> AVX_LS.csv
            echo "$n $likwid_output_flops_avx_SS" >> AVX_SS.csv
            echo "$n $likwid_output_flops_avx_R" >> AVX_R.csv
            ;;
        ENERGY)
            echo "$n $likwid_output_LS" >> ${g}_LS.csv
            echo "$n $likwid_output_SS" >> ${g}_SS.csv
            echo "$n $likwid_output_R" >> ${g}_R.csv
            ;;
        L2CACHE)
            echo "$n $likwid_output_LS" >> ${g}_LS.csv
            echo "$n $likwid_output_SS" >> ${g}_SS.csv
            echo "$n $likwid_output_R" >> ${g}_R.csv
            ;;
        L3)
            echo "$n $likwid_output_LS" >> ${g}_LS.csv
            echo "$n $likwid_output_SS" >> ${g}_SS.csv
            echo "$n $likwid_output_R" >> ${g}_R.csv
            ;;
        *)
            echo "Invalid group"
            ;;
    esac
}

# creating time.csv only once
echo $LS_CSV_FORMAT > TIME_LS.csv
echo $SS_CSV_FORMAT > TIME_R.csv

# for each group, run the executable for each size and parse the output
for g in $EVENTS; do
    if [ -f $g.csv ]; then
        rm $g.csv
    fi


    echo $LS_CSV_FORMAT > ${g}_LS.csv
    echo $R_CSV_FORMAT > ${g}_R.csv

    # FLOPS_AVX is a special case, so we need to create a new csv file
    if [ $g == "FLOPS_DP" ]; then
            echo $LS_CSV_FORMAT > AVX_LS.csv
            echo $R_CSV_FORMAT > AVX_R.csv
            echo $SS_CSV_FORMAT > ${g}_SS.csv
            echo $SS_CSV_FORMAT > TIME_SS.csv
            echo $SS_CSV_FORMAT > AVX_SS.csv
    fi

    # for each size, run the executable and parse the output
    for n in $SIZES; do
        ./gera_entrada $n | likwid-perfctr -C $CORE -g $g -m -f ./$EXECUTABLE > $g_$n.txt
        parse_output $g $n
        create_csv $g

        # creating time.csv only once
        if [ $TIME_SAVED -eq 0 ]; then
            echo "$n $time_spent_LS" >> TIME_LS.csv
            echo "$n $time_spent_SS" >> TIME_SS.csv
            echo "$n $time_spent_R" >> TIME_R.csv
        fi
        
        rm $g_$n.txt
    done
    TIME_SAVED=1
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 
