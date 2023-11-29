#!/bin/bash

# List of .txt files to process
files=("AVX_LS.csv" "AVX_SS.csv" "AVX_R.csv")
files+=("ENERGY_LS.csv" "ENERGY_SS.csv" "ENERGY_R.csv")
files+=("FLOPS_DP_LS.csv" "FLOPS_DP_SS.csv" "FLOPS_DP_R.csv")
files+=("AVX_LS.csv" "AVX_SS.csv" "AVX_R.csv")
files+=("L2CACHE_LS.csv" "L2CACHE_SS.csv" "L2CACHE_R.csv")
files+=("L3_LS.csv" "L3_SS.csv" "L3_R.csv")

# Gnuplot script filename
gnuplot_script="plot_script.gp"


# $1 = PLOT_TITLE1
# $2 = PLOT_TITLE2
function create_plot () {
# Generate the Gnuplot script for the current file
cat > "$gnuplot_script" <<EOL
set terminal pngcairo enhanced font 'Verdana,10' size 1600,1000
set output '$output_file'
set xlabel 'N'
set ylabel '$YLABEL'

set title 'Performance Comparison (Logarithmic Scale)'

set key outside right
set logscale y
set xtics rotate by -45 offset -1,-0.5
set mxtics 2
set size 1.8,1

set lmargin 15
set rmargin 170
set bmargin 8
set tmargin 8
set key at screen 0.95, screen 0.95

plot '$file' using 1:2 with linespoints title '$PLOT_TITLE1', \\
     '' using 1:3 with linespoints title '$PLOT_TITLE2'
EOL

    # Generate the plot using Gnuplot
    gnuplot "$gnuplot_script"

    # Optional: Cleanup the temporary Gnuplot script
    rm "$gnuplot_script"
}

# Iterate through the files and generate plots
for file in "${files[@]}"; do
    # Set the output filename based on the input file
    output_file="${file%.csv}.png"

    # switch case to change the YLABEL
    case $file in
        "FLOPS_DP_LS.csv" | "FLOPS_DP_SS.csv" | "FLOPS_DP_R.csv")
            YLABEL="MFLOPS/s"
            # extract the csv column names
            PLOT_TITLE1=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $1}' | sed 's/_/ /g')
            PLOT_TITLE2=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $2}' | sed 's/_/ /g')
            create_plot $PLOT_TITLE1 $PLOT_TITLE2
            ;;
        "AVX_LS.csv" | "AVX_SS.csv" | "AVX_R.csv")
            YLABEL="MFLOPS/s"
            PLOT_TITLE1=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $1}' | sed 's/_/ /g')
            PLOT_TITLE2=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $2}' | sed 's/_/ /g')
            create_plot $PLOT_TITLE1 $PLOT_TITLE2
            ;;
        "ENERGY_LS.csv" | "ENERGY_SS.csv" | "ENERGY_R.csv")
            YLABEL="Joules"
            PLOT_TITLE1=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $1}' | sed 's/_/ /g')
            PLOT_TITLE2=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $2}' | sed 's/_/ /g')
            create_plot $PLOT_TITLE1 $PLOT_TITLE2
            ;;
        "L2CACHE_LS.csv" | "L2CACHE_SS.csv" | "L2CACHE_R.csv")
            YLABEL="L2 Cache Miss Ratio"
            PLOT_TITLE1=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $1}' | sed 's/_/ /g')
            PLOT_TITLE2=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $2}' | sed 's/_/ /g')
            create_plot $PLOT_TITLE1 $PLOT_TITLE2
            ;;
        "L3_LS.csv" | "L3_SS.csv" | "L3_R")
            YLABEL="L3 Bandwidth"
            PLOT_TITLE1=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $1}' | sed 's/_/ /g')
            PLOT_TITLE2=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $2}' | sed 's/_/ /g')
            create_plot $PLOT_TITLE1 $PLOT_TITLE2
            ;;
        "time_LS.csv" | "time_SS.csv" | "time_R.csv")
            YLABEL="Time (ms)"
            PLOT_TITLE1=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $1}' | sed 's/_/ /g')
            PLOT_TITLE2=$(head -n 1 $file | cut -d ' ' -f 2- | awk '{print $2}' | sed 's/_/ /g')
            create_plot $PLOT_TITLE1 $PLOT_TITLE2
            ;;
    esac
    


done
